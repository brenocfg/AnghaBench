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
struct pci_dev {int dummy; } ;
struct ehci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*) ; 
 int pci_set_mwi (struct pci_dev*) ; 

__attribute__((used)) static int ehci_pci_reinit(struct ehci_hcd *ehci, struct pci_dev *pdev)
{
	int			retval;

	/* we expect static quirk code to handle the "extended capabilities"
	 * (currently just BIOS handoff) allowed starting with EHCI 0.96
	 */

	/* PCI Memory-Write-Invalidate cycle support is optional (uncommon) */
	retval = pci_set_mwi(pdev);
	if (!retval)
		ehci_dbg(ehci, "MWI active\n");

	return 0;
}