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
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 unsigned int PCI_BASE_ADDRESS_0 ; 
 int PCI_CLASS_STORAGE_SCSI ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_class (int,struct pci_dev*) ; 
 unsigned int pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static struct pci_dev *get_pci_dev(unsigned long port_base)
{
#if defined(CONFIG_PCI)
	unsigned int addr;
	struct pci_dev *dev = NULL;

	while ((dev = pci_get_class(PCI_CLASS_STORAGE_SCSI << 8, dev))) {
		addr = pci_resource_start(dev, 0);

#if defined(DEBUG_PCI_DETECT)
		printk("%s: get_pci_dev, bus %d, devfn 0x%x, addr 0x%x.\n",
		       driver_name, dev->bus->number, dev->devfn, addr);
#endif

		/* we are in so much trouble for a pci hotplug system with this driver
		 * anyway, so doing this at least lets people unload the driver and not
		 * cause memory problems, but in general this is a bad thing to do (this
		 * driver needs to be converted to the proper PCI api someday... */
		pci_dev_put(dev);
		if (addr + PCI_BASE_ADDRESS_0 == port_base)
			return dev;
	}
#endif				/* end CONFIG_PCI */
	return NULL;
}