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
struct pci_bus {int /*<<< orphan*/  number; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_ACCESS_READ ; 
 int /*<<< orphan*/  PCI_ACCESS_WRITE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int,int,int,unsigned long) ; 
 int sh7786_pcie_config_access (int /*<<< orphan*/ ,struct pci_bus*,unsigned int,int,int*) ; 
 int /*<<< orphan*/  sh7786_pcie_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sh7786_pcie_write(struct pci_bus *bus, unsigned int devfn,
			     int where, int size, u32 val)
{
	unsigned long flags;
	int shift, ret;
	u32 data;

        if ((size == 2) && (where & 1))
		return PCIBIOS_BAD_REGISTER_NUMBER;
	else if ((size == 4) && (where & 3))
		return PCIBIOS_BAD_REGISTER_NUMBER;

	spin_lock_irqsave(&sh7786_pcie_lock, flags);
	ret = sh7786_pcie_config_access(PCI_ACCESS_READ, bus,
					devfn, where, &data);
	if (ret != PCIBIOS_SUCCESSFUL)
		goto out;

	dev_dbg(&bus->dev, "pcie-config-write: bus=%3d devfn=0x%04x "
		"where=0x%04x size=%d val=%08lx\n", bus->number,
		devfn, where, size, (unsigned long)val);

	if (size == 1) {
		shift = (where & 3) << 3;
		data &= ~(0xff << shift);
		data |= ((val & 0xff) << shift);
	} else if (size == 2) {
		shift = (where & 2) << 3;
		data &= ~(0xffff << shift);
		data |= ((val & 0xffff) << shift);
	} else
		data = val;

	ret = sh7786_pcie_config_access(PCI_ACCESS_WRITE, bus,
					devfn, where, &data);
out:
	spin_unlock_irqrestore(&sh7786_pcie_lock, flags);
	return ret;
}