#include "Arduino.h"
#include "VirtualWire.h"

void setup()
{
  Serial.begin(9600);	// Debugging only
  Serial.println("receiver setup");
  vw_set_rx_pin(11);
  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
  
  vw_rx_start();       // Start the receiver PLL running
    pinMode(13, OUTPUT);
}

void loop()
{
  int i;
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
   String message;
      if (vw_get_message(buf, &buflen)) // Non-blocking
      {

    digitalWrite(13, true); // Flash a light to show received good message
  	// Message with a good checksum received, dump it.
  	Serial.print("Received: ");

  	for (i = 0; i < buflen; i++)
  	{
       message += char(buf[i]);
  	}
     Serial.println(message);
          digitalWrite(13, false);
      }
  
}

