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
typedef  size_t u16 ;
struct protection_domain {scalar_t__ dev_cnt; int /*<<< orphan*/  id; int /*<<< orphan*/  lock; } ;
struct amd_iommu {int dummy; } ;
struct TYPE_2__ {int* data; } ;

/* Variables and functions */
 int IOMMU_PTE_P ; 
 int IOMMU_PTE_TV ; 
 int /*<<< orphan*/  __attach_device (struct amd_iommu*,struct protection_domain*,size_t) ; 
 int /*<<< orphan*/  amd_iommu_apply_erratum_63 (size_t) ; 
 TYPE_1__* amd_iommu_dev_table ; 
 int /*<<< orphan*/ ** amd_iommu_pd_table ; 
 struct amd_iommu** amd_iommu_rlookup_table ; 
 int /*<<< orphan*/  iommu_completion_wait (struct amd_iommu*) ; 
 int /*<<< orphan*/  iommu_flush_tlb_pde (struct amd_iommu*,int /*<<< orphan*/ ) ; 
 scalar_t__ iommu_pass_through ; 
 int /*<<< orphan*/  iommu_queue_inv_dev_entry (struct amd_iommu*,size_t) ; 
 struct protection_domain* pt_domain ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __detach_device(struct protection_domain *domain, u16 devid)
{
	struct amd_iommu *iommu = amd_iommu_rlookup_table[devid];

	/* lock domain */
	spin_lock(&domain->lock);

	/* remove domain from the lookup table */
	amd_iommu_pd_table[devid] = NULL;

	/* remove entry from the device table seen by the hardware */
	amd_iommu_dev_table[devid].data[0] = IOMMU_PTE_P | IOMMU_PTE_TV;
	amd_iommu_dev_table[devid].data[1] = 0;
	amd_iommu_dev_table[devid].data[2] = 0;

	amd_iommu_apply_erratum_63(devid);

	/* decrease reference counter */
	domain->dev_cnt -= 1;

	/* ready */
	spin_unlock(&domain->lock);

	/*
	 * If we run in passthrough mode the device must be assigned to the
	 * passthrough domain if it is detached from any other domain.
	 * Make sure we can deassign from the pt_domain itself.
	 */
	if (iommu_pass_through && domain != pt_domain)
		__attach_device(iommu, pt_domain, devid);

	iommu_queue_inv_dev_entry(iommu, devid);
	if (domain->dev_cnt == 0)
		iommu_flush_tlb_pde(iommu, domain->id);
	iommu_completion_wait(iommu);
}