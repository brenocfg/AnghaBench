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
struct TYPE_2__ {scalar_t__ pcidev; scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_disable (scalar_t__) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  pci1710_reset (struct comedi_device*) ; 
 int /*<<< orphan*/  pci_dev_put (scalar_t__) ; 

__attribute__((used)) static int pci1710_detach(struct comedi_device *dev)
{

	if (dev->private) {
		if (devpriv->valid)
			pci1710_reset(dev);
		if (dev->irq)
			free_irq(dev->irq, dev);
		if (devpriv->pcidev) {
			if (dev->iobase) {
				comedi_pci_disable(devpriv->pcidev);
			}
			pci_dev_put(devpriv->pcidev);
		}
	}

	return 0;
}