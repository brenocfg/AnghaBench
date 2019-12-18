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
struct iommu_cmd {int dummy; } ;
struct amd_iommu {int need_sync; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __iommu_queue_command (struct amd_iommu*,struct iommu_cmd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int iommu_queue_command(struct amd_iommu *iommu, struct iommu_cmd *cmd)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&iommu->lock, flags);
	ret = __iommu_queue_command(iommu, cmd);
	if (!ret)
		iommu->need_sync = true;
	spin_unlock_irqrestore(&iommu->lock, flags);

	return ret;
}