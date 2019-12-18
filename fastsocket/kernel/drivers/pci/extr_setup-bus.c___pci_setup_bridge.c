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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct pci_bus {int /*<<< orphan*/  bridge_ctl; int /*<<< orphan*/  subordinate; int /*<<< orphan*/  secondary; struct pci_dev* self; } ;

/* Variables and functions */
 unsigned long IORESOURCE_IO ; 
 unsigned long IORESOURCE_MEM ; 
 unsigned long IORESOURCE_PREFETCH ; 
 int /*<<< orphan*/  PCI_BRIDGE_CONTROL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_setup_bridge_io (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_setup_bridge_mmio (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_setup_bridge_mmio_pref (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __pci_setup_bridge(struct pci_bus *bus, unsigned long type)
{
	struct pci_dev *bridge = bus->self;

	dev_info(&bridge->dev, "PCI bridge to [bus %02x-%02x]\n",
		 bus->secondary, bus->subordinate);

	if (type & IORESOURCE_IO)
		pci_setup_bridge_io(bus);

	if (type & IORESOURCE_MEM)
		pci_setup_bridge_mmio(bus);

	if (type & IORESOURCE_PREFETCH)
		pci_setup_bridge_mmio_pref(bus);
 
	pci_write_config_word(bridge, PCI_BRIDGE_CONTROL, bus->bridge_ctl);
}