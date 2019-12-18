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

/* Variables and functions */
 int /*<<< orphan*/  RTAS_CHANGE_FN ; 
 int /*<<< orphan*/  RTAS_CHANGE_MSI_FN ; 
 struct pci_dn* get_pdn (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ rtas_change_msi (struct pci_dn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtas_disable_msi(struct pci_dev *pdev)
{
	struct pci_dn *pdn;

	pdn = get_pdn(pdev);
	if (!pdn)
		return;

	/*
	 * disabling MSI with the explicit interface also disables MSI-X
	 */
	if (rtas_change_msi(pdn, RTAS_CHANGE_MSI_FN, 0) != 0) {
		/* 
		 * may have failed because explicit interface is not
		 * present
		 */
		if (rtas_change_msi(pdn, RTAS_CHANGE_FN, 0) != 0) {
			pr_debug("rtas_msi: Setting MSIs to 0 failed!\n");
		}
	}
}