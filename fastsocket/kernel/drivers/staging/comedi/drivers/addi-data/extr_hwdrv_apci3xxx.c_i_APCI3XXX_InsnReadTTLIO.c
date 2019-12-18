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
 int /*<<< orphan*/  printk (char*,...) ; 

int i_APCI3XXX_InsnReadTTLIO(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{
	unsigned char b_Channel = (unsigned char) CR_CHAN(insn->chanspec);
	int i_ReturnValue = insn->n;
	unsigned int *pls_ReadData = data;

	/************************/
	/* Test the buffer size */
	/************************/

	if (insn->n >= 1) {
	   /***********************/
		/* Test if read port 0 */
	   /***********************/

		if (b_Channel < 8) {
	      /*******************************************/
			/* Read port 0 (first digital output port) */
	      /*******************************************/

			pls_ReadData[0] = inl(devpriv->iobase + 80);
			pls_ReadData[0] = (pls_ReadData[0] >> b_Channel) & 1;
		} else {
	      /***********************/
			/* Test if read port 1 */
	      /***********************/

			if ((b_Channel > 7) && (b_Channel < 16)) {
		 /******************************************/
				/* Read port 1 (first digital input port) */
		 /******************************************/

				pls_ReadData[0] = inl(devpriv->iobase + 64);
				pls_ReadData[0] =
					(pls_ReadData[0] >> (b_Channel -
						8)) & 1;
			} else {
		 /***********************/
				/* Test if read port 2 */
		 /***********************/

				if ((b_Channel > 15) && (b_Channel < 24)) {
		    /************************/
					/* Test if port 2 input */
		    /************************/

					if ((devpriv->ul_TTLPortConfiguration[0]
							& 0xFF) == 0) {
						pls_ReadData[0] =
							inl(devpriv->iobase +
							96);
						pls_ReadData[0] =
							(pls_ReadData[0] >>
							(b_Channel - 16)) & 1;
					} else {
						pls_ReadData[0] =
							inl(devpriv->iobase +
							112);
						pls_ReadData[0] =
							(pls_ReadData[0] >>
							(b_Channel - 16)) & 1;
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