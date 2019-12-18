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
struct TYPE_10__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_14__ {TYPE_6__* s_ModuleInfo; TYPE_3__ s_BoardInfos; } ;
struct TYPE_11__ {int b_CounterInit; } ;
struct TYPE_8__ {unsigned char b_ModeRegister1; } ;
struct TYPE_9__ {int /*<<< orphan*/  dw_ModeRegister1_2_3_4; TYPE_1__ s_ByteModeRegister; } ;
struct TYPE_12__ {TYPE_4__ s_InitFlag; TYPE_2__ s_ModeRegister; } ;
struct TYPE_13__ {TYPE_5__ s_SiemensCounterInfo; } ;

/* Variables and functions */
 unsigned char APCI1710_16BIT_COUNTER ; 
 unsigned char APCI1710_32BIT_COUNTER ; 
 unsigned char APCI1710_DECREMENT ; 
 unsigned char APCI1710_DIRECT_MODE ; 
 unsigned char APCI1710_DOUBLE_MODE ; 
 unsigned char APCI1710_HYSTERESIS_OFF ; 
 unsigned char APCI1710_HYSTERESIS_ON ; 
 unsigned char APCI1710_INCREMENT ; 
 int APCI1710_INCREMENTAL_COUNTER ; 
 unsigned char APCI1710_QUADRUPLE_MODE ; 
 unsigned char APCI1710_SIMPLE_MODE ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_7__* devpriv ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

int i_APCI1710_InitCounter(struct comedi_device *dev,
	unsigned char b_ModulNbr,
	unsigned char b_CounterRange,
	unsigned char b_FirstCounterModus,
	unsigned char b_FirstCounterOption,
	unsigned char b_SecondCounterModus, unsigned char b_SecondCounterOption)
{
	int i_ReturnValue = 0;

	/*******************************/
	/* Test if incremental counter */
	/*******************************/

	if ((devpriv->s_BoardInfos.
			dw_MolduleConfiguration[b_ModulNbr] & 0xFFFF0000UL) ==
		APCI1710_INCREMENTAL_COUNTER) {
	   /**************************/
		/* Test the counter range */
	   /**************************/

		if (b_CounterRange == APCI1710_16BIT_COUNTER
			|| b_CounterRange == APCI1710_32BIT_COUNTER) {
	      /********************************/
			/* Test the first counter modus */
	      /********************************/

			if (b_FirstCounterModus == APCI1710_QUADRUPLE_MODE ||
				b_FirstCounterModus == APCI1710_DOUBLE_MODE ||
				b_FirstCounterModus == APCI1710_SIMPLE_MODE ||
				b_FirstCounterModus == APCI1710_DIRECT_MODE) {
		 /*********************************/
				/* Test the first counter option */
		 /*********************************/

				if ((b_FirstCounterModus == APCI1710_DIRECT_MODE
						&& (b_FirstCounterOption ==
							APCI1710_INCREMENT
							|| b_FirstCounterOption
							== APCI1710_DECREMENT))
					|| (b_FirstCounterModus !=
						APCI1710_DIRECT_MODE
						&& (b_FirstCounterOption ==
							APCI1710_HYSTERESIS_ON
							|| b_FirstCounterOption
							==
							APCI1710_HYSTERESIS_OFF)))
				{
		    /**************************/
					/* Test if 16-bit counter */
		    /**************************/

					if (b_CounterRange ==
						APCI1710_16BIT_COUNTER) {
		       /*********************************/
						/* Test the second counter modus */
		       /*********************************/

						if ((b_FirstCounterModus !=
								APCI1710_DIRECT_MODE
								&&
								(b_SecondCounterModus
									==
									APCI1710_QUADRUPLE_MODE
									||
									b_SecondCounterModus
									==
									APCI1710_DOUBLE_MODE
									||
									b_SecondCounterModus
									==
									APCI1710_SIMPLE_MODE))
							|| (b_FirstCounterModus
								==
								APCI1710_DIRECT_MODE
								&&
								b_SecondCounterModus
								==
								APCI1710_DIRECT_MODE))
						{
			  /**********************************/
							/* Test the second counter option */
			  /**********************************/

							if ((b_SecondCounterModus == APCI1710_DIRECT_MODE && (b_SecondCounterOption == APCI1710_INCREMENT || b_SecondCounterOption == APCI1710_DECREMENT)) || (b_SecondCounterModus != APCI1710_DIRECT_MODE && (b_SecondCounterOption == APCI1710_HYSTERESIS_ON || b_SecondCounterOption == APCI1710_HYSTERESIS_OFF))) {
								i_ReturnValue =
									0;
							} else {
			     /*********************************************************/
								/* The selected second counter operating option is wrong */
			     /*********************************************************/

								DPRINTK("The selected second counter operating option is wrong\n");
								i_ReturnValue =
									-7;
							}
						} else {
			  /*******************************************************/
							/* The selected second counter operating mode is wrong */
			  /*******************************************************/

							DPRINTK("The selected second counter operating mode is wrong\n");
							i_ReturnValue = -6;
						}
					}
				} else {
		    /********************************************************/
					/* The selected first counter operating option is wrong */
		    /********************************************************/

					DPRINTK("The selected first counter operating option is wrong\n");
					i_ReturnValue = -5;
				}
			} else {
		 /******************************************************/
				/* The selected first counter operating mode is wrong */
		 /******************************************************/
				DPRINTK("The selected first counter operating mode is wrong\n");
				i_ReturnValue = -4;
			}
		} else {
	      /***************************************/
			/* The selected counter range is wrong */
	      /***************************************/

			DPRINTK("The selected counter range is wrong\n");
			i_ReturnValue = -3;
		}

	   /*************************/
		/* Test if a error occur */
	   /*************************/

		if (i_ReturnValue == 0) {
	      /**************************/
			/* Test if 16-Bit counter */
	      /**************************/

			if (b_CounterRange == APCI1710_32BIT_COUNTER) {
				devpriv->
					s_ModuleInfo[b_ModulNbr].
					s_SiemensCounterInfo.
					s_ModeRegister.
					s_ByteModeRegister.
					b_ModeRegister1 = b_CounterRange |
					b_FirstCounterModus |
					b_FirstCounterOption;
			} else {
				devpriv->
					s_ModuleInfo[b_ModulNbr].
					s_SiemensCounterInfo.
					s_ModeRegister.
					s_ByteModeRegister.
					b_ModeRegister1 = b_CounterRange |
					(b_FirstCounterModus & 0x5) |
					(b_FirstCounterOption & 0x20) |
					(b_SecondCounterModus & 0xA) |
					(b_SecondCounterOption & 0x40);

		 /***********************/
				/* Test if direct mode */
		 /***********************/

				if (b_FirstCounterModus == APCI1710_DIRECT_MODE) {
					devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_SiemensCounterInfo.
						s_ModeRegister.
						s_ByteModeRegister.
						b_ModeRegister1 = devpriv->
						s_ModuleInfo[b_ModulNbr].
						s_SiemensCounterInfo.
						s_ModeRegister.
						s_ByteModeRegister.
						b_ModeRegister1 |
						APCI1710_DIRECT_MODE;
				}
			}

	      /***************************/
			/* Write the configuration */
	      /***************************/

			outl(devpriv->s_ModuleInfo[b_ModulNbr].
				s_SiemensCounterInfo.
				s_ModeRegister.
				dw_ModeRegister1_2_3_4,
				devpriv->s_BoardInfos.
				ui_Address + 20 + (64 * b_ModulNbr));

			devpriv->
				s_ModuleInfo[b_ModulNbr].
				s_SiemensCounterInfo.
				s_InitFlag.b_CounterInit = 1;
		}
	} else {
	   /**************************************/
		/* The module is not a counter module */
	   /**************************************/

		DPRINTK("The module is not a counter module\n");
		i_ReturnValue = -2;
	}

	return i_ReturnValue;
}