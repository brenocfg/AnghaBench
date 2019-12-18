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
 int /*<<< orphan*/  BUG_ON (unsigned long) ; 
 unsigned int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 unsigned long VMALLOC_END ; 
 unsigned long VMALLOC_START ; 
 unsigned int VMAP_MAX_ALLOC ; 
 int /*<<< orphan*/  debug_check_no_locks_freed (void const*,unsigned long) ; 
 int /*<<< orphan*/  free_unmap_vmap_area_addr (unsigned long) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  vb_free (void const*,unsigned long) ; 
 int /*<<< orphan*/  vmap_debug_free_range (unsigned long,unsigned long) ; 

void vm_unmap_ram(const void *mem, unsigned int count)
{
	unsigned long size = count << PAGE_SHIFT;
	unsigned long addr = (unsigned long)mem;

	BUG_ON(!addr);
	BUG_ON(addr < VMALLOC_START);
	BUG_ON(addr > VMALLOC_END);
	BUG_ON(addr & (PAGE_SIZE-1));

	debug_check_no_locks_freed(mem, size);
	vmap_debug_free_range(addr, addr+size);

	if (likely(count <= VMAP_MAX_ALLOC))
		vb_free(mem, size);
	else
		free_unmap_vmap_area_addr(addr);
}