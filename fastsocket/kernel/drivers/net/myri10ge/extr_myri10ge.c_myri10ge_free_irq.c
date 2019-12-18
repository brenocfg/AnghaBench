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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct myri10ge_priv {int num_slices; scalar_t__ msix_enabled; scalar_t__ msi_enabled; int /*<<< orphan*/ * ss; TYPE_1__* msix_vectors; struct pci_dev* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 

__attribute__((used)) static void myri10ge_free_irq(struct myri10ge_priv *mgp)
{
	struct pci_dev *pdev = mgp->pdev;
	int i;

	if (mgp->msix_enabled) {
		for (i = 0; i < mgp->num_slices; i++)
			free_irq(mgp->msix_vectors[i].vector, &mgp->ss[i]);
	} else {
		free_irq(pdev->irq, &mgp->ss[0]);
	}
	if (mgp->msi_enabled)
		pci_disable_msi(pdev);
	if (mgp->msix_enabled)
		pci_disable_msix(pdev);
}