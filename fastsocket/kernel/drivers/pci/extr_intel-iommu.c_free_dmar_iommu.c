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
struct intel_iommu {int gcmd; size_t seq_id; struct dmar_domain** domain_ids; struct dmar_domain** domains; scalar_t__ irq; int /*<<< orphan*/  cap; } ;
struct dmar_domain {scalar_t__ iommu_count; int flags; int /*<<< orphan*/  iommu_lock; } ;

/* Variables and functions */
 int DMA_GCMD_TE ; 
 int DOMAIN_FLAG_VIRTUAL_MACHINE ; 
 int cap_ndoms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int,struct dmar_domain**) ; 
 int /*<<< orphan*/  destroy_irq (scalar_t__) ; 
 int /*<<< orphan*/  domain_exit (struct dmar_domain*) ; 
 int find_first_bit (struct dmar_domain**,int) ; 
 int find_next_bit (struct dmar_domain**,int,int) ; 
 int /*<<< orphan*/  free_context_table (struct intel_iommu*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct intel_iommu*) ; 
 struct dmar_domain** g_iommus ; 
 int g_num_of_iommus ; 
 int /*<<< orphan*/  iommu_disable_translation (struct intel_iommu*) ; 
 int /*<<< orphan*/  kfree (struct dmar_domain**) ; 
 int /*<<< orphan*/  set_irq_data (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vm_domain_exit (struct dmar_domain*) ; 

void free_dmar_iommu(struct intel_iommu *iommu)
{
	struct dmar_domain *domain;
	int i;
	unsigned long flags;

	if ((iommu->domains) && (iommu->domain_ids)) {
		i = find_first_bit(iommu->domain_ids, cap_ndoms(iommu->cap));
		for (; i < cap_ndoms(iommu->cap); ) {
			domain = iommu->domains[i];
			clear_bit(i, iommu->domain_ids);

			spin_lock_irqsave(&domain->iommu_lock, flags);
			if (--domain->iommu_count == 0) {
				if (domain->flags & DOMAIN_FLAG_VIRTUAL_MACHINE)
					vm_domain_exit(domain);
				else
					domain_exit(domain);
			}
			spin_unlock_irqrestore(&domain->iommu_lock, flags);

			i = find_next_bit(iommu->domain_ids,
				cap_ndoms(iommu->cap), i+1);
		}
	}

	if (iommu->gcmd & DMA_GCMD_TE)
		iommu_disable_translation(iommu);

	if (iommu->irq) {
		set_irq_data(iommu->irq, NULL);
		/* This will mask the irq */
		free_irq(iommu->irq, iommu);
		destroy_irq(iommu->irq);
	}

	kfree(iommu->domains);
	kfree(iommu->domain_ids);

	g_iommus[iommu->seq_id] = NULL;

	/* if all iommus are freed, free g_iommus */
	for (i = 0; i < g_num_of_iommus; i++) {
		if (g_iommus[i])
			break;
	}

	if (i == g_num_of_iommus)
		kfree(g_iommus);

	/* free context mapping */
	free_context_table(iommu);
}