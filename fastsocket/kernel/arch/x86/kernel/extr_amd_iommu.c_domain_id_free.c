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

/* Variables and functions */
 int MAX_DOMAIN_ID ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_iommu_devtable_lock ; 
 int /*<<< orphan*/  amd_iommu_pd_alloc_bitmap ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void domain_id_free(int id)
{
	unsigned long flags;

	write_lock_irqsave(&amd_iommu_devtable_lock, flags);
	if (id > 0 && id < MAX_DOMAIN_ID)
		__clear_bit(id, amd_iommu_pd_alloc_bitmap);
	write_unlock_irqrestore(&amd_iommu_devtable_lock, flags);
}