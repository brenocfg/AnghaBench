#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ iobase; TYPE_1__* ps_BoardInfo; } ;
struct TYPE_3__ {unsigned char i_NbrDoChannel; } ;

/* Variables and functions */
 unsigned char CR_CHAN (int /*<<< orphan*/ ) ; 
 TYPE_2__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI3XXX_InsnReadDigitalOutput(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = insn->n;
	unsigned char b_Channel = CR_CHAN(insn->chanspec);
	unsigned int dw_Status = 0;

	/************************/
	/* Test the buffer size */
	/************************/

	if (insn->n >= 1) {
	   /***************************/
		/* Test the channel number */
	   /***************************/

		if (b_Channel < devpriv->ps_BoardInfo->i_NbrDoChannel) {
	      /********************************/
			/* Read the digital output port */
	      /********************************/

			dw_Status = inl(devpriv->iobase + 48);

			dw_Status = (dw_Status >> b_Channel) & 1;
			*data = dw_Status;
		} else {
	      /***************************/
			/* Channel selection error */
	      /***************************/

			printk("Channel selection error\n");
			i_ReturnValue = -3;
		}
	} else {
	   /*******************/
		/* Data size error */
	   /*******************/

		printk("Buffer size error\n");
		i_ReturnValue = -101;
	}

	return i_ReturnValue;
}