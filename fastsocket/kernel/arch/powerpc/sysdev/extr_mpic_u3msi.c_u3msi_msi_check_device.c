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

/* Variables and functions */
 int ENXIO ; 
 int PCI_CAP_ID_MSIX ; 
 scalar_t__ find_ht_magic_addr (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int u3msi_msi_check_device(struct pci_dev *pdev, int nvec, int type)
{
	if (type == PCI_CAP_ID_MSIX)
		pr_debug("u3msi: MSI-X untested, trying anyway.\n");

	/* If we can't find a magic address then MSI ain't gonna work */
	if (find_ht_magic_addr(pdev) == 0) {
		pr_debug("u3msi: no magic address found for %s\n",
			 pci_name(pdev));
		return -ENXIO;
	}

	return 0;
}