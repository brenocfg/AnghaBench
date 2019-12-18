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
typedef  int uint32_t ;
typedef  int u32 ;
struct pci_bus {int number; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int PCI_FUNC (unsigned int) ; 
 int PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  TITAN_PCI_0_CONFIG_ADDRESS ; 
 int /*<<< orphan*/  TITAN_PCI_0_CONFIG_DATA ; 
 int /*<<< orphan*/  ocd_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocd_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocd_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int titan_write_config(struct pci_bus *bus, unsigned int devfn, int reg,
	int size, u32 val)
{
	uint32_t address;
	int dev, busno, func;

	busno = bus->number;
	dev = PCI_SLOT(devfn);
	func = PCI_FUNC(devfn);

	address = (busno << 16) | (dev << 11) | (func << 8) |
		(reg & 0xfc) | 0x80000000;

	/* start the configuration cycle */
	ocd_writel(address, TITAN_PCI_0_CONFIG_ADDRESS);

	/* write the data */
	switch (size) {
	case 1:
		ocd_writeb(val, TITAN_PCI_0_CONFIG_DATA + (~reg & 0x3));
		break;

	case 2:
		ocd_writew(val, TITAN_PCI_0_CONFIG_DATA + (~reg & 0x2));
		break;

	case 4:
		ocd_writel(val, TITAN_PCI_0_CONFIG_DATA);
		break;
	}

	return PCIBIOS_SUCCESSFUL;
}