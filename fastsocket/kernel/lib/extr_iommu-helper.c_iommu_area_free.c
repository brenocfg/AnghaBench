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
 int /*<<< orphan*/  __clear_bit (unsigned long,unsigned long*) ; 

void iommu_area_free(unsigned long *map, unsigned long start, unsigned int nr)
{
	unsigned long end = start + nr;

	while (start < end) {
		__clear_bit(start, map);
		start++;
	}
}