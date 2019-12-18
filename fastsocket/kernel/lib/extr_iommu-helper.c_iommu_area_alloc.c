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
 unsigned long find_next_zero_area (unsigned long*,unsigned long,unsigned long,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  iommu_area_reserve (unsigned long*,unsigned long,unsigned int) ; 
 scalar_t__ iommu_is_span_boundary (unsigned long,unsigned int,unsigned long,unsigned long) ; 

unsigned long iommu_area_alloc(unsigned long *map, unsigned long size,
			       unsigned long start, unsigned int nr,
			       unsigned long shift, unsigned long boundary_size,
			       unsigned long align_mask)
{
	unsigned long index;
again:
	index = find_next_zero_area(map, size, start, nr, align_mask);
	if (index != -1) {
		if (iommu_is_span_boundary(index, nr, shift, boundary_size)) {
			/* we could do more effectively */
			start = index + 1;
			goto again;
		}
		iommu_area_reserve(map, index, nr);
	}
	return index;
}