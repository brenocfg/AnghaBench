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
struct pci_bus {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int /*<<< orphan*/  PCIE_BASE ; 
 int /*<<< orphan*/  PCI_SLOT (int) ; 
 int /*<<< orphan*/  kirkwood_pcie_lock ; 
 int orion_pcie_rd_conf (int /*<<< orphan*/ ,struct pci_bus*,int,int,int,int*) ; 
 scalar_t__ pcie_valid_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pcie_rd_conf(struct pci_bus *bus, u32 devfn, int where,
			int size, u32 *val)
{
	unsigned long flags;
	int ret;

	if (pcie_valid_config(bus->number, PCI_SLOT(devfn)) == 0) {
		*val = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	spin_lock_irqsave(&kirkwood_pcie_lock, flags);
	ret = orion_pcie_rd_conf(PCIE_BASE, bus, devfn, where, size, val);
	spin_unlock_irqrestore(&kirkwood_pcie_lock, flags);

	return ret;
}