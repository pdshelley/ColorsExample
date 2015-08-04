/*
  ColorsExample
  For use with the "Handy BLE" iPhone app by Paul Shelley and 
  the LightBlue Bean by Punchthrough Design.

  This sketch receives Serial data with a simple packet format
  of '#' for a start character and ';' as an end character. Start
  and end characters can be changed easily. Simple error checking 
  is also included. 
  
  Handy BLE - https://pdshelley.com
  LightBlueBean - https://punchthrough.com

  This example code is in the public domain.

  Created 9 June 2015
  by Paul Shelley
*/

String command;
boolean commandStarted = false;

void setup() {
  Serial.begin(57600);
}

void loop() {
  getCommand();
}

/* 
This function reads the serial port and checks for the start character '#'
if the start character if found it will add all received characters to 
the command buffer until it receives the end command ';' When the end 
command is received the commandCompleted() function is called.
if a second start character is found before an end character then the buffer
is cleared and the process starts over. 
*/
void getCommand() {
   while (Serial.available()) {
    char newChar = (char)Serial.read();
    if (newChar == '#') {
      commandStarted = true;
      command = "\0";
    } else if (newChar == ';') {
      commandStarted = false;
      commandCompleted();
      command = "\0";
    } else if (commandStarted == true) {
      command += newChar;
    }
  }
}

/*
This function takes the completed command and checks it against a list
of available commands and executes the appropriate code.  Add extra 'if' 
statements to add commands with the code you want to execute when that 
command is received. It is recommended to create a function for a command
if there are more than a few lines of code for as in the 'off' example.
*/
void commandCompleted() {
  if (command == "red") {
    Bean.setLed( 255, 0, 0 );
  }
  if (command == "green") {
    Bean.setLed( 0, 255, 0 ); 
  }
  if (command == "blue") {
    Bean.setLed( 0, 0, 255 );
  }
  if (command == "yellow") {
    Bean.setLed( 255, 255, 0 ); 
  }
  if (command == "orange") {
    Bean.setLed( 255, 60, 0 ); 
  }
  if (command == "purple") {
    Bean.setLed( 128, 0, 128 );
  }
  if (command == "white") {
    Bean.setLed( 255, 255, 255 );
  }
  if (command == "off") {
    off();
  }
}

/*
Use a separate function like this when there are more than just a few
lines of code.  This will help maintain clean easy to read code.
*/
void off() {
  Bean.setLed( 0, 0, 0 );
}
