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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; } ;
struct page {int /*<<< orphan*/  _mapcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_ANON_PAGES ; 
 int /*<<< orphan*/  NR_ANON_TRANSPARENT_HUGEPAGES ; 
 int /*<<< orphan*/  PageKsm (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __inc_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __page_check_anon_rmap (struct page*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  __page_set_anon_rmap (struct page*,struct vm_area_struct*,unsigned long,int) ; 
 int atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void do_page_add_anon_rmap(struct page *page,
	struct vm_area_struct *vma, unsigned long address, int exclusive)
{
	int first = atomic_inc_and_test(&page->_mapcount);
	if (first) {
		if (!PageTransHuge(page))
			__inc_zone_page_state(page, NR_ANON_PAGES);
		else
			__inc_zone_page_state(page,
					      NR_ANON_TRANSPARENT_HUGEPAGES);
	}
	if (unlikely(PageKsm(page)))
		return;

	VM_BUG_ON(!PageLocked(page));
	VM_BUG_ON(address < vma->vm_start || address >= vma->vm_end);
	if (first)
		__page_set_anon_rmap(page, vma, address, exclusive);
	else
		__page_check_anon_rmap(page, vma, address);
}