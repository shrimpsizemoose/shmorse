int dot_dur = 100;
int BUZZ = 3;
int BUTTON = 4;

int state = 0;
const char* phrases[3] = {
  "... .... .-. .. -- .--. ... .. --.. . -- --- --- ... ."   // shrimpsizemoose
  "... -.-. .. .- .-. - .-.-.- .-.. --- .-..",               // sciart.lol
};

void setup() {
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  pinMode(1, OUTPUT);
  digitalWrite(1, LOW);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(BUZZ, OUTPUT);
  digitalWrite(BUZZ, LOW);

  pinMode(BUTTON, INPUT_PULLUP);
}

void p() { // between letters
  delay(dot_dur * 3);
}

void s() { // slovo
  delay(dot_dur * 7);
}

void dot() {
  digitalWrite(0, HIGH);
  for(int i = 0; i < (dot_dur / 4); i++) {
    digitalWrite(BUZZ, HIGH);
    delayMicroseconds(3816/2);
    digitalWrite(BUZZ, LOW);
    delayMicroseconds(3816/2);
  }
  // delay(dot_dur-80);
  digitalWrite(0, LOW);
  digitalWrite(BUZZ, LOW);
  delay(dot_dur);
}

void tire() {
  int dur = dot_dur * 3; 
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  for(int i = 0; i < (dot_dur / 4) * 3; i++) {
    digitalWrite(BUZZ, HIGH);
    delayMicroseconds(3816/2);
    digitalWrite(BUZZ, LOW);
    delayMicroseconds(3816/2);
  };
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(BUZZ, LOW);
  delay(dot_dur);
}
void k() {
  int seq[] = {0,1,2,0,1,2,0,1,2};
  for (int i = 0; i < 9; i++) {
    int led = i%3;
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite((led+1)%3,HIGH);
    digitalWrite(led, LOW);
    delay(50);
    digitalWrite((led+1)%3,LOW);
  }
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
}

// the loop function runs over and over again forever
void loop() {
  bool reading = digitalRead(BUTTON);
  if (reading == LOW) {
    k();
    state = (state + 1) % 3;
  }
  // state = 0;

  for (const char* c = phrases[state]; *c; c++) {
    if (*c == '.') {
      dot();
    } else if (*c == '-') {
      tire();
    } else if (*c == ' ') {
      s();
      continue;
    }
  }

  delay(1000);
}

