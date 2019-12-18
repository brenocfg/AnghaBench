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
struct TYPE_4__ {scalar_t__ mite; scalar_t__ dma_chan; scalar_t__ dma_buffer; } ;
struct TYPE_3__ {scalar_t__ bustype; } ;

/* Variables and functions */
 int /*<<< orphan*/  LABPC_SIZE ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 scalar_t__ isa_bustype ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  mite_unsetup (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subdev_8255_cleanup (struct comedi_device*,scalar_t__) ; 
 TYPE_1__* thisboard ; 

int labpc_common_detach(struct comedi_device *dev)
{
	printk("comedi%d: ni_labpc: detach\n", dev->minor);

	if (dev->subdevices)
		subdev_8255_cleanup(dev, dev->subdevices + 2);

	/* only free stuff if it has been allocated by _attach */
	if (devpriv->dma_buffer)
		kfree(devpriv->dma_buffer);
	if (devpriv->dma_chan)
		free_dma(devpriv->dma_chan);
	if (dev->irq)
		free_irq(dev->irq, dev);
	if (thisboard->bustype == isa_bustype && dev->iobase)
		release_region(dev->iobase, LABPC_SIZE);
#ifdef CONFIG_COMEDI_PCI
	if (devpriv->mite)
		mite_unsetup(devpriv->mite);
#endif

	return 0;
}