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
struct pci_dn {int dummy; } ;
struct pci_dev {int dummy; } ;
struct device_node {int dummy; } ;
typedef  enum pcie_reset_state { ____Placeholder_pcie_reset_state } pcie_reset_state ;

/* Variables and functions */
 int EINVAL ; 
 struct pci_dn* PCI_DN (struct device_node*) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 
#define  pcie_deassert_reset 130 
#define  pcie_hot_reset 129 
#define  pcie_warm_reset 128 
 int /*<<< orphan*/  rtas_pci_slot_reset (struct pci_dn*,int) ; 

int pcibios_set_pcie_reset_state(struct pci_dev *dev, enum pcie_reset_state state)
{
	struct device_node *dn = pci_device_to_OF_node(dev);
	struct pci_dn *pdn = PCI_DN(dn);

	switch (state) {
	case pcie_deassert_reset:
		rtas_pci_slot_reset(pdn, 0);
		break;
	case pcie_hot_reset:
		rtas_pci_slot_reset(pdn, 1);
		break;
	case pcie_warm_reset:
		rtas_pci_slot_reset(pdn, 3);
		break;
	default:
		return -EINVAL;
	};

	return 0;
}