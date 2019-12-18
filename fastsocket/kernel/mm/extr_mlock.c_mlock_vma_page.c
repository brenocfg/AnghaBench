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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NR_MLOCK ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  TestSetPageMlocked (struct page*) ; 
 int /*<<< orphan*/  UNEVICTABLE_PGMLOCKED ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isolate_lru_page (struct page*) ; 
 int /*<<< orphan*/  putback_lru_page (struct page*) ; 

void mlock_vma_page(struct page *page)
{
	BUG_ON(!PageLocked(page));

	if (!TestSetPageMlocked(page)) {
		inc_zone_page_state(page, NR_MLOCK);
		count_vm_event(UNEVICTABLE_PGMLOCKED);
		if (!isolate_lru_page(page))
			putback_lru_page(page);
	}
}