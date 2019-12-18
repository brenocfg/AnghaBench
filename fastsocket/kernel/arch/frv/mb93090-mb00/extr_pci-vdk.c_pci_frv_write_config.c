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
struct pci_bus {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CONFIG_CMD (struct pci_bus*,unsigned int,int) ; 
 int PCIBIOS_SUCCESSFUL ; 
 unsigned int PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_PciBridgeDataB (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_PciBridgeDataL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_PciBridgeDataW (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_PciCfgAddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_PciCfgDataB (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_PciCfgDataL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_PciCfgDataW (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_frv_write_config(struct pci_bus *bus, unsigned int devfn, int where, int size,
				u32 value)
{
	switch (size) {
	case 1:
		if (bus->number == 0 && devfn == PCI_DEVFN(0, 0)) {
			__set_PciBridgeDataB(where, value);
		}
		else {
			__set_PciCfgAddr(CONFIG_CMD(bus, devfn, where));
			__set_PciCfgDataB(where, value);
		}
		break;

	case 2:
		if (bus->number == 0 && devfn == PCI_DEVFN(0, 0)) {
			__set_PciBridgeDataW(where, value);
		}
		else {
			__set_PciCfgAddr(CONFIG_CMD(bus, devfn, where));
			__set_PciCfgDataW(where, value);
		}
		break;

	case 4:
		if (bus->number == 0 && devfn == PCI_DEVFN(0, 0)) {
			__set_PciBridgeDataL(where, value);
		}
		else {
			__set_PciCfgAddr(CONFIG_CMD(bus, devfn, where));
			__set_PciCfgDataL(where, value);
		}
		break;

	default:
		BUG();
	}

	return PCIBIOS_SUCCESSFUL;
}