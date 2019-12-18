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
struct dmar_domain {int gaw; struct dma_pte* pgd; scalar_t__ max_addr; scalar_t__ iommu_snooping; scalar_t__ iommu_coherency; scalar_t__ iommu_count; int /*<<< orphan*/  devices; int /*<<< orphan*/  agaw; int /*<<< orphan*/  iommu_lock; int /*<<< orphan*/  iovad; } ;
struct dma_pte {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_32BIT_PFN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ alloc_pgtable_page () ; 
 int /*<<< orphan*/  domain_flush_cache (struct dmar_domain*,struct dma_pte*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  domain_reserve_special_ranges (struct dmar_domain*) ; 
 int guestwidth_to_adjustwidth (int) ; 
 int /*<<< orphan*/  init_iova_domain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  width_to_agaw (int) ; 

__attribute__((used)) static int md_domain_init(struct dmar_domain *domain, int guest_width)
{
	int adjust_width;

	init_iova_domain(&domain->iovad, DMA_32BIT_PFN);
	spin_lock_init(&domain->iommu_lock);

	domain_reserve_special_ranges(domain);

	/* calculate AGAW */
	domain->gaw = guest_width;
	adjust_width = guestwidth_to_adjustwidth(guest_width);
	domain->agaw = width_to_agaw(adjust_width);

	INIT_LIST_HEAD(&domain->devices);

	domain->iommu_count = 0;
	domain->iommu_coherency = 0;
	domain->iommu_snooping = 0;
	domain->max_addr = 0;

	/* always allocate the top pgd */
	domain->pgd = (struct dma_pte *)alloc_pgtable_page();
	if (!domain->pgd)
		return -ENOMEM;
	domain_flush_cache(domain, domain->pgd, PAGE_SIZE);
	return 0;
}