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
struct intel_iommu {int seq_id; int /*<<< orphan*/  lock; struct dmar_domain** domains; int /*<<< orphan*/  domain_ids; int /*<<< orphan*/  cap; } ;
struct dmar_domain {int /*<<< orphan*/  iommu_bmp; } ;

/* Variables and functions */
 int cap_ndoms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int find_first_bit (int /*<<< orphan*/ ,int) ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void iommu_detach_domain(struct dmar_domain *domain,
				struct intel_iommu *iommu)
{
	unsigned long flags;
	int num, ndomains;
	int found = 0;

	spin_lock_irqsave(&iommu->lock, flags);
	ndomains = cap_ndoms(iommu->cap);
	num = find_first_bit(iommu->domain_ids, ndomains);
	for (; num < ndomains; ) {
		if (iommu->domains[num] == domain) {
			found = 1;
			break;
		}
		num = find_next_bit(iommu->domain_ids,
				    cap_ndoms(iommu->cap), num+1);
	}

	if (found) {
		clear_bit(num, iommu->domain_ids);
		clear_bit(iommu->seq_id, domain->iommu_bmp);
		iommu->domains[num] = NULL;
	}
	spin_unlock_irqrestore(&iommu->lock, flags);
}