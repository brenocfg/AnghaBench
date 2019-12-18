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
struct amd_iommu {int need_sync; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __iommu_completion_wait (struct amd_iommu*) ; 
 int /*<<< orphan*/  __iommu_wait_for_completion (struct amd_iommu*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int iommu_completion_wait(struct amd_iommu *iommu)
{
	int ret = 0;
	unsigned long flags;

	spin_lock_irqsave(&iommu->lock, flags);

	if (!iommu->need_sync)
		goto out;

	ret = __iommu_completion_wait(iommu);

	iommu->need_sync = false;

	if (ret)
		goto out;

	__iommu_wait_for_completion(iommu);

out:
	spin_unlock_irqrestore(&iommu->lock, flags);

	return 0;
}