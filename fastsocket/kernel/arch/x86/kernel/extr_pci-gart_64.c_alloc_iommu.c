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
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long long,int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned long long dma_get_seg_boundary (struct device*) ; 
 unsigned long iommu_area_alloc (int /*<<< orphan*/ ,unsigned long,unsigned long,int,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  iommu_bitmap_lock ; 
 unsigned long long iommu_bus_base ; 
 scalar_t__ iommu_fullflush ; 
 int /*<<< orphan*/  iommu_gart_bitmap ; 
 unsigned long iommu_pages ; 
 int need_flush ; 
 unsigned long next_bit ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned long alloc_iommu(struct device *dev, int size,
				 unsigned long align_mask)
{
	unsigned long offset, flags;
	unsigned long boundary_size;
	unsigned long base_index;

	base_index = ALIGN(iommu_bus_base & dma_get_seg_boundary(dev),
			   PAGE_SIZE) >> PAGE_SHIFT;
	boundary_size = ALIGN((unsigned long long)dma_get_seg_boundary(dev) + 1,
			      PAGE_SIZE) >> PAGE_SHIFT;

	spin_lock_irqsave(&iommu_bitmap_lock, flags);
	offset = iommu_area_alloc(iommu_gart_bitmap, iommu_pages, next_bit,
				  size, base_index, boundary_size, align_mask);
	if (offset == -1) {
		need_flush = true;
		offset = iommu_area_alloc(iommu_gart_bitmap, iommu_pages, 0,
					  size, base_index, boundary_size,
					  align_mask);
	}
	if (offset != -1) {
		next_bit = offset+size;
		if (next_bit >= iommu_pages) {
			next_bit = 0;
			need_flush = true;
		}
	}
	if (iommu_fullflush)
		need_flush = true;
	spin_unlock_irqrestore(&iommu_bitmap_lock, flags);

	return offset;
}