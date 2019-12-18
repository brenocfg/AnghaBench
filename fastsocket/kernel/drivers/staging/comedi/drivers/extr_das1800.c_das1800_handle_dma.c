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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {int irq_dma_bits; scalar_t__ dma_current; scalar_t__ dma0; scalar_t__ dma1; int /*<<< orphan*/  ai_buf0; int /*<<< orphan*/  dma_current_buf; int /*<<< orphan*/  ai_buf1; int /*<<< orphan*/  dma_transfer_size; } ;

/* Variables and functions */
 unsigned int CLEAR_INTR_MASK ; 
 scalar_t__ DAS1800_STATUS ; 
 unsigned int DMATC ; 
 int DMA_DUAL ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  das1800_flush_dma_channel (struct comedi_device*,struct comedi_subdevice*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  enable_dma (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_addr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_count (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void das1800_handle_dma(struct comedi_device *dev,
			       struct comedi_subdevice *s, unsigned int status)
{
	unsigned long flags;
	const int dual_dma = devpriv->irq_dma_bits & DMA_DUAL;

	flags = claim_dma_lock();
	das1800_flush_dma_channel(dev, s, devpriv->dma_current,
				  devpriv->dma_current_buf);
	/*  re-enable  dma channel */
	set_dma_addr(devpriv->dma_current,
		     virt_to_bus(devpriv->dma_current_buf));
	set_dma_count(devpriv->dma_current, devpriv->dma_transfer_size);
	enable_dma(devpriv->dma_current);
	release_dma_lock(flags);

	if (status & DMATC) {
		/*  clear DMATC interrupt bit */
		outb(CLEAR_INTR_MASK & ~DMATC, dev->iobase + DAS1800_STATUS);
		/*  switch dma channels for next time, if appropriate */
		if (dual_dma) {
			/*  read data from the other channel next time */
			if (devpriv->dma_current == devpriv->dma0) {
				devpriv->dma_current = devpriv->dma1;
				devpriv->dma_current_buf = devpriv->ai_buf1;
			} else {
				devpriv->dma_current = devpriv->dma0;
				devpriv->dma_current_buf = devpriv->ai_buf0;
			}
		}
	}

	return;
}