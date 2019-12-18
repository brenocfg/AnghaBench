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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long DCACHE_ALIAS_MASK ; 
 int /*<<< orphan*/  PG_arch_1 ; 
 int /*<<< orphan*/  PageReserved (struct page*) ; 
 unsigned long TLBTEMP_BASE_1 ; 
 int VM_EXEC ; 
 int /*<<< orphan*/  __flush_dcache_page (unsigned long) ; 
 int /*<<< orphan*/  __flush_invalidate_dcache_page (unsigned long) ; 
 int /*<<< orphan*/  __flush_invalidate_dcache_page_alias (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  __invalidate_icache_page (unsigned long) ; 
 int /*<<< orphan*/  __invalidate_icache_page_alias (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  invalidate_dtlb_mapping (unsigned long) ; 
 int /*<<< orphan*/  invalidate_itlb_mapping (unsigned long) ; 
 scalar_t__ page_address (struct page*) ; 
 unsigned long page_to_phys (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
update_mmu_cache(struct vm_area_struct * vma, unsigned long addr, pte_t pte)
{
	unsigned long pfn = pte_pfn(pte);
	struct page *page;

	if (!pfn_valid(pfn))
		return;

	page = pfn_to_page(pfn);

	/* Invalidate old entry in TLBs */

	invalidate_itlb_mapping(addr);
	invalidate_dtlb_mapping(addr);

#if (DCACHE_WAY_SIZE > PAGE_SIZE) && XCHAL_DCACHE_IS_WRITEBACK

	if (!PageReserved(page) && test_bit(PG_arch_1, &page->flags)) {

		unsigned long vaddr = TLBTEMP_BASE_1 + (addr & DCACHE_ALIAS_MASK);
		unsigned long paddr = (unsigned long) page_address(page);
		unsigned long phys = page_to_phys(page);

		__flush_invalidate_dcache_page(paddr);

		__flush_invalidate_dcache_page_alias(vaddr, phys);
		__invalidate_icache_page_alias(vaddr, phys);

		clear_bit(PG_arch_1, &page->flags);
	}
#else
	if (!PageReserved(page) && !test_bit(PG_arch_1, &page->flags)
	    && (vma->vm_flags & VM_EXEC) != 0) {
	    	unsigned long paddr = (unsigned long) page_address(page);
		__flush_dcache_page(paddr);
		__invalidate_icache_page(paddr);
		set_bit(PG_arch_1, &page->flags);
	}
#endif
}