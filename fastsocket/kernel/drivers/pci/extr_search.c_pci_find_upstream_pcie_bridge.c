#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 scalar_t__ PCI_EXP_TYPE_PCI_BRIDGE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pci_is_root_bus (TYPE_1__*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 

struct pci_dev *
pci_find_upstream_pcie_bridge(struct pci_dev *pdev)
{
	struct pci_dev *tmp = NULL;

	if (pci_is_pcie(pdev))
		return NULL;
	while (1) {
		if (pci_is_root_bus(pdev->bus))
			break;
		pdev = pdev->bus->self;
		/* a p2p bridge */
		if (!pci_is_pcie(pdev)) {
			tmp = pdev;
			continue;
		}
		/* PCI device should connect to a PCIe bridge */
		if (pci_pcie_type(pdev) != PCI_EXP_TYPE_PCI_BRIDGE) {
			/* Busted hardware? */
			WARN_ON_ONCE(1);
			return NULL;
		}
		return pdev;
	}

	return tmp;
}