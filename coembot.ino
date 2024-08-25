#include <Arduino.h>
#include <FastLED.h>

const int PIN_LED = 21;
const int NUM_LEDS = 1;
CRGB leds[NUM_LEDS];

const int RIGHT = 0;
const int LEFT = 1;

int angle[2] = { 5, 5 };

#define B(data, bit) (((data) & (1 << ((bit) % 4))) ? HIGH : LOW)

void rotate(int target, int i) {
  int bn = target * 4;
  digitalWrite(bn + 1, B(0b1001, i));
  digitalWrite(bn + 2, B(0b1100, i));
  digitalWrite(bn + 3, B(0b0110, i));
  digitalWrite(bn + 4, B(0b0011, i));
}

void move(int to_left, int to_right) {
  int a[2];
  a[LEFT] = to_left;
  a[RIGHT] = to_right;
  for (;;) {
    int moved = 0;
    for (int t = RIGHT; t <= LEFT; t++) {
      if (angle[t] < a[t]) {
        angle[t]++;
        moved++;
      } else if (angle[t] > a[t]) {
        angle[t]--;
        moved++;
      }
      rotate(t, angle[t]);
    }
    if (moved == 0) return;
    delay(50);
  }
}

void off() {
  for (int i = 1; i <= 8; i++) {
    digitalWrite(i, 0);
  }
}

void setup() {
  for (int i = 1; i <= 8; i++) {
    pinMode(i, OUTPUT);
  }
  off();

  FastLED.addLeds<WS2812, PIN_LED, GRB>(leds, NUM_LEDS);

  move(5, 5);
  delay(1000);
}

void led(int on) {
  leds[0] = on ? CRGB::Red : CRGB::Black;
  FastLED.show();
}

void loop() {
  for (int i = 0; i < 2; i++) {
    led(1);
    move(3, 7);
    delay(200);
    move(7, 3);
    delay(200);
    move(3, 7);
    delay(200);
    move(5, 5);
    led(0);
    delay(400);
  }
  led(1);
  for (int i = 0; i < 3; i++) {
    move(3, 7);
    delay(200);
    move(7, 3);
    delay(200);
  }
  move(3, 7);
  delay(200);
  move(5, 5);
  led(0);
  delay(400);
}
