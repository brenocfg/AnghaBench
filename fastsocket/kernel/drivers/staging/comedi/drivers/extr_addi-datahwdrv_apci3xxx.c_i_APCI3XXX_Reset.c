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
struct comedi_device {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {scalar_t__ dw_AiBase; scalar_t__ b_EocEosInterrupt; } ;

/* Variables and functions */
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (void*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,void*) ; 

int i_APCI3XXX_Reset(struct comedi_device *dev)
{
	unsigned char b_Cpt = 0;

	/*************************/
	/* Disable the interrupt */
	/*************************/

	disable_irq(dev->irq);

	/****************************/
	/* Reset the interrupt flag */
	/****************************/

	devpriv->b_EocEosInterrupt = 0;

	/***************************/
	/* Clear the start command */
	/***************************/

	writel(0, (void *)(devpriv->dw_AiBase + 8));

	/*****************************/
	/* Reset the interrupt flags */
	/*****************************/

	writel(readl((void *)(devpriv->dw_AiBase + 16)),
		(void *)(devpriv->dw_AiBase + 16));

	/*****************/
	/* clear the EOS */
	/*****************/

	readl((void *)(devpriv->dw_AiBase + 20));

	/******************/
	/* Clear the FIFO */
	/******************/

	for (b_Cpt = 0; b_Cpt < 16; b_Cpt++) {
		readl((void *)(devpriv->dw_AiBase + 28));
	}

	/************************/
	/* Enable the interrupt */
	/************************/

	enable_irq(dev->irq);

	return 0;
}