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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int b_EocEosInterrupt; unsigned char ui_AiNbrofChannels; unsigned int* ui_AiReadData; int /*<<< orphan*/  tsk_Current; scalar_t__ dw_AiBase; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGIO ; 
 TYPE_1__* devpriv ; 
 unsigned int readl (void*) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,void*) ; 

void v_APCI3XXX_Interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	unsigned char b_CopyCpt = 0;
	unsigned int dw_Status = 0;

	/***************************/
	/* Test if interrupt occur */
	/***************************/

	dw_Status = readl((void *)(devpriv->dw_AiBase + 16));
	if ( (dw_Status & 0x2UL) == 0x2UL) {
	   /***********************/
		/* Reset the interrupt */
	   /***********************/

		writel(dw_Status, (void *)(devpriv->dw_AiBase + 16));

	   /*****************************/
		/* Test if interrupt enabled */
	   /*****************************/

		if (devpriv->b_EocEosInterrupt == 1) {
	      /********************************/
			/* Read all analog inputs value */
	      /********************************/

			for (b_CopyCpt = 0;
				b_CopyCpt < devpriv->ui_AiNbrofChannels;
				b_CopyCpt++) {
				devpriv->ui_AiReadData[b_CopyCpt] =
					(unsigned int) readl((void *)(devpriv->
						dw_AiBase + 28));
			}

	      /**************************/
			/* Set the interrupt flag */
	      /**************************/

			devpriv->b_EocEosInterrupt = 2;

	      /**********************************************/
			/* Send a signal to from kernel to user space */
	      /**********************************************/

			send_sig(SIGIO, devpriv->tsk_Current, 0);
		}
	}
}