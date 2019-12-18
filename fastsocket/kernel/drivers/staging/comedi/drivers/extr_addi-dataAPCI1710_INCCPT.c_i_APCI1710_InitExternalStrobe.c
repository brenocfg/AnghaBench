#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_9__ {int* dw_MolduleConfiguration; } ;
struct TYPE_14__ {TYPE_6__* s_ModuleInfo; TYPE_2__ s_BoardInfos; } ;
struct TYPE_10__ {int b_ModeRegister4; } ;
struct TYPE_11__ {TYPE_3__ s_ByteModeRegister; } ;
struct TYPE_8__ {int b_CounterInit; } ;
struct TYPE_12__ {TYPE_4__ s_ModeRegister; TYPE_1__ s_InitFlag; } ;
struct TYPE_13__ {TYPE_5__ s_SiemensCounterInfo; } ;

/* Variables and functions */
 unsigned char APCI1710_HIGH ; 
 unsigned char APCI1710_LOW ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_7__* devpriv ; 

int i_APCI1710_InitExternalStrobe(struct comedi_device *dev,
	unsigned char b_ModulNbr, unsigned char b_ExternalStrobe, unsigned char b_ExternalStrobeLevel)
{
	int i_ReturnValue = 0;

	/**************************/
	/* Test the module number */
	/**************************/

	if (b_ModulNbr < 4) {
	   /*******************************/
		/* Test if counter initialised */
	   /*******************************/

		if (devpriv->
			s_ModuleInfo[b_ModulNbr].
			s_SiemensCounterInfo.s_InitFlag.b_CounterInit == 1) {
	      /**************************************/
			/* Test the external strobe selection */
	      /**************************************/

			if (b_ExternalStrobe == 0 || b_ExternalStrobe == 1) {
		 /******************/
				/* Test the level */
		 /******************/

				if ((b_ExternalStrobeLevel == APCI1710_HIGH) ||
					((b_ExternalStrobeLevel == APCI1710_LOW
							&& (devpriv->
								s_BoardInfos.
								dw_MolduleConfiguration
								[b_ModulNbr] &
								0xFFFF) >=
							0x3135))) {
		    /*****************/
					/* Set the level */
		    /*****************/

					devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_SiemensCounterInfo.
						s_ModeRegister.
						s_ByteModeRegister.
						b_ModeRegister4 = (devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_SiemensCounterInfo.
						s_ModeRegister.
						s_ByteModeRegister.
						b_ModeRegister4 & (0xFF -
							(0x10 << b_ExternalStrobe))) | ((b_ExternalStrobeLevel ^ 1) << (4 + b_ExternalStrobe));
				} else {
		    /********************************************/
					/* External strobe level parameter is wrong */
		    /********************************************/

					DPRINTK("External strobe level parameter is wrong\n");
					i_ReturnValue = -5;
				}
			}	/*  if (b_ExternalStrobe == 0 || b_ExternalStrobe == 1) */
			else {
		 /**************************************/
				/* External strobe selection is wrong */
		 /**************************************/

				DPRINTK("External strobe selection is wrong\n");
				i_ReturnValue = -4;
			}	/*  if (b_ExternalStrobe == 0 || b_ExternalStrobe == 1) */
		} else {
	      /****************************************/
			/* Counter not initialised see function */
			/* "i_APCI1710_InitCounter"             */
	      /****************************************/

			DPRINTK("Counter not initialised\n");
			i_ReturnValue = -3;
		}
	} else {
	   /*************************************************/
		/* The selected module number parameter is wrong */
	   /*************************************************/

		DPRINTK("The selected module number parameter is wrong\n");
		i_ReturnValue = -2;
	}

	return i_ReturnValue;
}