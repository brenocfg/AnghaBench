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
typedef  int /*<<< orphan*/  u16 ;
struct protection_domain {int /*<<< orphan*/  id; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __attach_device (struct amd_iommu*,struct protection_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_iommu_devtable_lock ; 
 int /*<<< orphan*/  iommu_flush_tlb_pde (struct amd_iommu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_queue_inv_dev_entry (struct amd_iommu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void attach_device(struct amd_iommu *iommu,
			  struct protection_domain *domain,
			  u16 devid)
{
	unsigned long flags;

	write_lock_irqsave(&amd_iommu_devtable_lock, flags);
	__attach_device(iommu, domain, devid);
	write_unlock_irqrestore(&amd_iommu_devtable_lock, flags);

	/*
	 * We might boot into a crash-kernel here. The crashed kernel
	 * left the caches in the IOMMU dirty. So we have to flush
	 * here to evict all dirty stuff.
	 */
	iommu_queue_inv_dev_entry(iommu, devid);
	iommu_flush_tlb_pde(iommu, domain->id);
}