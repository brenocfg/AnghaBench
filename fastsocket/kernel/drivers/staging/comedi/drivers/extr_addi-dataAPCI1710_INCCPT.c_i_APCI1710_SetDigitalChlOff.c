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
struct TYPE_13__ {scalar_t__ ui_Address; } ;
struct TYPE_14__ {TYPE_6__ s_BoardInfos; TYPE_5__* s_ModuleInfo; } ;
struct TYPE_9__ {int b_ModeRegister3; } ;
struct TYPE_10__ {int /*<<< orphan*/  dw_ModeRegister1_2_3_4; TYPE_2__ s_ByteModeRegister; } ;
struct TYPE_8__ {int b_CounterInit; } ;
struct TYPE_11__ {TYPE_3__ s_ModeRegister; TYPE_1__ s_InitFlag; } ;
struct TYPE_12__ {TYPE_4__ s_SiemensCounterInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_7__* devpriv ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

int i_APCI1710_SetDigitalChlOff(struct comedi_device *dev, unsigned char b_ModulNbr)
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
			devpriv->
				s_ModuleInfo[b_ModulNbr].
				s_SiemensCounterInfo.
				s_ModeRegister.
				s_ByteModeRegister.
				b_ModeRegister3 = devpriv->
				s_ModuleInfo[b_ModulNbr].
				s_SiemensCounterInfo.
				s_ModeRegister.
				s_ByteModeRegister.b_ModeRegister3 & 0xEF;

	      /**********************/
			/* Set the output Off */
	      /**********************/

			outl(devpriv->s_ModuleInfo[b_ModulNbr].
				s_SiemensCounterInfo.
				s_ModeRegister.
				dw_ModeRegister1_2_3_4, devpriv->s_BoardInfos.
				ui_Address + 20 + (64 * b_ModulNbr));
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