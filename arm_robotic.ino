#include <Servo.h>
#include <IRremote.h>

Servo servoLeft;
Servo servoRight;
Servo servoBase;
Servo servoHook;

int positionHook = 0;
int positionServeLeft = 170;
int positionServeRight = 30;
int positionBase = 90;
int pinoReceiver = 7;
boolean openedHook = false;

IRrecv irrecv(pinoReceiver);
decode_results results;

void setup() {
  servoBase.attach(2);
  servoHook.attach(3);
  servoRight.attach(5);
  servoLeft.attach(4);

  servoBase.write(positionBase);
  servoHook.write(160);
  servoRight.write(positionServeRight);
  servoLeft.write(positionServeLeft);
  irrecv.enableIRIn();

  Serial.begin(9600);
}

void onMoveRight(){
  if(positionBase > 0){
     positionBase-=10;
     servoBase.write(positionBase);
     delay(15);
  }
}

void onMoveLeft(){
  if(positionBase <= 180){
    positionBase+=10;
    servoBase.write(positionBase);
    delay(15);
  }
}

void onOpenHook(){
  servoHook.write(60);
}

void onCloseHook(){
 servoHook.write(160);
}

void onOpenOrCloseHook(){
  if(openedHook){
     servoHook.write(170);
     openedHook = false;
  }else{
     servoHook.write(60);
     openedHook = true;
  }
}

void onUpArm(){
  if(positionServeLeft <= 190){
    positionServeLeft+=10;
    servoLeft.write(positionServeLeft);
    delay(15);
  }
}

void onDownArm(){
  if(positionServeLeft >= 95){
    positionServeLeft-=10;
    servoLeft.write(positionServeLeft);
    delay(15);
  }
}

void onToFrontArm(){  
  if(positionServeRight <= 120){
    positionServeRight+=10;
    servoRight.write(positionServeRight);
    delay(15);
  }  
}

void onToBackArm(){  
  if(positionServeRight >= 0){
    positionServeRight-=10;
    servoRight.write(positionServeRight);
    delay(15);
  }
}



void loop() {
  char tecla = Serial.read();
  
  if(tecla == 'd' || tecla == 'D'){
    onMoveRight();
  }else if(tecla == 'e'|| tecla == 'E'){
    onMoveLeft();
  }else if(tecla == 'o' || tecla == 'O'){
    onOpenHook();
  }else if(tecla == 'c' || tecla == 'C'){
    onCloseHook();
  }else if(tecla == 's' || tecla == 'S'){
    onUpArm();
  }else if(tecla == 'b' || tecla == 'B'){
    onDownArm();
  }else if(tecla == 'f' || tecla == 'F'){
    onToFrontArm();
  }else if(tecla == 'v' || tecla == 'V'){
    onToBackArm();
  }

  if(irrecv.decode(&results)){
    Serial.println("Valor lido: ");
    Serial.println(results.value, HEX);

    switch(results.value){
      case 0xFD6897:
        onMoveRight();
        break;
      case 0xFD28D7:
        onMoveLeft();
        break;
      case 0xFDA857:
        onOpenOrCloseHook();
        break;
      case 0xFD8877:
        onUpArm();
        break;
      case 0xFD9867:
        onDownArm();
        break;
      case 0xFD708F:
        onToFrontArm();
        break;
      case 0xFD30CF:
        onToBackArm();
        break;
    }
    
    irrecv.resume();
  }

  delay(15);

}
