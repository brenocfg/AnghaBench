#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct resource {int flags; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct pci_bus_region {int start; int end; } ;
struct pci_bus {struct resource** resource; struct pci_dev* self; } ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  PCI_MEMORY_BASE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcibios_resource_to_bus (struct pci_dev*,struct pci_bus_region*,struct resource*) ; 

__attribute__((used)) static void pci_setup_bridge_mmio(struct pci_bus *bus)
{
	struct pci_dev *bridge = bus->self;
	struct resource *res;
	struct pci_bus_region region;
	u32 l;

	/* Set up the top and bottom of the PCI Memory segment for this bus. */
	res = bus->resource[1];
	pcibios_resource_to_bus(bridge, &region, res);
	if (res->flags & IORESOURCE_MEM) {
		l = (region.start >> 16) & 0xfff0;
		l |= region.end & 0xfff00000;
		dev_info(&bridge->dev, "  bridge window %pR\n", res);
	} else {
		l = 0x0000fff0;
		dev_info(&bridge->dev, "  bridge window [mem disabled]\n");
	}
	pci_write_config_dword(bridge, PCI_MEMORY_BASE, l);
}