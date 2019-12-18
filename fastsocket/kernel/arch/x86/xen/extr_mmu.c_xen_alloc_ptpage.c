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
struct mm_struct {int /*<<< orphan*/  pgd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMUEXT_PIN_L1_TABLE ; 
 int /*<<< orphan*/  PFN_PHYS (unsigned long) ; 
 unsigned int PT_PTE ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 scalar_t__ PagePinned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPagePinned (struct page*) ; 
 scalar_t__ USE_SPLIT_PTLOCKS ; 
 int /*<<< orphan*/  __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmap_flush_unused () ; 
 int /*<<< orphan*/  make_lowmem_page_readonly (int /*<<< orphan*/ ) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pin_pagetable_pfn (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_alloc_ptpage(struct mm_struct *mm, unsigned long pfn, unsigned level)
{
	struct page *page = pfn_to_page(pfn);

	if (PagePinned(virt_to_page(mm->pgd))) {
		SetPagePinned(page);

		if (!PageHighMem(page)) {
			make_lowmem_page_readonly(__va(PFN_PHYS((unsigned long)pfn)));
			if (level == PT_PTE && USE_SPLIT_PTLOCKS)
				pin_pagetable_pfn(MMUEXT_PIN_L1_TABLE, pfn);
		} else {
			/* make sure there are no stray mappings of
			   this page */
			kmap_flush_unused();
		}
	}
}