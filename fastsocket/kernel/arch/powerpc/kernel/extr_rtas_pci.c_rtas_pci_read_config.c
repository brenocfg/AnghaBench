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
struct pci_dn {unsigned int devfn; } ;
struct pci_bus {int dummy; } ;
struct device_node {struct device_node* sibling; struct device_node* child; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 struct pci_dn* PCI_DN (struct device_node*) ; 
 scalar_t__ of_device_is_available (struct device_node*) ; 
 struct device_node* pci_bus_to_OF_node (struct pci_bus*) ; 
 int rtas_read_config (struct pci_dn*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtas_pci_read_config(struct pci_bus *bus,
				unsigned int devfn,
				int where, int size, u32 *val)
{
	struct device_node *busdn, *dn;

	busdn = pci_bus_to_OF_node(bus);

	/* Search only direct children of the bus */
	for (dn = busdn->child; dn; dn = dn->sibling) {
		struct pci_dn *pdn = PCI_DN(dn);
		if (pdn && pdn->devfn == devfn
		    && of_device_is_available(dn))
			return rtas_read_config(pdn, where, size, val);
	}

	return PCIBIOS_DEVICE_NOT_FOUND;
}