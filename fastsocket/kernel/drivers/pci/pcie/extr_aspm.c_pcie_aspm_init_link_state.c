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
struct pcie_link_state {int dummy; } ;
struct pci_dev {TYPE_2__* subordinate; TYPE_1__* bus; scalar_t__ link_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  devices; } ;
struct TYPE_3__ {scalar_t__ self; } ;

/* Variables and functions */
 scalar_t__ PCI_EXP_TYPE_DOWNSTREAM ; 
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 scalar_t__ POLICY_POWERSAVE ; 
 struct pcie_link_state* alloc_pcie_link_state (struct pci_dev*) ; 
 scalar_t__ aspm_clear_state ; 
 scalar_t__ aspm_disabled ; 
 int /*<<< orphan*/  aspm_lock ; 
 scalar_t__ aspm_policy ; 
 int /*<<< orphan*/  aspm_support_enabled ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_aspm_cap_init (struct pcie_link_state*,int) ; 
 int /*<<< orphan*/  pcie_aspm_sanity_check (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_clkpm_cap_init (struct pcie_link_state*,int) ; 
 int /*<<< orphan*/  pcie_config_aspm_path (struct pcie_link_state*) ; 
 int /*<<< orphan*/  pcie_set_clkpm (struct pcie_link_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_to_clkpm_state (struct pcie_link_state*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void pcie_aspm_init_link_state(struct pci_dev *pdev)
{
	struct pcie_link_state *link;
	int blacklist = !!pcie_aspm_sanity_check(pdev);

	if (!aspm_support_enabled)
		return;

	if (!pci_is_pcie(pdev) || pdev->link_state)
		return;
	if (pci_pcie_type(pdev) != PCI_EXP_TYPE_ROOT_PORT &&
	    pci_pcie_type(pdev) != PCI_EXP_TYPE_DOWNSTREAM)
		return;

	if (aspm_disabled && !aspm_clear_state)
		return;

	/* VIA has a strange chipset, root port is under a bridge */
	if (pci_pcie_type(pdev) == PCI_EXP_TYPE_ROOT_PORT &&
	    pdev->bus->self)
		return;

	down_read(&pci_bus_sem);
	if (list_empty(&pdev->subordinate->devices))
		goto out;

	mutex_lock(&aspm_lock);
	link = alloc_pcie_link_state(pdev);
	if (!link)
		goto unlock;
	/*
	 * Setup initial ASPM state. Note that we need to configure
	 * upstream links also because capable state of them can be
	 * update through pcie_aspm_cap_init().
	 */
	pcie_aspm_cap_init(link, blacklist);

	/* Setup initial Clock PM state */
	pcie_clkpm_cap_init(link, blacklist);

	/*
	 * At this stage drivers haven't had an opportunity to change the
	 * link policy setting. Enabling ASPM on broken hardware can cripple
	 * it even before the driver has had a chance to disable ASPM, so
	 * default to a safe level right now. If we're enabling ASPM beyond
	 * the BIOS's expectation, we'll do so once pci_enable_device() is
	 * called.
	 */
	if (aspm_policy != POLICY_POWERSAVE || aspm_clear_state) {
		pcie_config_aspm_path(link);
		pcie_set_clkpm(link, policy_to_clkpm_state(link));
	}

unlock:
	mutex_unlock(&aspm_lock);
out:
	up_read(&pci_bus_sem);
}