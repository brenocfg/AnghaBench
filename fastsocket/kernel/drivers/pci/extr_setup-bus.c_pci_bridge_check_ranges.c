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
typedef  scalar_t__ u16 ;
struct resource {int flags; } ;
struct pci_dev {scalar_t__ vendor; int device; struct resource* resource; } ;
struct pci_bus {struct pci_dev* self; } ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM ; 
 int IORESOURCE_MEM_64 ; 
 int IORESOURCE_PREFETCH ; 
 size_t PCI_BRIDGE_RESOURCES ; 
 int /*<<< orphan*/  PCI_IO_BASE ; 
 int /*<<< orphan*/  PCI_PREF_BASE_UPPER32 ; 
 int /*<<< orphan*/  PCI_PREF_MEMORY_BASE ; 
 int PCI_PREF_RANGE_TYPE_64 ; 
 int PCI_PREF_RANGE_TYPE_MASK ; 
 scalar_t__ PCI_VENDOR_ID_DEC ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pci_bridge_check_ranges(struct pci_bus *bus)
{
	u16 io;
	u32 pmem;
	struct pci_dev *bridge = bus->self;
	struct resource *b_res;

	b_res = &bridge->resource[PCI_BRIDGE_RESOURCES];
	b_res[1].flags |= IORESOURCE_MEM;

	pci_read_config_word(bridge, PCI_IO_BASE, &io);
	if (!io) {
		pci_write_config_word(bridge, PCI_IO_BASE, 0xf0f0);
		pci_read_config_word(bridge, PCI_IO_BASE, &io);
 		pci_write_config_word(bridge, PCI_IO_BASE, 0x0);
 	}
 	if (io)
		b_res[0].flags |= IORESOURCE_IO;
	/*  DECchip 21050 pass 2 errata: the bridge may miss an address
	    disconnect boundary by one PCI data phase.
	    Workaround: do not use prefetching on this device. */
	if (bridge->vendor == PCI_VENDOR_ID_DEC && bridge->device == 0x0001)
		return;
	pci_read_config_dword(bridge, PCI_PREF_MEMORY_BASE, &pmem);
	if (!pmem) {
		pci_write_config_dword(bridge, PCI_PREF_MEMORY_BASE,
					       0xfff0fff0);
		pci_read_config_dword(bridge, PCI_PREF_MEMORY_BASE, &pmem);
		pci_write_config_dword(bridge, PCI_PREF_MEMORY_BASE, 0x0);
	}
	if (pmem) {
		b_res[2].flags |= IORESOURCE_MEM | IORESOURCE_PREFETCH;
		if ((pmem & PCI_PREF_RANGE_TYPE_MASK) == PCI_PREF_RANGE_TYPE_64)
			b_res[2].flags |= IORESOURCE_MEM_64;
	}

	/* double check if bridge does support 64 bit pref */
	if (b_res[2].flags & IORESOURCE_MEM_64) {
		u32 mem_base_hi, tmp;
		pci_read_config_dword(bridge, PCI_PREF_BASE_UPPER32,
					 &mem_base_hi);
		pci_write_config_dword(bridge, PCI_PREF_BASE_UPPER32,
					       0xffffffff);
		pci_read_config_dword(bridge, PCI_PREF_BASE_UPPER32, &tmp);
		if (!tmp)
			b_res[2].flags &= ~IORESOURCE_MEM_64;
		pci_write_config_dword(bridge, PCI_PREF_BASE_UPPER32,
				       mem_base_hi);
	}
}