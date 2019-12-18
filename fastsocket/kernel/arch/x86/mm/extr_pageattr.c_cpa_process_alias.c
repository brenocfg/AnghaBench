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
struct cpa_data {int pfn; int flags; size_t curpage; unsigned long* vaddr; struct page** pages; } ;

/* Variables and functions */
 int CPA_ARRAY ; 
 int CPA_PAGES_ARRAY ; 
 unsigned long PAGE_OFFSET ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 unsigned long __START_KERNEL_map ; 
 int __change_page_attr_set_clr (struct cpa_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ __va (int) ; 
 unsigned long _brk_end ; 
 scalar_t__ _text ; 
 unsigned long highmap_end_pfn () ; 
 unsigned long highmap_start_pfn () ; 
 int max_low_pfn_mapped ; 
 int max_pfn_mapped ; 
 scalar_t__ page_address (struct page*) ; 
 unsigned long phys_base ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ within (unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static int cpa_process_alias(struct cpa_data *cpa)
{
	struct cpa_data alias_cpa;
	unsigned long laddr = (unsigned long)__va(cpa->pfn << PAGE_SHIFT);
	unsigned long vaddr;
	int ret;

	if (cpa->pfn >= max_pfn_mapped)
		return 0;

#ifdef CONFIG_X86_64
	if (cpa->pfn >= max_low_pfn_mapped && cpa->pfn < (1UL<<(32-PAGE_SHIFT)))
		return 0;
#endif
	/*
	 * No need to redo, when the primary call touched the direct
	 * mapping already:
	 */
	if (cpa->flags & CPA_PAGES_ARRAY) {
		struct page *page = cpa->pages[cpa->curpage];
		if (unlikely(PageHighMem(page)))
			return 0;
		vaddr = (unsigned long)page_address(page);
	} else if (cpa->flags & CPA_ARRAY)
		vaddr = cpa->vaddr[cpa->curpage];
	else
		vaddr = *cpa->vaddr;

	if (!(within(vaddr, PAGE_OFFSET,
		    PAGE_OFFSET + (max_pfn_mapped << PAGE_SHIFT)))) {

		alias_cpa = *cpa;
		alias_cpa.vaddr = &laddr;
		alias_cpa.flags &= ~(CPA_PAGES_ARRAY | CPA_ARRAY);

		ret = __change_page_attr_set_clr(&alias_cpa, 0);
		if (ret)
			return ret;
	}

#ifdef CONFIG_X86_64
	/*
	 * If the primary call didn't touch the high mapping already
	 * and the physical address is inside the kernel map, we need
	 * to touch the high mapped kernel as well:
	 */
	if (!within(vaddr, (unsigned long)_text, _brk_end) &&
	    within(cpa->pfn, highmap_start_pfn(), highmap_end_pfn())) {
		unsigned long temp_cpa_vaddr = (cpa->pfn << PAGE_SHIFT) +
					       __START_KERNEL_map - phys_base;
		alias_cpa = *cpa;
		alias_cpa.vaddr = &temp_cpa_vaddr;
		alias_cpa.flags &= ~(CPA_PAGES_ARRAY | CPA_ARRAY);

		/*
		 * The high mapping range is imprecise, so ignore the
		 * return value.
		 */
		__change_page_attr_set_clr(&alias_cpa, 0);
	}
#endif

	return 0;
}