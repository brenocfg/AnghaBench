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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* subdevices; } ;
struct comedi_cmd {scalar_t__ stop_src; } ;
struct comedi_async {int events; struct comedi_cmd cmd; } ;
struct TYPE_2__ {int irq_dma_bits; scalar_t__ count; } ;

/* Variables and functions */
 unsigned int ADC ; 
 unsigned int CLEAR_INTR_MASK ; 
 int COMEDI_CB_BLOCK ; 
 int COMEDI_CB_EOA ; 
 int COMEDI_CB_ERROR ; 
 unsigned int CT0TC ; 
 scalar_t__ DAS1800_SELECT ; 
 scalar_t__ DAS1800_STATUS ; 
 int DMA_ENABLED ; 
 unsigned int FHF ; 
 unsigned int FNE ; 
 unsigned int OVF ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  das1800_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  das1800_flush_dma (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  das1800_handle_dma (struct comedi_device*,struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  das1800_handle_fifo_half_full (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  das1800_handle_fifo_not_empty (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_1__* devpriv ; 
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void das1800_ai_handler(struct comedi_device *dev)
{
	struct comedi_subdevice *s = dev->subdevices + 0;	/* analog input subdevice */
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int status = inb(dev->iobase + DAS1800_STATUS);

	async->events = 0;
	/*  select adc for base address + 0 */
	outb(ADC, dev->iobase + DAS1800_SELECT);
	/*  dma buffer full */
	if (devpriv->irq_dma_bits & DMA_ENABLED) {
		/*  look for data from dma transfer even if dma terminal count hasn't happened yet */
		das1800_handle_dma(dev, s, status);
	} else if (status & FHF) {	/*  if fifo half full */
		das1800_handle_fifo_half_full(dev, s);
	} else if (status & FNE) {	/*  if fifo not empty */
		das1800_handle_fifo_not_empty(dev, s);
	}

	async->events |= COMEDI_CB_BLOCK;
	/* if the card's fifo has overflowed */
	if (status & OVF) {
		/*  clear OVF interrupt bit */
		outb(CLEAR_INTR_MASK & ~OVF, dev->iobase + DAS1800_STATUS);
		comedi_error(dev, "DAS1800 FIFO overflow");
		das1800_cancel(dev, s);
		async->events |= COMEDI_CB_ERROR | COMEDI_CB_EOA;
		comedi_event(dev, s);
		return;
	}
	/*  stop taking data if appropriate */
	/* stop_src TRIG_EXT */
	if (status & CT0TC) {
		/*  clear CT0TC interrupt bit */
		outb(CLEAR_INTR_MASK & ~CT0TC, dev->iobase + DAS1800_STATUS);
		/*  make sure we get all remaining data from board before quitting */
		if (devpriv->irq_dma_bits & DMA_ENABLED)
			das1800_flush_dma(dev, s);
		else
			das1800_handle_fifo_not_empty(dev, s);
		das1800_cancel(dev, s);	/* disable hardware conversions */
		async->events |= COMEDI_CB_EOA;
	} else if (cmd->stop_src == TRIG_COUNT && devpriv->count == 0) {	/*  stop_src TRIG_COUNT */
		das1800_cancel(dev, s);	/* disable hardware conversions */
		async->events |= COMEDI_CB_EOA;
	}

	comedi_event(dev, s);

	return;
}