#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_5__ {size_t ui_Read; TYPE_1__* s_FIFOInterruptParameters; } ;
struct TYPE_6__ {TYPE_2__ s_InterruptParameters; } ;
struct TYPE_4__ {unsigned int b_OldModuleMask; unsigned int ul_OldInterruptMask; unsigned int ul_OldCounterLatchValue; } ;

/* Variables and functions */
 int APCI1710_SAVE_INTERRUPT ; 
 TYPE_3__* devpriv ; 

int i_APCI1710_InsnBitsReadPWMInterrupt(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	data[0] = devpriv->s_InterruptParameters.
		s_FIFOInterruptParameters[devpriv->
		s_InterruptParameters.ui_Read].b_OldModuleMask;
	data[1] = devpriv->s_InterruptParameters.
		s_FIFOInterruptParameters[devpriv->
		s_InterruptParameters.ui_Read].ul_OldInterruptMask;
	data[2] = devpriv->s_InterruptParameters.
		s_FIFOInterruptParameters[devpriv->
		s_InterruptParameters.ui_Read].ul_OldCounterLatchValue;

	/**************************/
	/* Increment the read FIFO */
	/***************************/

	devpriv->
		s_InterruptParameters.
		ui_Read = (devpriv->
		s_InterruptParameters.ui_Read + 1) % APCI1710_SAVE_INTERRUPT;

	return insn->n;

}