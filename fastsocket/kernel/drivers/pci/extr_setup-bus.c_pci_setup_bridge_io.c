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
struct pci_bus {struct resource** resource; int /*<<< orphan*/  subordinate; int /*<<< orphan*/  secondary; struct pci_dev* self; } ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int /*<<< orphan*/  PCI_IO_BASE ; 
 int /*<<< orphan*/  PCI_IO_BASE_UPPER16 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ pci_is_enabled (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcibios_resource_to_bus (struct pci_dev*,struct pci_bus_region*,struct resource*) ; 

__attribute__((used)) static void pci_setup_bridge_io(struct pci_bus *bus)
{
	struct pci_dev *bridge = bus->self;
	struct resource *res;
	struct pci_bus_region region;
	u32 l, io_upper16;

	if (pci_is_enabled(bridge))
		return;

	dev_info(&bridge->dev, "PCI bridge to [bus %02x-%02x]\n",
		 bus->secondary, bus->subordinate);

	/* Set up the top and bottom of the PCI I/O segment for this bus. */
	res = bus->resource[0];
	pcibios_resource_to_bus(bridge, &region, res);
	if (res->flags & IORESOURCE_IO) {
		pci_read_config_dword(bridge, PCI_IO_BASE, &l);
		l &= 0xffff0000;
		l |= (region.start >> 8) & 0x00f0;
		l |= region.end & 0xf000;
		/* Set up upper 16 bits of I/O base/limit. */
		io_upper16 = (region.end & 0xffff0000) | (region.start >> 16);
		dev_info(&bridge->dev, "  bridge window %pR\n", res);
	} else {
		/* Clear upper 16 bits of I/O base/limit. */
		io_upper16 = 0;
		l = 0x00f0;
		dev_info(&bridge->dev, "  bridge window [io  disabled]\n");
	}
	/* Temporarily disable the I/O range before updating PCI_IO_BASE. */
	pci_write_config_dword(bridge, PCI_IO_BASE_UPPER16, 0x0000ffff);
	/* Update lower 16 bits of I/O base/limit. */
	pci_write_config_dword(bridge, PCI_IO_BASE, l);
	/* Update upper 16 bits of I/O base/limit. */
	pci_write_config_dword(bridge, PCI_IO_BASE_UPPER16, io_upper16);
}