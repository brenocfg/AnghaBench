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
struct iommu_arena {unsigned long hint; unsigned long limit; int /*<<< orphan*/  map; } ;
struct iommu {int page_table_map_base; int /*<<< orphan*/  (* flush_all ) (struct iommu*) ;struct iommu_arena arena; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int) ; 
 unsigned long DMA_ERROR_CODE ; 
 int IO_PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long dma_get_seg_boundary (struct device*) ; 
 unsigned long iommu_area_alloc (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,int,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  stub1 (struct iommu*) ; 
 int /*<<< orphan*/  stub2 (struct iommu*) ; 
 scalar_t__ unlikely (int) ; 

unsigned long iommu_range_alloc(struct device *dev,
				struct iommu *iommu,
				unsigned long npages,
				unsigned long *handle)
{
	unsigned long n, end, start, limit, boundary_size;
	struct iommu_arena *arena = &iommu->arena;
	int pass = 0;

	/* This allocator was derived from x86_64's bit string search */

	/* Sanity check */
	if (unlikely(npages == 0)) {
		if (printk_ratelimit())
			WARN_ON(1);
		return DMA_ERROR_CODE;
	}

	if (handle && *handle)
		start = *handle;
	else
		start = arena->hint;

	limit = arena->limit;

	/* The case below can happen if we have a small segment appended
	 * to a large, or when the previous alloc was at the very end of
	 * the available space. If so, go back to the beginning and flush.
	 */
	if (start >= limit) {
		start = 0;
		if (iommu->flush_all)
			iommu->flush_all(iommu);
	}

 again:

	if (dev)
		boundary_size = ALIGN(dma_get_seg_boundary(dev) + 1,
				      1 << IO_PAGE_SHIFT);
	else
		boundary_size = ALIGN(1UL << 32, 1 << IO_PAGE_SHIFT);

	n = iommu_area_alloc(arena->map, limit, start, npages,
			     iommu->page_table_map_base >> IO_PAGE_SHIFT,
			     boundary_size >> IO_PAGE_SHIFT, 0);
	if (n == -1) {
		if (likely(pass < 1)) {
			/* First failure, rescan from the beginning.  */
			start = 0;
			if (iommu->flush_all)
				iommu->flush_all(iommu);
			pass++;
			goto again;
		} else {
			/* Second failure, give up */
			return DMA_ERROR_CODE;
		}
	}

	end = n + npages;

	arena->hint = end;

	/* Update handle for SG allocations */
	if (handle)
		*handle = end;

	return n;
}