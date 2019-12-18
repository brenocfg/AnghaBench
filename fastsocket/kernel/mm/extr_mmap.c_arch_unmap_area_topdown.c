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
struct mm_struct {unsigned long free_area_cache; unsigned long mmap_base; unsigned int cached_hole_size; unsigned int total_vm; unsigned int reserved_vm; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 unsigned int sysctl_unmap_area_factor ; 

void arch_unmap_area_topdown(struct mm_struct *mm, unsigned long addr)
{
	unsigned int unmap_factor = sysctl_unmap_area_factor;
	if (likely(!unmap_factor)) {
		/*
		 * Is this a new hole at the highest possible address?
		 */
		if (addr > mm->free_area_cache)
			mm->free_area_cache = addr;

		/* dont allow allocations above current base */
		if (mm->free_area_cache > mm->mmap_base)
			mm->free_area_cache = mm->mmap_base;
	} else {
		/*
		 * Go back to first-fit search once more than 1/(factor)th
		 * of normal process memory has been unmapped.
		 */
		if (mm->cached_hole_size >
		    (mm->total_vm - mm->reserved_vm) / unmap_factor) {
			mm->free_area_cache = mm->mmap_base;
			mm->cached_hole_size = 0UL;
		}
	}
}