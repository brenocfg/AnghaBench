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
struct pci_dev {TYPE_1__* resource; } ;
struct pci_controller {unsigned long io_offset; unsigned long mem_offset; } ;
struct pci_bus {scalar_t__ sysdata; } ;
struct TYPE_2__ {int flags; unsigned long end; scalar_t__ start; } ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM ; 
 int IORESOURCE_PCI_FIXED ; 
 int PCI_NUM_RESOURCES ; 

__attribute__((used)) static void pcibios_fixup_device_resources(struct pci_dev *dev,
	struct pci_bus *bus)
{
	/* Update device resources.  */
	struct pci_controller *hose = (struct pci_controller *)bus->sysdata;
	unsigned long offset = 0;
	int i;

	for (i = 0; i < PCI_NUM_RESOURCES; i++) {
		if (!dev->resource[i].start)
			continue;
		if (dev->resource[i].flags & IORESOURCE_PCI_FIXED)
			continue;
		if (dev->resource[i].flags & IORESOURCE_IO)
			offset = hose->io_offset;
		else if (dev->resource[i].flags & IORESOURCE_MEM)
			offset = hose->mem_offset;

		dev->resource[i].start += offset;
		dev->resource[i].end += offset;
	}
}