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
struct comedi_device {scalar_t__ iobase; scalar_t__ irq; scalar_t__ subdevices; int /*<<< orphan*/  minor; } ;
struct TYPE_4__ {scalar_t__ user_ao_range_table; scalar_t__ user_ai_range_table; scalar_t__ dma_chan; int /*<<< orphan*/ * dma_buffer_addr; scalar_t__* dma_buffer; } ;
struct TYPE_3__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAS16_DMA_SIZE ; 
 int /*<<< orphan*/  das16_reset (struct comedi_device*) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  subdev_8255_cleanup (struct comedi_device*,scalar_t__) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int das16_detach(struct comedi_device *dev)
{
	printk("comedi%d: das16: remove\n", dev->minor);

	das16_reset(dev);

	if (dev->subdevices)
		subdev_8255_cleanup(dev, dev->subdevices + 4);

	if (devpriv) {
		int i;
		for (i = 0; i < 2; i++) {
			if (devpriv->dma_buffer[i])
				pci_free_consistent(NULL, DAS16_DMA_SIZE,
						    devpriv->dma_buffer[i],
						    devpriv->
						    dma_buffer_addr[i]);
		}
		if (devpriv->dma_chan)
			free_dma(devpriv->dma_chan);
		if (devpriv->user_ai_range_table)
			kfree(devpriv->user_ai_range_table);
		if (devpriv->user_ao_range_table)
			kfree(devpriv->user_ao_range_table);
	}

	if (dev->irq)
		free_irq(dev->irq, dev);

	if (dev->iobase) {
		if (thisboard->size < 0x400) {
			release_region(dev->iobase, thisboard->size);
		} else {
			release_region(dev->iobase, 0x10);
			release_region(dev->iobase + 0x400,
				       thisboard->size & 0x3ff);
		}
	}

	return 0;
}