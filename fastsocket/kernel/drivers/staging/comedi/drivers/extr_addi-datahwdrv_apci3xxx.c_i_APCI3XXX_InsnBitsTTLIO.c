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
struct TYPE_2__ {int* ul_TTLPortConfiguration; scalar_t__ iobase; } ;

/* Variables and functions */
 TYPE_1__* devpriv ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI3XXX_InsnBitsTTLIO(struct comedi_device *dev,
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

		if (((dw_ChannelMask & 0XFF00FF00) == 0) &&
			(((devpriv->ul_TTLPortConfiguration[0] & 0xFF) == 0xFF)
				|| (((devpriv->ul_TTLPortConfiguration[0] &
							0xFF) == 0)
					&& ((dw_ChannelMask & 0XFF0000) ==
						0)))) {
	      /*********************************/
			/* Test if set/reset any channel */
	      /*********************************/

			if (dw_ChannelMask) {
		 /****************************************/
				/* Test if set/rest any port 0 channels */
		 /****************************************/

				if (dw_ChannelMask & 0xFF) {
		    /*******************************************/
					/* Read port 0 (first digital output port) */
		    /*******************************************/

					dw_Status = inl(devpriv->iobase + 80);

					for (b_ChannelCpt = 0; b_ChannelCpt < 8;
						b_ChannelCpt++) {
						if ((dw_ChannelMask >>
								b_ChannelCpt) &
							1) {
							dw_Status =
								(dw_Status &
								(0xFF - (1 << b_ChannelCpt))) | (dw_BitMask & (1 << b_ChannelCpt));
						}
					}

					outl(dw_Status, devpriv->iobase + 80);
				}

		 /****************************************/
				/* Test if set/rest any port 2 channels */
		 /****************************************/

				if (dw_ChannelMask & 0xFF0000) {
					dw_BitMask = dw_BitMask >> 16;
					dw_ChannelMask = dw_ChannelMask >> 16;

		    /********************************************/
					/* Read port 2 (second digital output port) */
		    /********************************************/

					dw_Status = inl(devpriv->iobase + 112);

					for (b_ChannelCpt = 0; b_ChannelCpt < 8;
						b_ChannelCpt++) {
						if ((dw_ChannelMask >>
								b_ChannelCpt) &
							1) {
							dw_Status =
								(dw_Status &
								(0xFF - (1 << b_ChannelCpt))) | (dw_BitMask & (1 << b_ChannelCpt));
						}
					}

					outl(dw_Status, devpriv->iobase + 112);
				}
			}

	      /*******************************************/
			/* Read port 0 (first digital output port) */
	      /*******************************************/

			data[1] = inl(devpriv->iobase + 80);

	      /******************************************/
			/* Read port 1 (first digital input port) */
	      /******************************************/

			data[1] = data[1] | (inl(devpriv->iobase + 64) << 8);

	      /************************/
			/* Test if port 2 input */
	      /************************/

			if ((devpriv->ul_TTLPortConfiguration[0] & 0xFF) == 0) {
				data[1] =
					data[1] | (inl(devpriv->iobase +
						96) << 16);
			} else {
				data[1] =
					data[1] | (inl(devpriv->iobase +
						112) << 16);
			}
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