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
struct vm_area_struct {int dummy; } ;
struct page {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  PG_dcache_dirty ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_kernel_dcache_page (struct page*) ; 
 scalar_t__ page_mapping (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 scalar_t__ parisc_requires_coherency () ; 
 scalar_t__ pfn_valid (int /*<<< orphan*/ ) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
update_mmu_cache(struct vm_area_struct *vma, unsigned long address, pte_t pte)
{
	struct page *page = pte_page(pte);

	if (pfn_valid(page_to_pfn(page)) && page_mapping(page) &&
	    test_bit(PG_dcache_dirty, &page->flags)) {

		flush_kernel_dcache_page(page);
		clear_bit(PG_dcache_dirty, &page->flags);
	} else if (parisc_requires_coherency())
		flush_kernel_dcache_page(page);
}