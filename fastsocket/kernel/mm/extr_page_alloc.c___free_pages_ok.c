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
struct page {int /*<<< orphan*/ * mapping; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  PGFREE ; 
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 int __TestClearPageMlocked (struct page*) ; 
 int /*<<< orphan*/  __count_vm_events (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arch_free_page (struct page*,unsigned int) ; 
 int /*<<< orphan*/  debug_check_no_locks_freed (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  debug_check_no_obj_freed (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  free_one_page (int /*<<< orphan*/ ,struct page*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page_mlock (struct page*) ; 
 scalar_t__ free_pages_check (struct page*) ; 
 int /*<<< orphan*/  get_pageblock_migratetype (struct page*) ; 
 int /*<<< orphan*/  kernel_map_pages (struct page*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemcheck_free_shadow (struct page*,unsigned int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  page_zone (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __free_pages_ok(struct page *page, unsigned int order)
{
	unsigned long flags;
	int i;
	int bad = 0;
	int wasMlocked = __TestClearPageMlocked(page);

	kmemcheck_free_shadow(page, order);

	if (PageAnon(page))
		page->mapping = NULL;
	for (i = 0 ; i < (1 << order) ; ++i)
		bad += free_pages_check(page + i);
	if (bad)
		return;

	if (!PageHighMem(page)) {
		debug_check_no_locks_freed(page_address(page),PAGE_SIZE<<order);
		debug_check_no_obj_freed(page_address(page),
					   PAGE_SIZE << order);
	}
	arch_free_page(page, order);
	kernel_map_pages(page, 1 << order, 0);

	local_irq_save(flags);
	if (unlikely(wasMlocked))
		free_page_mlock(page);
	__count_vm_events(PGFREE, 1 << order);
	free_one_page(page_zone(page), page, order,
					get_pageblock_migratetype(page));
	local_irq_restore(flags);
}