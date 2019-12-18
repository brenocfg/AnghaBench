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
struct pci_channel {int dummy; } ;
struct pci_bus {int number; struct pci_channel* sysdata; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_FUNC_NOT_SUPPORTED ; 
 int PCIBIOS_SUCCESSFUL ; 
 unsigned char PCI_ACCESS_READ ; 
 int PCI_FUNC (unsigned int) ; 
 int PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  SH4A_PCIEPAR ; 
 int /*<<< orphan*/  SH4A_PCIEPCICONF1 ; 
 int /*<<< orphan*/  SH4A_PCIEPCTLR ; 
 int /*<<< orphan*/  SH4A_PCIEPDR ; 
 int pci_read_reg (struct pci_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_reg (struct pci_channel*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh7786_pcie_config_access(unsigned char access_type,
		struct pci_bus *bus, unsigned int devfn, int where, u32 *data)
{
	struct pci_channel *chan = bus->sysdata;
	int dev, func;

	dev = PCI_SLOT(devfn);
	func = PCI_FUNC(devfn);

	if (bus->number > 255 || dev > 31 || func > 7)
		return PCIBIOS_FUNC_NOT_SUPPORTED;
	if (devfn)
		return PCIBIOS_DEVICE_NOT_FOUND;

	/* Set the PIO address */
	pci_write_reg(chan, (bus->number << 24) | (dev << 19) |
				(func << 16) | (where & ~3), SH4A_PCIEPAR);

	/* Enable the configuration access */
	pci_write_reg(chan, (1 << 31), SH4A_PCIEPCTLR);

	if (access_type == PCI_ACCESS_READ)
		*data = pci_read_reg(chan, SH4A_PCIEPDR);
	else
		pci_write_reg(chan, *data, SH4A_PCIEPDR);

	/* Check for master and target aborts */
	if (pci_read_reg(chan, SH4A_PCIEPCICONF1) & ((1 << 29) | (1 << 28)))
		return PCIBIOS_DEVICE_NOT_FOUND;

	return PCIBIOS_SUCCESSFUL;
}