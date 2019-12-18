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
struct vm_area_struct {int vm_flags; } ;
struct page {int /*<<< orphan*/  flags; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  PG_dcache_dirty ; 
 int VM_EXEC ; 
 int /*<<< orphan*/  __flush_dcache_page (struct address_space*,struct page*) ; 
 int /*<<< orphan*/  __flush_icache_all () ; 
 scalar_t__ cache_is_vivt () ; 
 int /*<<< orphan*/  make_coherent (struct address_space*,struct vm_area_struct*,unsigned long,unsigned long) ; 
 struct address_space* page_mapping (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void update_mmu_cache(struct vm_area_struct *vma, unsigned long addr, pte_t pte)
{
	unsigned long pfn = pte_pfn(pte);
	struct address_space *mapping;
	struct page *page;

	if (!pfn_valid(pfn))
		return;

	page = pfn_to_page(pfn);
	mapping = page_mapping(page);
#ifndef CONFIG_SMP
	if (test_and_clear_bit(PG_dcache_dirty, &page->flags))
		__flush_dcache_page(mapping, page);
#endif
	if (mapping) {
		if (cache_is_vivt())
			make_coherent(mapping, vma, addr, pfn);
		else if (vma->vm_flags & VM_EXEC)
			__flush_icache_all();
	}
}