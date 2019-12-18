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
struct intel_iommu {int /*<<< orphan*/  ecap; int /*<<< orphan*/  cap; } ;
struct dmar_domain {int gaw; int agaw; int iommu_coherency; int iommu_snooping; int iommu_count; struct dma_pte* pgd; int /*<<< orphan*/  devices; int /*<<< orphan*/  iommu_lock; int /*<<< orphan*/  iovad; } ;
struct dma_pte {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_32BIT_PFN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __iommu_flush_cache (struct intel_iommu*,struct dma_pte*,int /*<<< orphan*/ ) ; 
 scalar_t__ alloc_pgtable_page () ; 
 int cap_mgaw (int /*<<< orphan*/ ) ; 
 unsigned long cap_sagaw (int /*<<< orphan*/ ) ; 
 struct intel_iommu* domain_get_iommu (struct dmar_domain*) ; 
 int /*<<< orphan*/  domain_reserve_special_ranges (struct dmar_domain*) ; 
 scalar_t__ ecap_coherent (int /*<<< orphan*/ ) ; 
 scalar_t__ ecap_sc_support (int /*<<< orphan*/ ) ; 
 int find_next_bit (unsigned long*,int,int) ; 
 int guestwidth_to_adjustwidth (int) ; 
 int /*<<< orphan*/  init_iova_domain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 
 int width_to_agaw (int) ; 

__attribute__((used)) static int domain_init(struct dmar_domain *domain, int guest_width)
{
	struct intel_iommu *iommu;
	int adjust_width, agaw;
	unsigned long sagaw;

	init_iova_domain(&domain->iovad, DMA_32BIT_PFN);
	spin_lock_init(&domain->iommu_lock);

	domain_reserve_special_ranges(domain);

	/* calculate AGAW */
	iommu = domain_get_iommu(domain);
	if (guest_width > cap_mgaw(iommu->cap))
		guest_width = cap_mgaw(iommu->cap);
	domain->gaw = guest_width;
	adjust_width = guestwidth_to_adjustwidth(guest_width);
	agaw = width_to_agaw(adjust_width);
	sagaw = cap_sagaw(iommu->cap);
	if (!test_bit(agaw, &sagaw)) {
		/* hardware doesn't support it, choose a bigger one */
		pr_debug("IOMMU: hardware doesn't support agaw %d\n", agaw);
		agaw = find_next_bit(&sagaw, 5, agaw);
		if (agaw >= 5)
			return -ENODEV;
	}
	domain->agaw = agaw;
	INIT_LIST_HEAD(&domain->devices);

	if (ecap_coherent(iommu->ecap))
		domain->iommu_coherency = 1;
	else
		domain->iommu_coherency = 0;

	if (ecap_sc_support(iommu->ecap))
		domain->iommu_snooping = 1;
	else
		domain->iommu_snooping = 0;

	domain->iommu_count = 1;

	/* always allocate the top pgd */
	domain->pgd = (struct dma_pte *)alloc_pgtable_page();
	if (!domain->pgd)
		return -ENOMEM;
	__iommu_flush_cache(iommu, domain->pgd, PAGE_SIZE);
	return 0;
}