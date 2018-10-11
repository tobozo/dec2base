#include <string>

const char *alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-_";

char *reverseString(char *x) {
  uint8_t n = strlen(x), i;
  if (n == 1) return x;
  uint8_t j = n / 2;
  for (i = 0; i < j; i++) {
    char c = x[i];
    x[i] = x[n - i - 1];
    x[n - i - 1] = c;
  }
  return x;
}

char *dec2base(uint32_t num, uint8_t base, uint8_t padding = 4) {
  if (base < 2) base = 2;
  if (base > 64) base = 64;
  std::string rslt;
  uint32_t current = num;
  uint8_t remainder, ln = 0;
  while (current > 0) {
    remainder = current % base;
    //Serial.print(" . current = "); Serial.println(current);
    //Serial.print(" . remainder = "); Serial.println(remainder);
    //Serial.print(" . remainder = "); Serial.println(alphabet[remainder]);
    rslt.push_back(alphabet[remainder]);
    current = current / base;
    ln += 1;
  }
  while (ln < padding) {
    rslt.push_back('0');
    ln += 1;
  }
  return reverseString((char*)rslt.c_str());
}

void setup() {
  Serial.begin(115200);
  Serial.print("Alphabet ");
  Serial.print("(");
  Serial.print(strlen(alphabet));
  Serial.print(" chars) : ");
  Serial.println( alphabet );
}

void loop() {
  uint8_t i;
  #if defined(ESP32)
    // built-in true random
    uint32_t r = esp_rand() % 1600000;
    uint8_t b = random(strlen(alphabet));
  #elif defined(ESP8266)
    // use ESP8266 true random library?
    uint32_t r = rand() % 1600000;
    uint8_t b = random(strlen(alphabet));
  #else
    // arduino and so on
    uint32_t r = rand() % 1600000;
    uint8_t b = random(strlen(alphabet));
  #endif
  if (b < 2) b = 2;
  if (b > 64) b = 64;
  Serial.print(r); Serial.print(" in base "+String(b)+": ");
  Serial.println(dec2base(r, b));
  delay(1000);
}
