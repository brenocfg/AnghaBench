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
struct comedi_device {int /*<<< orphan*/  irq; scalar_t__ iobase; int /*<<< orphan*/  attached; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int int816_mode; scalar_t__ irq_was_now_closed; int /*<<< orphan*/  irq_blocked; int /*<<< orphan*/  irq_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
#define  INT_TYPE_AI1_DMA 131 
#define  INT_TYPE_AI1_INT 130 
#define  INT_TYPE_AI3_DMA 129 
#define  INT_TYPE_AI3_INT 128 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PCL816_CLRINT ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  interrupt_pcl816_ai_mode13_dma (int,void*) ; 
 int /*<<< orphan*/  interrupt_pcl816_ai_mode13_int (int,void*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t interrupt_pcl816(int irq, void *d)
{
	struct comedi_device *dev = d;
	DPRINTK("<I>");

	if (!dev->attached) {
		comedi_error(dev, "premature interrupt");
		return IRQ_HANDLED;
	}

	switch (devpriv->int816_mode) {
	case INT_TYPE_AI1_DMA:
	case INT_TYPE_AI3_DMA:
		return interrupt_pcl816_ai_mode13_dma(irq, d);
	case INT_TYPE_AI1_INT:
	case INT_TYPE_AI3_INT:
		return interrupt_pcl816_ai_mode13_int(irq, d);
	}

	outb(0, dev->iobase + PCL816_CLRINT);	/* clear INT request */
	if ((!dev->irq) | (!devpriv->irq_free) | (!devpriv->irq_blocked) |
	    (!devpriv->int816_mode)) {
		if (devpriv->irq_was_now_closed) {
			devpriv->irq_was_now_closed = 0;
			/*  comedi_error(dev,"last IRQ.."); */
			return IRQ_HANDLED;
		}
		comedi_error(dev, "bad IRQ!");
		return IRQ_NONE;
	}
	comedi_error(dev, "IRQ from unknow source!");
	return IRQ_NONE;
}