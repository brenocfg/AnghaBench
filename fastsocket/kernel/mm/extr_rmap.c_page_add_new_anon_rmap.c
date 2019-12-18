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
 int /*<<< orphan*/  LRU_ACTIVE_ANON ; 
 int /*<<< orphan*/  NR_ANON_PAGES ; 
 int /*<<< orphan*/  NR_ANON_TRANSPARENT_HUGEPAGES ; 
 int /*<<< orphan*/  PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  SetPageSwapBacked (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __inc_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __page_set_anon_rmap (struct page*,struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  add_page_to_unevictable_list (struct page*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lru_cache_add_lru (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ page_evictable (struct page*,struct vm_area_struct*) ; 

void page_add_new_anon_rmap(struct page *page,
	struct vm_area_struct *vma, unsigned long address)
{
	VM_BUG_ON(address < vma->vm_start || address >= vma->vm_end);
	SetPageSwapBacked(page);
	atomic_set(&page->_mapcount, 0); /* increment count (starts at -1) */
	if (!PageTransHuge(page))
		__inc_zone_page_state(page, NR_ANON_PAGES);
	else
		__inc_zone_page_state(page, NR_ANON_TRANSPARENT_HUGEPAGES);
	__page_set_anon_rmap(page, vma, address, 1);
	if (page_evictable(page, vma))
		lru_cache_add_lru(page, LRU_ACTIVE_ANON);
	else
		add_page_to_unevictable_list(page);
}