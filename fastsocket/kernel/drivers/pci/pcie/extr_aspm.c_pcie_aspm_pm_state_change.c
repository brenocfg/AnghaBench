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
struct pcie_link_state {int /*<<< orphan*/  root; } ;
struct pci_dev {struct pcie_link_state* link_state; } ;

/* Variables and functions */
 scalar_t__ PCI_EXP_TYPE_DOWNSTREAM ; 
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 scalar_t__ aspm_disabled ; 
 int /*<<< orphan*/  aspm_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_config_aspm_path (struct pcie_link_state*) ; 
 int /*<<< orphan*/  pcie_update_aspm_capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void pcie_aspm_pm_state_change(struct pci_dev *pdev)
{
	struct pcie_link_state *link = pdev->link_state;

	if (aspm_disabled || !pci_is_pcie(pdev) || !link)
		return;
	if ((pci_pcie_type(pdev) != PCI_EXP_TYPE_ROOT_PORT) &&
	    (pci_pcie_type(pdev) != PCI_EXP_TYPE_DOWNSTREAM))
		return;
	/*
	 * Devices changed PM state, we should recheck if latency
	 * meets all functions' requirement
	 */
	down_read(&pci_bus_sem);
	mutex_lock(&aspm_lock);
	pcie_update_aspm_capable(link->root);
	pcie_config_aspm_path(link);
	mutex_unlock(&aspm_lock);
	up_read(&pci_bus_sem);
}