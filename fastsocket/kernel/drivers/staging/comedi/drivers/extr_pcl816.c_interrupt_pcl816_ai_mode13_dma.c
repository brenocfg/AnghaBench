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
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* subdevices; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int next_dma_buf; int dma_runs_to_end; int* hwdmasize; int last_dma_run; int ai_poll_ptr; scalar_t__* dmabuf; int /*<<< orphan*/  dma; int /*<<< orphan*/ * hwdmaptr; scalar_t__ ai_neverending; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MODE_READ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PCL816_CLRINT ; 
 unsigned long claim_dma_lock () ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_count (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dma_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transfer_from_dma_buf (struct comedi_device*,struct comedi_subdevice*,short*,int,int) ; 

__attribute__((used)) static irqreturn_t interrupt_pcl816_ai_mode13_dma(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->subdevices + 0;
	int len, bufptr, this_dma_buf;
	unsigned long dma_flags;
	short *ptr;

	disable_dma(devpriv->dma);
	this_dma_buf = devpriv->next_dma_buf;

	if ((devpriv->dma_runs_to_end > -1) || devpriv->ai_neverending) {	/*  switch dma bufs */

		devpriv->next_dma_buf = 1 - devpriv->next_dma_buf;
		set_dma_mode(devpriv->dma, DMA_MODE_READ);
		dma_flags = claim_dma_lock();
/* clear_dma_ff (devpriv->dma); */
		set_dma_addr(devpriv->dma,
			     devpriv->hwdmaptr[devpriv->next_dma_buf]);
		if (devpriv->dma_runs_to_end) {
			set_dma_count(devpriv->dma,
				      devpriv->hwdmasize[devpriv->
							 next_dma_buf]);
		} else {
			set_dma_count(devpriv->dma, devpriv->last_dma_run);
		}
		release_dma_lock(dma_flags);
		enable_dma(devpriv->dma);
	}

	devpriv->dma_runs_to_end--;
	outb(0, dev->iobase + PCL816_CLRINT);	/* clear INT request */

	ptr = (short *)devpriv->dmabuf[this_dma_buf];

	len = (devpriv->hwdmasize[0] >> 1) - devpriv->ai_poll_ptr;
	bufptr = devpriv->ai_poll_ptr;
	devpriv->ai_poll_ptr = 0;

	transfer_from_dma_buf(dev, s, ptr, bufptr, len);
	return IRQ_HANDLED;
}