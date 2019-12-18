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
struct page {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned int CACHE_COLOUR (unsigned long) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  PG_dcache_dirty ; 
 scalar_t__ TOP_PTE (unsigned long) ; 
 int /*<<< orphan*/  __flush_dcache_page (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  copy_page (void*,void*) ; 
 int /*<<< orphan*/  discard_old_kernel_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_kernel_page (unsigned long) ; 
 unsigned long from_address ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  page_mapping (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pfn_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_ext (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long to_address ; 
 int /*<<< orphan*/  v6_lock ; 

__attribute__((used)) static void v6_copy_user_highpage_aliasing(struct page *to,
	struct page *from, unsigned long vaddr)
{
	unsigned int offset = CACHE_COLOUR(vaddr);
	unsigned long kfrom, kto;

	if (test_and_clear_bit(PG_dcache_dirty, &from->flags))
		__flush_dcache_page(page_mapping(from), from);

	/* FIXME: not highmem safe */
	discard_old_kernel_data(page_address(to));

	/*
	 * Now copy the page using the same cache colour as the
	 * pages ultimate destination.
	 */
	spin_lock(&v6_lock);

	set_pte_ext(TOP_PTE(from_address) + offset, pfn_pte(page_to_pfn(from), PAGE_KERNEL), 0);
	set_pte_ext(TOP_PTE(to_address) + offset, pfn_pte(page_to_pfn(to), PAGE_KERNEL), 0);

	kfrom = from_address + (offset << PAGE_SHIFT);
	kto   = to_address + (offset << PAGE_SHIFT);

	flush_tlb_kernel_page(kfrom);
	flush_tlb_kernel_page(kto);

	copy_page((void *)kto, (void *)kfrom);

	spin_unlock(&v6_lock);
}