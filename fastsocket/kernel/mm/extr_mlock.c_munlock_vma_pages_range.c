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
struct vm_area_struct {int /*<<< orphan*/  vm_flags; } ;
struct page {scalar_t__ mapping; } ;

/* Variables and functions */
 int FOLL_DUMP ; 
 int FOLL_GET ; 
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_LOCKED ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct page* follow_page (struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  munlock_vma_page (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

void munlock_vma_pages_range(struct vm_area_struct *vma,
			     unsigned long start, unsigned long end)
{
	unsigned long addr;

	lru_add_drain();
	vma->vm_flags &= ~VM_LOCKED;

	for (addr = start; addr < end; addr += PAGE_SIZE) {
		struct page *page;
		/*
		 * Although FOLL_DUMP is intended for get_dump_page(),
		 * it just so happens that its special treatment of the
		 * ZERO_PAGE (returning an error instead of doing get_page)
		 * suits munlock very well (and if somehow an abnormal page
		 * has sneaked into the range, we won't oops here: great).
		 */
		page = follow_page(vma, addr, FOLL_GET | FOLL_DUMP);
		if (page && !IS_ERR(page)) {
			lock_page(page);
			/*
			 * Like in __mlock_vma_pages_range(),
			 * because we lock page here and migration is
			 * blocked by the elevated reference, we need
			 * only check for file-cache page truncation.
			 */
			if (page->mapping)
				munlock_vma_page(page);
			unlock_page(page);
			put_page(page);
		}
		cond_resched();
	}
}