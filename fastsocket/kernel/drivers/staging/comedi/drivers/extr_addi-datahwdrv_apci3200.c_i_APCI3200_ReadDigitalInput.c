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
struct TYPE_2__ {int /*<<< orphan*/  i_IobaseReserved; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* devpriv ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI3200_ReadDigitalInput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_Temp = 0;
	unsigned int ui_NoOfChannel = 0;
	ui_NoOfChannel = CR_CHAN(insn->chanspec);
	ui_Temp = data[0];
	*data = inl(devpriv->i_IobaseReserved);

	if (ui_Temp == 0) {
		*data = (*data >> ui_NoOfChannel) & 0x1;
	}			/* if  (ui_Temp==0) */
	else {
		if (ui_Temp == 1) {
			if (data[1] < 0 || data[1] > 1) {
				printk("\nThe port number is in error\n");
				return -EINVAL;
			}	/* if(data[1] < 0 || data[1] >1) */
			switch (ui_NoOfChannel) {

			case 2:
				*data = (*data >> (2 * data[1])) & 0x3;
				break;
			case 3:
				*data = (*data & 15);
				break;
			default:
				comedi_error(dev, " chan spec wrong");
				return -EINVAL;	/*  "sorry channel spec wrong " */

			}	/* switch(ui_NoOfChannels) */
		}		/* if  (ui_Temp==1) */
		else {
			printk("\nSpecified channel not supported \n");
		}		/* elseif  (ui_Temp==1) */
	}
	return insn->n;
}