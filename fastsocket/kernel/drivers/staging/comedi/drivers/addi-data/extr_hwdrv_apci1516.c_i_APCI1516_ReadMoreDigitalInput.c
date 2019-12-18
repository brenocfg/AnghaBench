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
 scalar_t__ APCI1516_DIGITAL_IP ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 TYPE_1__* devpriv ; 
 scalar_t__ inw (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1516_ReadMoreDigitalInput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{

	unsigned int ui_PortValue = data[0];
	unsigned int ui_Mask = 0;
	unsigned int ui_NoOfChannels;

	ui_NoOfChannels = CR_CHAN(insn->chanspec);

	*data = (unsigned int) inw(devpriv->iobase + APCI1516_DIGITAL_IP);
	switch (ui_NoOfChannels) {
	case 2:
		ui_Mask = 3;
		*data = (*data >> (2 * ui_PortValue)) & ui_Mask;
		break;
	case 4:
		ui_Mask = 15;
		*data = (*data >> (4 * ui_PortValue)) & ui_Mask;
		break;
	case 7:
		break;

	default:
		printk("\nWrong parameters\n");
		return -EINVAL;	/*  "sorry channel spec wrong " */
		break;
	}			/* switch(ui_NoOfChannels) */

	return insn->n;
}