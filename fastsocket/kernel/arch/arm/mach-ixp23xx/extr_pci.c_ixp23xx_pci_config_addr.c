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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int IXP23XX_PCI_CFG0_VIRT ; 
 unsigned int IXP23XX_PCI_CFG1_VIRT ; 
 int PCI_FUNC (unsigned int) ; 
 int PCI_SLOT (unsigned int) ; 

__attribute__((used)) static u32
*ixp23xx_pci_config_addr(unsigned int bus_nr, unsigned int devfn, int where)
{
	u32 *paddress;

	/*
	 * Must be dword aligned
	 */
	where &= ~3;

	/*
	 * For top bus, generate type 0, else type 1
	 */
	if (!bus_nr) {
		if (PCI_SLOT(devfn) >= 8)
			return 0;

		paddress = (u32 *) (IXP23XX_PCI_CFG0_VIRT
				    | (1 << (PCI_SLOT(devfn) + 16))
				    | (PCI_FUNC(devfn) << 8) | where);
	} else {
		paddress = (u32 *) (IXP23XX_PCI_CFG1_VIRT
				    | (bus_nr << 16)
				    | (PCI_SLOT(devfn) << 11)
				    | (PCI_FUNC(devfn) << 8) | where);
	}

	return paddress;
}