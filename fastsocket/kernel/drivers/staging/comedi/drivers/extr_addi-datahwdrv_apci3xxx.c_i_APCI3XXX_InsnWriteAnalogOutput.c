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
struct TYPE_4__ {scalar_t__ dw_AiBase; TYPE_1__* ps_BoardInfo; } ;
struct TYPE_3__ {unsigned char i_NbrAoChannel; } ;

/* Variables and functions */
 scalar_t__ CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ CR_RANGE (int /*<<< orphan*/ ) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned int readl (void*) ; 
 int /*<<< orphan*/  writel (unsigned int,void*) ; 

int i_APCI3XXX_InsnWriteAnalogOutput(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	unsigned char b_Range = (unsigned char) CR_RANGE(insn->chanspec);
	unsigned char b_Channel = (unsigned char) CR_CHAN(insn->chanspec);
	unsigned int dw_Status = 0;
	int i_ReturnValue = insn->n;

	/************************/
	/* Test the buffer size */
	/************************/

	if (insn->n >= 1) {
	   /***************************/
		/* Test the channel number */
	   /***************************/

		if (b_Channel < devpriv->ps_BoardInfo->i_NbrAoChannel) {
	      /**********************************/
			/* Test the channel configuration */
	      /**********************************/

			if (b_Range < 2) {
		 /***************************/
				/* Set the range selection */
		 /***************************/

				writel(b_Range,
					(void *)(devpriv->dw_AiBase + 96));

		 /**************************************************/
				/* Write the analog value to the selected channel */
		 /**************************************************/

				writel((data[0] << 8) | b_Channel,
					(void *)(devpriv->dw_AiBase + 100));

		 /****************************/
				/* Wait the end of transfer */
		 /****************************/

				do {
					dw_Status =
						readl((void *)(devpriv->
							dw_AiBase + 96));
				} while ((dw_Status & 0x100) != 0x100);
			} else {
		 /***************************/
				/* Channel not initialised */
		 /***************************/

				i_ReturnValue = -4;
				printk("Channel %d range %d selection error\n",
					b_Channel, b_Range);
			}
		} else {
	      /***************************/
			/* Channel selection error */
	      /***************************/

			i_ReturnValue = -3;
			printk("Channel %d selection error\n", b_Channel);
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