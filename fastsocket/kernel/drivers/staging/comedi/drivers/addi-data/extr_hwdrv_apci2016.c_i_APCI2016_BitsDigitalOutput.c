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
 scalar_t__ APCI2016_DIGITAL_OP_RW ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* devpriv ; 
 unsigned int inw (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI2016_BitsDigitalOutput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_Temp;
	unsigned int ui_NoOfChannel;
	ui_NoOfChannel = CR_CHAN(insn->chanspec);
	if ((ui_NoOfChannel < 0) || (ui_NoOfChannel > 15)) {
		comedi_error(dev,
			"Invalid Channel Numbers !!!, Channel Numbers must be between 0 and 15\n");
		return -EINVAL;
	}			/*  if  ((ui_NoOfChannel<0) || (ui_NoOfChannel>15)) */
	if ((data[0] != 0) && (data[0] != 1)) {
		comedi_error(dev,
			"Invalid Data[0] value !!!, Data[0] should be 0 or 1\n");
		return -EINVAL;
	}			/*  if  ((data[0]!=0) && (data[0]!=1)) */
	ui_Temp = data[0];
	*data = inw(devpriv->iobase + APCI2016_DIGITAL_OP_RW);
	if (ui_Temp == 0) {
		*data = (*data >> ui_NoOfChannel) & 0x1;
	}			/*  if  (ui_Temp==0) */
	else {
		if (ui_Temp == 1) {
			switch (ui_NoOfChannel) {
			case 2:
				*data = (*data >> (2 * data[1])) & 3;
				break;

			case 4:
				*data = (*data >> (4 * data[1])) & 15;
				break;

			case 8:
				*data = (*data >> (8 * data[1])) & 255;
				break;

			case 15:
				break;

			default:
				comedi_error(dev, " chan spec wrong");
				return -EINVAL;	/*  "sorry channel spec wrong " */
			}	/* switch(ui_NoOfChannel) */
		}		/*  if  (ui_Temp==1) */
		else {
			printk("\nSpecified channel not supported \n");
		}		/*  else if  (ui_Temp==1) */
	}			/*  if  (ui_Temp==0) */
	return insn->n;
}