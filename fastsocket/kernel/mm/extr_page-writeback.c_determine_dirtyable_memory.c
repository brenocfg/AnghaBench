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
 int /*<<< orphan*/  NR_FREE_PAGES ; 
 unsigned long global_page_state (int /*<<< orphan*/ ) ; 
 unsigned long global_reclaimable_pages () ; 
 scalar_t__ highmem_dirtyable_memory (unsigned long) ; 
 int /*<<< orphan*/  vm_highmem_is_dirtyable ; 

unsigned long determine_dirtyable_memory(void)
{
	unsigned long x;

	x = global_page_state(NR_FREE_PAGES) + global_reclaimable_pages();

	if (!vm_highmem_is_dirtyable)
		x -= highmem_dirtyable_memory(x);

	return x + 1;	/* Ensure that we never return 0 */
}