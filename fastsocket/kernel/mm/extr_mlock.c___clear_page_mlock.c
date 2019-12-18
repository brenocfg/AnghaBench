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
struct page {int /*<<< orphan*/  mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_MLOCK ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ PageUnevictable (struct page*) ; 
 int /*<<< orphan*/  UNEVICTABLE_PGCLEARED ; 
 int /*<<< orphan*/  UNEVICTABLE_PGSTRANDED ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isolate_lru_page (struct page*) ; 
 int /*<<< orphan*/  putback_lru_page (struct page*) ; 

void __clear_page_mlock(struct page *page)
{
	VM_BUG_ON(!PageLocked(page));

	if (!page->mapping) {	/* truncated ? */
		return;
	}

	dec_zone_page_state(page, NR_MLOCK);
	count_vm_event(UNEVICTABLE_PGCLEARED);
	if (!isolate_lru_page(page)) {
		putback_lru_page(page);
	} else {
		/*
		 * We lost the race. the page already moved to evictable list.
		 */
		if (PageUnevictable(page))
			count_vm_event(UNEVICTABLE_PGSTRANDED);
	}
}