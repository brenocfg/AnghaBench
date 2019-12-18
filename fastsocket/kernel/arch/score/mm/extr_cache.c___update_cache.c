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
 int /*<<< orphan*/  PG_arch_1 ; 
 int VM_EXEC ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_data_cache_page (unsigned long) ; 
 scalar_t__ page_address (struct page*) ; 
 scalar_t__ page_mapping (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void __update_cache(struct vm_area_struct *vma, unsigned long address,
		pte_t pte)
{
	struct page *page;
	unsigned long pfn, addr;
	int exec = (vma->vm_flags & VM_EXEC);

	pfn = pte_pfn(pte);
	if (unlikely(!pfn_valid(pfn)))
		return;
	page = pfn_to_page(pfn);
	if (page_mapping(page) && test_bit(PG_arch_1, &page->flags)) {
		addr = (unsigned long) page_address(page);
		if (exec)
			flush_data_cache_page(addr);
		clear_bit(PG_arch_1, &page->flags);
	}
}