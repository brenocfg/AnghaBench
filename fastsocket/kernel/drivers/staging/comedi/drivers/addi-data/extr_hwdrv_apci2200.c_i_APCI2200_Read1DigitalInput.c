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
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ APCI2200_DIGITAL_IP ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 TYPE_1__* devpriv ; 
 scalar_t__ inw (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI2200_Read1DigitalInput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_TmpValue = 0;
	unsigned int ui_Channel;
	ui_Channel = CR_CHAN(insn->chanspec);
	if (ui_Channel >= 0 && ui_Channel <= 7) {
		ui_TmpValue = (unsigned int) inw(devpriv->iobase + APCI2200_DIGITAL_IP);
		*data = (ui_TmpValue >> ui_Channel) & 0x1;
	}			/* if(ui_Channel >= 0 && ui_Channel <=7) */
	else {
		printk("\nThe specified channel does not exist\n");
		return -EINVAL;	/*  "sorry channel spec wrong " */
	}			/* else if(ui_Channel >= 0 && ui_Channel <=7) */

	return insn->n;
}