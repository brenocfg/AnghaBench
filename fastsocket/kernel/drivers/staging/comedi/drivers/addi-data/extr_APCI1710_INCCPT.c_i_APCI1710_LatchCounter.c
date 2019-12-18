#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_9__ {scalar_t__ ui_Address; } ;
struct TYPE_10__ {TYPE_4__ s_BoardInfos; TYPE_3__* s_ModuleInfo; } ;
struct TYPE_6__ {int b_CounterInit; } ;
struct TYPE_7__ {TYPE_1__ s_InitFlag; } ;
struct TYPE_8__ {TYPE_2__ s_SiemensCounterInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_5__* devpriv ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

int i_APCI1710_LatchCounter(struct comedi_device *dev,
	unsigned char b_ModulNbr, unsigned char b_LatchReg)
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
	      /*************************************/
			/* Test the latch register parameter */
	      /*************************************/

			if (b_LatchReg < 2) {
		 /*********************/
				/* Tatch the counter */
		 /*********************/

				outl(1 << (b_LatchReg * 4),
					devpriv->s_BoardInfos.ui_Address +
					(64 * b_ModulNbr));
			} else {
		 /**************************************************/
				/* The selected latch register parameter is wrong */
		 /**************************************************/

				DPRINTK("The selected latch register parameter is wrong\n");
				i_ReturnValue = -4;
			}
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