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
typedef  int u16 ;
struct resource {int end; int flags; scalar_t__ start; } ;
struct pci_dev {struct resource* resource; } ;
struct pci_bus {struct pci_dev* self; } ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM ; 
 int IORESOURCE_PREFETCH ; 
 int IORESOURCE_SIZEALIGN ; 
 size_t PCI_BRIDGE_RESOURCES ; 
 int /*<<< orphan*/  PCI_CB_BRIDGE_CONTROL ; 
 int PCI_CB_BRIDGE_CTL_PREFETCH_MEM0 ; 
 void* pci_cardbus_io_size ; 
 int pci_cardbus_mem_size ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pci_bus_size_cardbus(struct pci_bus *bus)
{
	struct pci_dev *bridge = bus->self;
	struct resource *b_res = &bridge->resource[PCI_BRIDGE_RESOURCES];
	u16 ctrl;

	/*
	 * Reserve some resources for CardBus.  We reserve
	 * a fixed amount of bus space for CardBus bridges.
	 */
	b_res[0].start = 0;
	b_res[0].end = pci_cardbus_io_size - 1;
	b_res[0].flags |= IORESOURCE_IO | IORESOURCE_SIZEALIGN;

	b_res[1].start = 0;
	b_res[1].end = pci_cardbus_io_size - 1;
	b_res[1].flags |= IORESOURCE_IO | IORESOURCE_SIZEALIGN;

	/*
	 * Check whether prefetchable memory is supported
	 * by this bridge.
	 */
	pci_read_config_word(bridge, PCI_CB_BRIDGE_CONTROL, &ctrl);
	if (!(ctrl & PCI_CB_BRIDGE_CTL_PREFETCH_MEM0)) {
		ctrl |= PCI_CB_BRIDGE_CTL_PREFETCH_MEM0;
		pci_write_config_word(bridge, PCI_CB_BRIDGE_CONTROL, ctrl);
		pci_read_config_word(bridge, PCI_CB_BRIDGE_CONTROL, &ctrl);
	}

	/*
	 * If we have prefetchable memory support, allocate
	 * two regions.  Otherwise, allocate one region of
	 * twice the size.
	 */
	if (ctrl & PCI_CB_BRIDGE_CTL_PREFETCH_MEM0) {
		b_res[2].start = 0;
		b_res[2].end = pci_cardbus_mem_size - 1;
		b_res[2].flags |= IORESOURCE_MEM | IORESOURCE_PREFETCH | IORESOURCE_SIZEALIGN;

		b_res[3].start = 0;
		b_res[3].end = pci_cardbus_mem_size - 1;
		b_res[3].flags |= IORESOURCE_MEM | IORESOURCE_SIZEALIGN;
	} else {
		b_res[3].start = 0;
		b_res[3].end = pci_cardbus_mem_size * 2 - 1;
		b_res[3].flags |= IORESOURCE_MEM | IORESOURCE_SIZEALIGN;
	}
}