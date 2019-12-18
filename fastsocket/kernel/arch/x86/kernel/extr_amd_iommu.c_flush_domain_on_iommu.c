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
struct iommu_cmd {int dummy; } ;
struct amd_iommu {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INV_IOMMU_ALL_PAGES_ADDRESS ; 
 int /*<<< orphan*/  __iommu_build_inv_iommu_pages (struct iommu_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  __iommu_completion_wait (struct amd_iommu*) ; 
 int /*<<< orphan*/  __iommu_queue_command (struct amd_iommu*,struct iommu_cmd*) ; 
 int /*<<< orphan*/  __iommu_wait_for_completion (struct amd_iommu*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void flush_domain_on_iommu(struct amd_iommu *iommu, u16 domid)
{
	struct iommu_cmd cmd;
	unsigned long flags;

	__iommu_build_inv_iommu_pages(&cmd, CMD_INV_IOMMU_ALL_PAGES_ADDRESS,
				      domid, 1, 1);

	spin_lock_irqsave(&iommu->lock, flags);
	__iommu_queue_command(iommu, &cmd);
	__iommu_completion_wait(iommu);
	__iommu_wait_for_completion(iommu);
	spin_unlock_irqrestore(&iommu->lock, flags);
}