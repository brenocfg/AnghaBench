#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct fe_priv {int msi_flags; TYPE_2__* pci_dev; TYPE_1__* msi_x_entry; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int NV_MSI_ENABLED ; 
 int NV_MSI_X_ENABLED ; 
 int NV_MSI_X_VECTORS_MASK ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct fe_priv* get_nvpriv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_disable_msix (TYPE_2__*) ; 

__attribute__((used)) static void nv_free_irq(struct net_device *dev)
{
	struct fe_priv *np = get_nvpriv(dev);
	int i;

	if (np->msi_flags & NV_MSI_X_ENABLED) {
		for (i = 0; i < (np->msi_flags & NV_MSI_X_VECTORS_MASK); i++) {
			free_irq(np->msi_x_entry[i].vector, dev);
		}
		pci_disable_msix(np->pci_dev);
		np->msi_flags &= ~NV_MSI_X_ENABLED;
	} else {
		free_irq(np->pci_dev->irq, dev);
		if (np->msi_flags & NV_MSI_ENABLED) {
			pci_disable_msi(np->pci_dev);
			np->msi_flags &= ~NV_MSI_ENABLED;
		}
	}
}