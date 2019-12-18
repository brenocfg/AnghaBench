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
struct pcie_link_state {scalar_t__ clkpm_capable; int /*<<< orphan*/  aspm_disable; } ;
struct pci_dev {struct pcie_link_state* link_state; TYPE_1__* bus; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPM_STATE_L0S ; 
 int /*<<< orphan*/  ASPM_STATE_L1 ; 
 int PCIE_LINK_STATE_CLKPM ; 
 int PCIE_LINK_STATE_L0S ; 
 int PCIE_LINK_STATE_L1 ; 
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
 int /*<<< orphan*/  pcie_config_aspm_link (struct pcie_link_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_set_clkpm (struct pcie_link_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_to_aspm_state (struct pcie_link_state*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __pci_disable_link_state(struct pci_dev *pdev, int state, bool sem)
{
	struct pci_dev *parent = pdev->bus->self;
	struct pcie_link_state *link;

	if (aspm_disabled || !pci_is_pcie(pdev))
		return;
	if (pci_pcie_type(pdev) == PCI_EXP_TYPE_ROOT_PORT ||
	    pci_pcie_type(pdev) == PCI_EXP_TYPE_DOWNSTREAM)
		parent = pdev;
	if (!parent || !parent->link_state)
		return;

	if (sem)
		down_read(&pci_bus_sem);
	mutex_lock(&aspm_lock);
	link = parent->link_state;
	if (state & PCIE_LINK_STATE_L0S)
		link->aspm_disable |= ASPM_STATE_L0S;
	if (state & PCIE_LINK_STATE_L1)
		link->aspm_disable |= ASPM_STATE_L1;
	pcie_config_aspm_link(link, policy_to_aspm_state(link));

	if (state & PCIE_LINK_STATE_CLKPM) {
		link->clkpm_capable = 0;
		pcie_set_clkpm(link, 0);
	}
	mutex_unlock(&aspm_lock);
	if (sem)
		up_read(&pci_bus_sem);
}