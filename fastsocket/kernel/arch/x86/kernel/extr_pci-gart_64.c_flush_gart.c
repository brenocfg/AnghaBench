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
 int /*<<< orphan*/  amd_flush_garts () ; 
 int /*<<< orphan*/  iommu_bitmap_lock ; 
 int need_flush ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void flush_gart(void)
{
	unsigned long flags;

	spin_lock_irqsave(&iommu_bitmap_lock, flags);
	if (need_flush) {
		amd_flush_garts();
		need_flush = false;
	}
	spin_unlock_irqrestore(&iommu_bitmap_lock, flags);
}