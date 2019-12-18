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
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_ACCESS_READ ; 
 int /*<<< orphan*/  PCI_ACCESS_WRITE ; 
 int /*<<< orphan*/  nile4_pci_lock ; 
 int nile4_pcibios_config_access (int /*<<< orphan*/ ,struct pci_bus*,unsigned int,int,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nile4_pcibios_write(struct pci_bus *bus, unsigned int devfn,
	int where, int size, u32 val)
{
	unsigned long flags;
	u32 data = 0;
	int err;

	if ((size == 2) && (where & 1))
		return PCIBIOS_BAD_REGISTER_NUMBER;
	else if ((size == 4) && (where & 3))
		return PCIBIOS_BAD_REGISTER_NUMBER;

	spin_lock_irqsave(&nile4_pci_lock, flags);
	err = nile4_pcibios_config_access(PCI_ACCESS_READ, bus, devfn, where,
					  &data);
	spin_unlock_irqrestore(&nile4_pci_lock, flags);

	if (err)
		return err;

	if (size == 1)
		data = (data & ~(0xff << ((where & 3) << 3))) |
		    (val << ((where & 3) << 3));
	else if (size == 2)
		data = (data & ~(0xffff << ((where & 3) << 3))) |
		    (val << ((where & 3) << 3));
	else
		data = val;

	if (nile4_pcibios_config_access
	    (PCI_ACCESS_WRITE, bus, devfn, where, &data))
		return -1;

	return PCIBIOS_SUCCESSFUL;
}