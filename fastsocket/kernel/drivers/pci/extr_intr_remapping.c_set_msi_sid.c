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
struct pci_dev {int devfn; TYPE_1__* bus; } ;
struct irte {int dummy; } ;
struct TYPE_2__ {int number; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQ_ALL_16 ; 
 int /*<<< orphan*/  SVT_VERIFY_BUS ; 
 int /*<<< orphan*/  SVT_VERIFY_SID_SQ ; 
 struct pci_dev* pci_find_upstream_pcie_bridge (struct pci_dev*) ; 
 scalar_t__ pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  set_irte_sid (struct irte*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int set_msi_sid(struct irte *irte, struct pci_dev *dev)
{
	struct pci_dev *bridge;

	if (!irte || !dev)
		return -1;

	/* PCIe device or Root Complex integrated PCI device */
	if (pci_is_pcie(dev) || !dev->bus->parent) {
		set_irte_sid(irte, SVT_VERIFY_SID_SQ, SQ_ALL_16,
			     (dev->bus->number << 8) | dev->devfn);
		return 0;
	}

	bridge = pci_find_upstream_pcie_bridge(dev);
	if (bridge) {
		if (pci_is_pcie(bridge))/* this is a PCIe-to-PCI/PCIX bridge */
			set_irte_sid(irte, SVT_VERIFY_BUS, SQ_ALL_16,
				(bridge->bus->number << 8) | dev->bus->number);
		else /* this is a legacy PCI bridge */
			set_irte_sid(irte, SVT_VERIFY_SID_SQ, SQ_ALL_16,
				(bridge->bus->number << 8) | bridge->devfn);
	}

	return 0;
}