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
typedef  int u64 ;
struct TYPE_2__ {struct iommu_domain* iommu_domain; } ;
struct kvm {TYPE_1__ arch; } ;
struct iommu_domain {int dummy; } ;
typedef  int pfn_t ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  gfn_to_gpa (int /*<<< orphan*/ ) ; 
 int iommu_iova_to_phys (struct iommu_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_unmap_range (struct iommu_domain*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  kvm_release_pfn_clean (int) ; 

__attribute__((used)) static void kvm_iommu_put_pages(struct kvm *kvm,
				gfn_t base_gfn, unsigned long npages)
{
	gfn_t gfn = base_gfn;
	pfn_t pfn;
	struct iommu_domain *domain = kvm->arch.iommu_domain;
	unsigned long i;
	u64 phys;

	/* check if iommu exists and in use */
	if (!domain)
		return;

	for (i = 0; i < npages; i++) {
		phys = iommu_iova_to_phys(domain, gfn_to_gpa(gfn));
		pfn = phys >> PAGE_SHIFT;
		kvm_release_pfn_clean(pfn);
		gfn++;
	}

	iommu_unmap_range(domain, gfn_to_gpa(base_gfn), PAGE_SIZE * npages);
}