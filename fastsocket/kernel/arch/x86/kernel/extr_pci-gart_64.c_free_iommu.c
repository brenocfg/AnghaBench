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
 int /*<<< orphan*/  iommu_area_free (int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  iommu_bitmap_lock ; 
 int /*<<< orphan*/  iommu_gart_bitmap ; 
 unsigned long next_bit ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_iommu(unsigned long offset, int size)
{
	unsigned long flags;

	spin_lock_irqsave(&iommu_bitmap_lock, flags);
	iommu_area_free(iommu_gart_bitmap, offset, size);
	if (offset >= next_bit)
		next_bit = offset + size;
	spin_unlock_irqrestore(&iommu_bitmap_lock, flags);
}