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
 int PCIBIOS_SUCCESSFUL ; 
 int* bytemask ; 
 int* ixp2000_pci_config_addr (int /*<<< orphan*/ ,unsigned int,int) ; 
 scalar_t__ pci_master_aborts ; 

int ixp2000_pci_read_config(struct pci_bus *bus, unsigned int devfn, int where,
				int size, u32 *value)
{
	u32 n;
	u32 *addr;

	n = where % 4;

	addr = ixp2000_pci_config_addr(bus->number, devfn, where);
	if (!addr)
		return PCIBIOS_DEVICE_NOT_FOUND;

	pci_master_aborts = 0;
	*value = (*addr >> (8*n)) & bytemask[size];
	if (pci_master_aborts) {
		pci_master_aborts = 0;
		*value = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	return PCIBIOS_SUCCESSFUL;
}