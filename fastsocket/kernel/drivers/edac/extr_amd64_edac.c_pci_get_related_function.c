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
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {scalar_t__ number; } ;

/* Variables and functions */
 scalar_t__ PCI_SLOT (int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_device (unsigned int,unsigned int,struct pci_dev*) ; 

__attribute__((used)) static struct pci_dev *pci_get_related_function(unsigned int vendor,
						unsigned int device,
						struct pci_dev *related)
{
	struct pci_dev *dev = NULL;

	dev = pci_get_device(vendor, device, dev);
	while (dev) {
		if ((dev->bus->number == related->bus->number) &&
		    (PCI_SLOT(dev->devfn) == PCI_SLOT(related->devfn)))
			break;
		dev = pci_get_device(vendor, device, dev);
	}

	return dev;
}