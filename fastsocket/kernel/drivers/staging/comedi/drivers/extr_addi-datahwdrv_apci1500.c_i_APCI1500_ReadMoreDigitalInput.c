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
struct TYPE_2__ {scalar_t__ i_IobaseAddon; } ;

/* Variables and functions */
 scalar_t__ APCI1500_DIGITAL_IP ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 TYPE_1__* devpriv ; 
 scalar_t__ inw (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI1500_ReadMoreDigitalInput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_PortValue = data[1];
	unsigned int ui_Mask = 0;
	unsigned int ui_Channel;
	unsigned int ui_TmpValue = 0;
	ui_Channel = CR_CHAN(insn->chanspec);

	switch (data[0]) {
	case 0:
		if (ui_Channel >= 0 && ui_Channel <= 15) {
			ui_TmpValue =
				(unsigned int) inw(devpriv->i_IobaseAddon +
				APCI1500_DIGITAL_IP);
			*data = (ui_TmpValue >> ui_Channel) & 0x1;
		}		/* if(ui_Channel >= 0 && ui_Channel <=15) */
		else {
			printk("\nThe channel specification are in error\n");
			return -EINVAL;	/*  "sorry channel spec wrong " */
		}		/* else if(ui_Channel >= 0 && ui_Channel <=15) */
		break;
	case 1:

		*data = (unsigned int) inw(devpriv->i_IobaseAddon +
			APCI1500_DIGITAL_IP);
		switch (ui_Channel) {
		case 2:
			ui_Mask = 3;
			*data = (*data >> (2 * ui_PortValue)) & ui_Mask;
			break;
		case 4:
			ui_Mask = 15;
			*data = (*data >> (4 * ui_PortValue)) & ui_Mask;
			break;
		case 8:
			ui_Mask = 255;
			*data = (*data >> (8 * ui_PortValue)) & ui_Mask;
			break;
		case 15:
			break;

		default:
			printk("\nSpecified channel cannot be read \n");
			return -EINVAL;	/*  "sorry channel spec wrong " */
			break;
		}		/* switch(ui_Channel) */
		break;
	default:
		printk("\nThe specified functionality does not exist\n");
		return -EINVAL;
	}			/* switch(data[0]) */
	return insn->n;
}