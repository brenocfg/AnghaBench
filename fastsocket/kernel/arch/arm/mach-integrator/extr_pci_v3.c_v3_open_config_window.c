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
struct pci_bus {unsigned int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned long PCI_CONFIG_VADDR ; 
 int PCI_FUNC (unsigned int) ; 
 int PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  PHYS_PCI_CONFIG_BASE ; 
 int /*<<< orphan*/  PHYS_PCI_MEM_BASE ; 
 int /*<<< orphan*/  V3_LB_BASE0 ; 
 int /*<<< orphan*/  V3_LB_BASE1 ; 
 int V3_LB_BASE_ADR_SIZE_16MB ; 
 int V3_LB_BASE_ADR_SIZE_512MB ; 
 int V3_LB_BASE_ENABLE ; 
 int /*<<< orphan*/  V3_LB_MAP1 ; 
 unsigned int V3_LB_MAP_AD_LOW_EN ; 
 unsigned int V3_LB_MAP_TYPE_CONFIG ; 
 int v3_addr_to_lb_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v3_writel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v3_writew (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned long v3_open_config_window(struct pci_bus *bus,
					   unsigned int devfn, int offset)
{
	unsigned int address, mapaddress, busnr;

	busnr = bus->number;

	/*
	 * Trap out illegal values
	 */
	if (offset > 255)
		BUG();
	if (busnr > 255)
		BUG();
	if (devfn > 255)
		BUG();

	if (busnr == 0) {
		int slot = PCI_SLOT(devfn);

		/*
		 * local bus segment so need a type 0 config cycle
		 *
		 * build the PCI configuration "address" with one-hot in
		 * A31-A11
		 *
		 * mapaddress:
		 *  3:1 = config cycle (101)
		 *  0   = PCI A1 & A0 are 0 (0)
		 */
		address = PCI_FUNC(devfn) << 8;
		mapaddress = V3_LB_MAP_TYPE_CONFIG;

		if (slot > 12)
			/*
			 * high order bits are handled by the MAP register
			 */
			mapaddress |= 1 << (slot - 5);
		else
			/*
			 * low order bits handled directly in the address
			 */
			address |= 1 << (slot + 11);
	} else {
        	/*
		 * not the local bus segment so need a type 1 config cycle
		 *
		 * address:
		 *  23:16 = bus number
		 *  15:11 = slot number (7:3 of devfn)
		 *  10:8  = func number (2:0 of devfn)
		 *
		 * mapaddress:
		 *  3:1 = config cycle (101)
		 *  0   = PCI A1 & A0 from host bus (1)
		 */
		mapaddress = V3_LB_MAP_TYPE_CONFIG | V3_LB_MAP_AD_LOW_EN;
		address = (busnr << 16) | (devfn << 8);
	}

	/*
	 * Set up base0 to see all 512Mbytes of memory space (not
	 * prefetchable), this frees up base1 for re-use by
	 * configuration memory
	 */
	v3_writel(V3_LB_BASE0, v3_addr_to_lb_base(PHYS_PCI_MEM_BASE) |
			V3_LB_BASE_ADR_SIZE_512MB | V3_LB_BASE_ENABLE);

	/*
	 * Set up base1/map1 to point into configuration space.
	 */
	v3_writel(V3_LB_BASE1, v3_addr_to_lb_base(PHYS_PCI_CONFIG_BASE) |
			V3_LB_BASE_ADR_SIZE_16MB | V3_LB_BASE_ENABLE);
	v3_writew(V3_LB_MAP1, mapaddress);

	return PCI_CONFIG_VADDR + address + offset;
}