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
struct TYPE_2__ {scalar_t__ iobase; } ;

/* Variables and functions */
 TYPE_1__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI3XXX_InsnBitsDigitalOutput(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = insn->n;
	unsigned char b_ChannelCpt = 0;
	unsigned int dw_ChannelMask = 0;
	unsigned int dw_BitMask = 0;
	unsigned int dw_Status = 0;

	/************************/
	/* Test the buffer size */
	/************************/

	if (insn->n >= 2) {
	   /*******************************/
		/* Get the channe and bit mask */
	   /*******************************/

		dw_ChannelMask = data[0];
		dw_BitMask = data[1];

	   /*************************/
		/* Test the channel mask */
	   /*************************/

		if ((dw_ChannelMask & 0XFFFFFFF0) == 0) {
	      /*********************************/
			/* Test if set/reset any channel */
	      /*********************************/

			if (dw_ChannelMask & 0xF) {
		 /********************************/
				/* Read the digital output port */
		 /********************************/

				dw_Status = inl(devpriv->iobase + 48);

				for (b_ChannelCpt = 0; b_ChannelCpt < 4;
					b_ChannelCpt++) {
					if ((dw_ChannelMask >> b_ChannelCpt) &
						1) {
						dw_Status =
							(dw_Status & (0xF -
								(1 << b_ChannelCpt))) | (dw_BitMask & (1 << b_ChannelCpt));
					}
				}

				outl(dw_Status, devpriv->iobase + 48);
			}

	      /********************************/
			/* Read the digital output port */
	      /********************************/

			data[1] = inl(devpriv->iobase + 48);
		} else {
	      /************************/
			/* Config command error */
	      /************************/

			printk("Channel mask error\n");
			i_ReturnValue = -4;
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