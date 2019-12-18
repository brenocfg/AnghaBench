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
struct pci_dev {unsigned int devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {unsigned int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ANY_ID ; 
 int pci_domain_nr (TYPE_1__*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 

struct pci_dev *pci_get_domain_bus_and_slot(int domain, unsigned int bus,
					    unsigned int devfn)
{
	struct pci_dev *dev = NULL;

	while ((dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, dev)) != NULL) {
		if (pci_domain_nr(dev->bus) == domain &&
		    (dev->bus->number == bus && dev->devfn == devfn))
			return dev;
	}
	return NULL;
}