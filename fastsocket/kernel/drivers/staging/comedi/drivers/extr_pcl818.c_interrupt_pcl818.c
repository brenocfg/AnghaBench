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
struct comedi_device {int /*<<< orphan*/  irq; scalar_t__ iobase; struct comedi_subdevice* subdevices; int /*<<< orphan*/  attached; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ ai_act_scan; int ai_mode; scalar_t__ irq_blocked; int /*<<< orphan*/  irq_free; scalar_t__ neverending_ai; scalar_t__ irq_was_now_closed; } ;

/* Variables and functions */
#define  INT_TYPE_AI1_DMA 135 
#define  INT_TYPE_AI1_FIFO 134 
#define  INT_TYPE_AI1_INT 133 
#define  INT_TYPE_AI3_DMA 132 
#define  INT_TYPE_AI3_FIFO 131 
#define  INT_TYPE_AI3_INT 130 
#define  INT_TYPE_AO1_INT 129 
#define  INT_TYPE_AO3_INT 128 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PCL818_CLRINT ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  interrupt_pcl818_ai_mode13_dma (int,void*) ; 
 int /*<<< orphan*/  interrupt_pcl818_ai_mode13_fifo (int,void*) ; 
 int /*<<< orphan*/  interrupt_pcl818_ai_mode13_int (int,void*) ; 
 int /*<<< orphan*/  interrupt_pcl818_ao_mode13_int (int,void*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pcl818_ai_cancel (struct comedi_device*,struct comedi_subdevice*) ; 

__attribute__((used)) static irqreturn_t interrupt_pcl818(int irq, void *d)
{
	struct comedi_device *dev = d;

	if (!dev->attached) {
		comedi_error(dev, "premature interrupt");
		return IRQ_HANDLED;
	}
	/* printk("I\n"); */

	if (devpriv->irq_blocked && devpriv->irq_was_now_closed) {
		if ((devpriv->neverending_ai || (!devpriv->neverending_ai &&
						 devpriv->ai_act_scan > 0)) &&
		    (devpriv->ai_mode == INT_TYPE_AI1_DMA ||
		     devpriv->ai_mode == INT_TYPE_AI3_DMA)) {
			/* The cleanup from ai_cancel() has been delayed
			   until now because the card doesn't seem to like
			   being reprogrammed while a DMA transfer is in
			   progress.
			 */
			struct comedi_subdevice *s = dev->subdevices + 0;
			devpriv->ai_act_scan = 0;
			devpriv->neverending_ai = 0;
			pcl818_ai_cancel(dev, s);
		}

		outb(0, dev->iobase + PCL818_CLRINT);	/* clear INT request */

		return IRQ_HANDLED;
	}

	switch (devpriv->ai_mode) {
	case INT_TYPE_AI1_DMA:
	case INT_TYPE_AI3_DMA:
		return interrupt_pcl818_ai_mode13_dma(irq, d);
	case INT_TYPE_AI1_INT:
	case INT_TYPE_AI3_INT:
		return interrupt_pcl818_ai_mode13_int(irq, d);
	case INT_TYPE_AI1_FIFO:
	case INT_TYPE_AI3_FIFO:
		return interrupt_pcl818_ai_mode13_fifo(irq, d);
#ifdef PCL818_MODE13_AO
	case INT_TYPE_AO1_INT:
	case INT_TYPE_AO3_INT:
		return interrupt_pcl818_ao_mode13_int(irq, d);
#endif
	default:
		break;
	}

	outb(0, dev->iobase + PCL818_CLRINT);	/* clear INT request */

	if ((!dev->irq) || (!devpriv->irq_free) || (!devpriv->irq_blocked)
	    || (!devpriv->ai_mode)) {
		comedi_error(dev, "bad IRQ!");
		return IRQ_NONE;
	}

	comedi_error(dev, "IRQ from unknow source!");
	return IRQ_NONE;
}