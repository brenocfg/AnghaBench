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
struct page {int dummy; } ;

/* Variables and functions */
 unsigned int CACHE_COLOUR (unsigned long) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned int PAGE_SHIFT ; 
 scalar_t__ TOP_PTE (unsigned int) ; 
 int /*<<< orphan*/  clear_page (void*) ; 
 int /*<<< orphan*/  discard_old_kernel_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_kernel_page (unsigned long) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pfn_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_ext (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned int to_address ; 
 int /*<<< orphan*/  v6_lock ; 

__attribute__((used)) static void v6_clear_user_highpage_aliasing(struct page *page, unsigned long vaddr)
{
	unsigned int offset = CACHE_COLOUR(vaddr);
	unsigned long to = to_address + (offset << PAGE_SHIFT);

	/* FIXME: not highmem safe */
	discard_old_kernel_data(page_address(page));

	/*
	 * Now clear the page using the same cache colour as
	 * the pages ultimate destination.
	 */
	spin_lock(&v6_lock);

	set_pte_ext(TOP_PTE(to_address) + offset, pfn_pte(page_to_pfn(page), PAGE_KERNEL), 0);
	flush_tlb_kernel_page(to);
	clear_page((void *)to);

	spin_unlock(&v6_lock);
}