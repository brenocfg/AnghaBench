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
 scalar_t__ APCI1032_DIGITAL_IP ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 TYPE_1__* devpriv ; 
 scalar_t__ inl (scalar_t__) ; 
 unsigned int ui_InterruptStatus ; 

int i_APCI1032_ReadMoreDigitalInput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_PortValue = data[0];
	unsigned int ui_Mask = 0;
	unsigned int ui_NoOfChannels;

	ui_NoOfChannels = CR_CHAN(insn->chanspec);
	if (data[1] == 0) {
		*data = (unsigned int) inl(devpriv->iobase + APCI1032_DIGITAL_IP);
		switch (ui_NoOfChannels) {
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
		case 16:
			ui_Mask = 65535;
			*data = (*data >> (16 * ui_PortValue)) & ui_Mask;
			break;
		case 31:
			break;
		default:
			/* comedi_error(dev," \nchan spec wrong\n"); */
			return -EINVAL;	/*  "sorry channel spec wrong " */
			break;
		}		/* switch(ui_NoOfChannels) */
	}			/* if(data[1]==0) */
	else {
		if (data[1] == 1) {
			*data = ui_InterruptStatus;
		}		/* if(data[1]==1) */
	}			/* else if(data[1]==0) */
	return insn->n;
}