#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcie_link_state {int /*<<< orphan*/  link; int /*<<< orphan*/  sibling; struct pcie_link_state* parent; struct pcie_link_state* root; } ;
struct pci_dev {struct pcie_link_state* link_state; TYPE_2__* subordinate; int /*<<< orphan*/  bus_list; TYPE_1__* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  devices; } ;
struct TYPE_3__ {struct pci_dev* self; } ;

/* Variables and functions */
 scalar_t__ PCI_EXP_TYPE_DOWNSTREAM ; 
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 int /*<<< orphan*/  aspm_clear_state ; 
 scalar_t__ aspm_disabled ; 
 int /*<<< orphan*/  aspm_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_link_state (struct pcie_link_state*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_config_aspm_link (struct pcie_link_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_config_aspm_path (struct pcie_link_state*) ; 
 int /*<<< orphan*/  pcie_update_aspm_capable (struct pcie_link_state*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void pcie_aspm_exit_link_state(struct pci_dev *pdev)
{
	struct pci_dev *parent = pdev->bus->self;
	struct pcie_link_state *link, *root, *parent_link;

	if ((aspm_disabled && !aspm_clear_state) || !pci_is_pcie(pdev) ||
	    !parent || !parent->link_state)
		return;
	if ((pci_pcie_type(parent) != PCI_EXP_TYPE_ROOT_PORT) &&
	    (pci_pcie_type(parent) != PCI_EXP_TYPE_DOWNSTREAM))
		return;

	down_read(&pci_bus_sem);
	mutex_lock(&aspm_lock);
	/*
	 * All PCIe functions are in one slot, remove one function will remove
	 * the whole slot, so just wait until we are the last function left.
	 */
	if (!list_is_last(&pdev->bus_list, &parent->subordinate->devices))
		goto out;

	link = parent->link_state;
	root = link->root;
	parent_link = link->parent;

	/* All functions are removed, so just disable ASPM for the link */
	pcie_config_aspm_link(link, 0);
	list_del(&link->sibling);
	list_del(&link->link);
	/* Clock PM is for endpoint device */
	free_link_state(link);

	/* Recheck latencies and configure upstream links */
	if (parent_link) {
		pcie_update_aspm_capable(root);
		pcie_config_aspm_path(parent_link);
	}
out:
	mutex_unlock(&aspm_lock);
	up_read(&pci_bus_sem);
}