#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {unsigned int b_OutputMemoryStatus; scalar_t__ iobase; int /*<<< orphan*/  tsk_Current; } ;

/* Variables and functions */
 unsigned int ADDIDATA_DISABLE ; 
 unsigned int ADDIDATA_ENABLE ; 
 scalar_t__ APCI2032_DIGITAL_OP_INTERRUPT ; 
 int EINVAL ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  current ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  ui_InterruptData ; 

int i_APCI2032_ConfigDigitalOutput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ul_Command = 0;
	devpriv->tsk_Current = current;

	if ((data[0] != 0) && (data[0] != 1)) {
		comedi_error(dev,
			"Not a valid Data !!! ,Data should be 1 or 0\n");
		return -EINVAL;
	}			/* if  ( (data[0]!=0) && (data[0]!=1) ) */
	if (data[0]) {
		devpriv->b_OutputMemoryStatus = ADDIDATA_ENABLE;
	}			/*  if  (data[0]) */
	else {
		devpriv->b_OutputMemoryStatus = ADDIDATA_DISABLE;
	}			/* else if  (data[0]) */

	if (data[1] == ADDIDATA_ENABLE) {
		ul_Command = ul_Command | 0x1;
	}			/* if  (data[1] == ADDIDATA_ENABLE) */
	else {
		ul_Command = ul_Command & 0xFFFFFFFE;
	}			/* elseif  (data[1] == ADDIDATA_ENABLE) */
	if (data[2] == ADDIDATA_ENABLE) {
		ul_Command = ul_Command | 0x2;
	}			/* if  (data[2] == ADDIDATA_ENABLE) */
	else {
		ul_Command = ul_Command & 0xFFFFFFFD;
	}			/* elseif  (data[2] == ADDIDATA_ENABLE) */
	outl(ul_Command, devpriv->iobase + APCI2032_DIGITAL_OP_INTERRUPT);
	ui_InterruptData = inl(devpriv->iobase + APCI2032_DIGITAL_OP_INTERRUPT);
	return insn->n;
}