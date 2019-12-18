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
struct comedi_device {scalar_t__ iobase; scalar_t__ irq; scalar_t__ private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dmabuf_pages; scalar_t__* dmabuf_virt; scalar_t__ pcidev; scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_disable (scalar_t__) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci9118_reset (struct comedi_device*) ; 
 int /*<<< orphan*/  pci_dev_put (scalar_t__) ; 

__attribute__((used)) static int pci9118_detach(struct comedi_device *dev)
{
	if (dev->private) {
		if (devpriv->valid)
			pci9118_reset(dev);
		if (dev->irq)
			free_irq(dev->irq, dev);
		if (devpriv->pcidev) {
			if (dev->iobase) {
				comedi_pci_disable(devpriv->pcidev);
			}
			pci_dev_put(devpriv->pcidev);
		}
		if (devpriv->dmabuf_virt[0])
			free_pages((unsigned long)devpriv->dmabuf_virt[0],
				   devpriv->dmabuf_pages[0]);
		if (devpriv->dmabuf_virt[1])
			free_pages((unsigned long)devpriv->dmabuf_virt[1],
				   devpriv->dmabuf_pages[1]);
	}

	return 0;
}