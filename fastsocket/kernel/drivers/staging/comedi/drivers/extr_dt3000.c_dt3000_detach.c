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
struct comedi_device {scalar_t__ irq; } ;
struct TYPE_2__ {scalar_t__ io_addr; scalar_t__ pci_dev; scalar_t__ phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_disable (scalar_t__) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_dev_put (scalar_t__) ; 

__attribute__((used)) static int dt3000_detach(struct comedi_device *dev)
{
	if (dev->irq)
		free_irq(dev->irq, dev);

	if (devpriv) {
		if (devpriv->pci_dev) {
			if (devpriv->phys_addr) {
				comedi_pci_disable(devpriv->pci_dev);
			}
			pci_dev_put(devpriv->pci_dev);
		}
		if (devpriv->io_addr)
			iounmap(devpriv->io_addr);
	}
	/* XXX */

	return 0;
}