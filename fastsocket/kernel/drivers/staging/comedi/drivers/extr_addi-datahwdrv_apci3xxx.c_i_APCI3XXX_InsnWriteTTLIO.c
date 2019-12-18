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
struct TYPE_2__ {int* ul_TTLPortConfiguration; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ CR_CHAN (int /*<<< orphan*/ ) ; 
 TYPE_1__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

int i_APCI3XXX_InsnWriteTTLIO(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	int i_ReturnValue = insn->n;
	unsigned char b_Channel = (unsigned char) CR_CHAN(insn->chanspec);
	unsigned char b_State = 0;
	unsigned int dw_Status = 0;

	/************************/
	/* Test the buffer size */
	/************************/

	if (insn->n >= 1) {
		b_State = (unsigned char) data[0];

	   /***********************/
		/* Test if read port 0 */
	   /***********************/

		if (b_Channel < 8) {
	      /*****************************************************************************/
			/* Read port 0 (first digital output port) and set/reset the selcted channel */
	      /*****************************************************************************/

			dw_Status = inl(devpriv->iobase + 80);
			dw_Status =
				(dw_Status & (0xFF -
					(1 << b_Channel))) | ((b_State & 1) <<
				b_Channel);
			outl(dw_Status, devpriv->iobase + 80);
		} else {
	      /***********************/
			/* Test if read port 2 */
	      /***********************/

			if ((b_Channel > 15) && (b_Channel < 24)) {
		 /*************************/
				/* Test if port 2 output */
		 /*************************/

				if ((devpriv->ul_TTLPortConfiguration[0] & 0xFF)
					== 0xFF) {
		    /*****************************************************************************/
					/* Read port 2 (first digital output port) and set/reset the selcted channel */
		    /*****************************************************************************/

					dw_Status = inl(devpriv->iobase + 112);
					dw_Status =
						(dw_Status & (0xFF -
							(1 << (b_Channel -
									16)))) |
						((b_State & 1) << (b_Channel -
							16));
					outl(dw_Status, devpriv->iobase + 112);
				} else {
		    /***************************/
					/* Channel selection error */
		    /***************************/

					i_ReturnValue = -3;
					printk("Channel %d selection error\n",
						b_Channel);
				}
			} else {
		 /***************************/
				/* Channel selection error */
		 /***************************/

				i_ReturnValue = -3;
				printk("Channel %d selection error\n",
					b_Channel);
			}
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