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
struct TYPE_13__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_14__ {TYPE_6__ s_BoardInfos; TYPE_5__* s_ModuleInfo; } ;
struct TYPE_9__ {int b_ModeRegister1; } ;
struct TYPE_10__ {TYPE_2__ s_ByteModeRegister; } ;
struct TYPE_8__ {int b_CounterInit; } ;
struct TYPE_11__ {TYPE_3__ s_ModeRegister; TYPE_1__ s_InitFlag; } ;
struct TYPE_12__ {TYPE_4__ s_SiemensCounterInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_7__* devpriv ; 
 unsigned int inl (scalar_t__) ; 

int i_APCI1710_Get16BitCBStatus(struct comedi_device *dev,
	unsigned char b_ModulNbr, unsigned char *pb_CBStatusCounter0, unsigned char *pb_CBStatusCounter1)
{
	int i_ReturnValue = 0;
	unsigned int dw_StatusReg = 0;

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
	      /*************************/
			/* Test if 2*16-Bit mode */
	      /*************************/

			if ((devpriv->s_ModuleInfo[b_ModulNbr].
					s_SiemensCounterInfo.
					s_ModeRegister.
					s_ByteModeRegister.
					b_ModeRegister1 & 0x10) == 0x10) {
		 /*****************************/
				/* Test the Firmware version */
		 /*****************************/

				if ((devpriv->s_BoardInfos.
						dw_MolduleConfiguration
						[b_ModulNbr] & 0xFFFF) >=
					0x3136) {
					dw_StatusReg =
						inl(devpriv->s_BoardInfos.
						ui_Address + 16 +
						(64 * b_ModulNbr));

					*pb_CBStatusCounter1 =
						(unsigned char) ((dw_StatusReg >> 0) &
						1);
					*pb_CBStatusCounter0 =
						(unsigned char) ((dw_StatusReg >> 1) &
						1);
				}	/*  if ((ps_APCI1710Variable->s_Board [b_BoardHandle].s_BoardInfos.dw_MolduleConfiguration [b_ModulNbr] & 0xFFFF) >= 0x3136) */
				else {
		    /****************************/
					/* Firmware revision error  */
		    /****************************/

					i_ReturnValue = -5;
				}	/*  if ((ps_APCI1710Variable->s_Board [b_BoardHandle].s_BoardInfos.dw_MolduleConfiguration [b_ModulNbr] & 0xFFFF) >= 0x3136) */
			}	/*  if ((ps_APCI1710Variable->s_Board [b_BoardHandle].s_ModuleInfo [b_ModulNbr].s_SiemensCounterInfo.s_ModeRegister.s_ByteModeRegister.b_ModeRegister1 & 0x10) == 0x10) */
			else {
		 /********************************************/
				/* Counter not initialised to 2*16-bit mode */
				/* "i_APCI1710_InitCounter"                 */
		 /********************************************/

				DPRINTK("Counter not initialised\n");
				i_ReturnValue = -4;
			}	/*  if ((ps_APCI1710Variable->s_Board [b_BoardHandle].s_ModuleInfo [b_ModulNbr].s_SiemensCounterInfo.s_ModeRegister.s_ByteModeRegister.b_ModeRegister1 & 0x10) == 0x10) */
		}		/*  if (ps_APCI1710Variable->s_Board [b_BoardHandle].s_ModuleInfo [b_ModulNbr].s_SiemensCounterInfo.s_InitFlag.b_CounterInit == 1) */
		else {
	      /****************************************/
			/* Counter not initialised see function */
			/* "i_APCI1710_InitCounter"             */
	      /****************************************/

			DPRINTK("Counter not initialised\n");
			i_ReturnValue = -3;
		}		/*  if (ps_APCI1710Variable->s_Board [b_BoardHandle].s_ModuleInfo [b_ModulNbr].s_SiemensCounterInfo.s_InitFlag.b_CounterInit == 1) */
	}			/*  if (b_ModulNbr < 4) */
	else {
	   /*************************************************/
		/* The selected module number parameter is wrong */
	   /*************************************************/

		DPRINTK("The selected module number parameter is wrong\n");
		i_ReturnValue = -2;
	}			/*  if (b_ModulNbr < 4) */

	return i_ReturnValue;
}