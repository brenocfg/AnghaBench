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
 int MAX_OBJS_PER_PAGE ; 
 scalar_t__ PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ fls (int) ; 
 int get_order (int) ; 
 int max (int,scalar_t__) ; 
 int slub_min_order ; 

__attribute__((used)) static inline int slab_order(int size, int min_objects,
				int max_order, int fract_leftover)
{
	int order;
	int rem;
	int min_order = slub_min_order;

	if ((PAGE_SIZE << min_order) / size > MAX_OBJS_PER_PAGE)
		return get_order(size * MAX_OBJS_PER_PAGE) - 1;

	for (order = max(min_order,
				fls(min_objects * size - 1) - PAGE_SHIFT);
			order <= max_order; order++) {

		unsigned long slab_size = PAGE_SIZE << order;

		if (slab_size < min_objects * size)
			continue;

		rem = slab_size % size;

		if (rem <= slab_size / fract_leftover)
			break;

	}

	return order;
}