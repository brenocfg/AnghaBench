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
struct pci_dev_rh1 {int /*<<< orphan*/ * msi_kset; } ;
struct pci_dev {int /*<<< orphan*/  msix_enabled; struct pci_dev_rh1* rh_reserved1; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_msi_irqs (struct pci_dev*) ; 
 int /*<<< orphan*/  kset_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_msi_enable ; 
 int /*<<< orphan*/  pci_msix_shutdown (struct pci_dev*) ; 

void pci_disable_msix(struct pci_dev *dev)
{
	struct pci_dev_rh1 *pdr = dev->rh_reserved1;

	if (!pci_msi_enable || !dev || !dev->msix_enabled)
		return;

	pci_msix_shutdown(dev);
	free_msi_irqs(dev);
	if (pdr && pdr->msi_kset) {
		kset_unregister(pdr->msi_kset);
		pdr->msi_kset = NULL;
	}
}