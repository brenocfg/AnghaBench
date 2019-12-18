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
struct sn_irq_info {size_t irq_irq; int /*<<< orphan*/  rcu; int /*<<< orphan*/  list; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {struct sn_irq_info* pdi_sn_irq_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  SN_PCIDEV_BUSSOFT (struct pci_dev*) ; 
 TYPE_1__* SN_PCIDEV_INFO (struct pci_dev*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq_vector (size_t) ; 
 int /*<<< orphan*/  kfree (struct sn_irq_info*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  sn_irq_info_free ; 
 int /*<<< orphan*/  sn_irq_info_lock ; 
 int /*<<< orphan*/ * sn_irq_lh ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_intr_pda (struct sn_irq_info*) ; 

void sn_irq_unfixup(struct pci_dev *pci_dev)
{
	struct sn_irq_info *sn_irq_info;

	/* Only cleanup IRQ stuff if this device has a host bus context */
	if (!SN_PCIDEV_BUSSOFT(pci_dev))
		return;

	sn_irq_info = SN_PCIDEV_INFO(pci_dev)->pdi_sn_irq_info;
	if (!sn_irq_info)
		return;
	if (!sn_irq_info->irq_irq) {
		kfree(sn_irq_info);
		return;
	}

	unregister_intr_pda(sn_irq_info);
	spin_lock(&sn_irq_info_lock);
	list_del_rcu(&sn_irq_info->list);
	spin_unlock(&sn_irq_info_lock);
	if (list_empty(sn_irq_lh[sn_irq_info->irq_irq]))
		free_irq_vector(sn_irq_info->irq_irq);
	call_rcu(&sn_irq_info->rcu, sn_irq_info_free);
	pci_dev_put(pci_dev);

}