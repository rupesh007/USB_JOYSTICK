//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"

BYTE mouse[3] = {0,0,0};
void initialisation();
 unsigned char cResult1, cResult2;
 

void main(void)
{
    char a,b;
    int c1,c2;
    initialisation();
	//while(1)
	for(;1;) {	
	
     while(DUALADC8_fIsDataAvailable == 0); // Wait for data to be ready
     cResult1 = DUALADC8_cGetData1();
	 
	 LCD_Position(0,1);
	 LCD_PrHexByte(cResult1);
	 cResult2 = DUALADC8_cGetData2ClearFlag(); // Get Data from ADC Input2
	 
	  LCD_Position(1,1);
	  LCD_PrHexByte(cResult2);
	  c1= cResult1-0x68;
	  c2= cResult2-0x6c;
	  
	  
	  
// and clear data ready flag
      //User_Function(cResult1,cResult2);
	
	while(!USBFS_bGetConfiguration());
	while(!USBFS_bGetEPAckState(1));
	USBFS_LoadInEP(1, mouse, 3, USB_NO_TOGGLE);
	        if (c1>130) 
				mouse[2]=0x05; //moves the cursor to the horizontal right
			else if(c1<130) 
				mouse[2]=0xFB; //moves the cursor to the horizontal left
			else mouse[2]=0x00;		//resets the array	
			
			if(c2>130)  
				mouse[1]=0x05;	//moves the cursor up
												
			else if(c2<130) 
				mouse[1]=0xFB;	//moves the cursor down
			else mouse[1]=0x00;
								
					
}
}


 void initialisation(){
    M8C_EnableGInt;
    PGA_1_SetGain(PGA_1_G1_00);
    PGA_1_Start(PGA_1_MEDPOWER);
	PGA_2_SetGain(PGA_2_G1_00);
    PGA_2_Start(PGA_2_MEDPOWER);
	DUALADC8_Start(DUALADC8_HIGHPOWER);
	DUALADC8_GetSamples();
	DUALADC8_SetCalcTime(100);
	USBFS_Start(0, USB_5V_OPERATION);
	LCD_Start();
	
	
	}