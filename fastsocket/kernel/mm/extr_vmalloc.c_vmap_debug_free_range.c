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
 int /*<<< orphan*/  flush_tlb_kernel_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  vunmap_page_range (unsigned long,unsigned long) ; 

__attribute__((used)) static void vmap_debug_free_range(unsigned long start, unsigned long end)
{
	/*
	 * Unmap page tables and force a TLB flush immediately if
	 * CONFIG_DEBUG_PAGEALLOC is set. This catches use after free
	 * bugs similarly to those in linear kernel virtual address
	 * space after a page has been freed.
	 *
	 * All the lazy freeing logic is still retained, in order to
	 * minimise intrusiveness of this debugging feature.
	 *
	 * This is going to be *slow* (linear kernel virtual address
	 * debugging doesn't do a broadcast TLB flush so it is a lot
	 * faster).
	 */
#ifdef CONFIG_DEBUG_PAGEALLOC
	vunmap_page_range(start, end);
	flush_tlb_kernel_range(start, end);
#endif
}