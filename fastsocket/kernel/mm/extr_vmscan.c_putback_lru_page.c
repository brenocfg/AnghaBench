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
 int /*<<< orphan*/  ClearPageUnevictable (struct page*) ; 
 int LRU_UNEVICTABLE ; 
 int /*<<< orphan*/  PageLRU (struct page*) ; 
 int PageUnevictable (struct page*) ; 
 int /*<<< orphan*/  TestClearPageActive (struct page*) ; 
 int /*<<< orphan*/  UNEVICTABLE_PGCULLED ; 
 int /*<<< orphan*/  UNEVICTABLE_PGRESCUED ; 
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_page_to_unevictable_list (struct page*) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isolate_lru_page (struct page*) ; 
 int /*<<< orphan*/  lru_cache_add_lru (struct page*,int) ; 
 scalar_t__ page_evictable (struct page*,int /*<<< orphan*/ *) ; 
 int page_lru_base_type (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  smp_mb () ; 

void putback_lru_page(struct page *page)
{
	int lru;
	int active = !!TestClearPageActive(page);
	int was_unevictable = PageUnevictable(page);

	VM_BUG_ON(PageLRU(page));

redo:
	ClearPageUnevictable(page);

	if (page_evictable(page, NULL)) {
		/*
		 * For evictable pages, we can use the cache.
		 * In event of a race, worst case is we end up with an
		 * unevictable page on [in]active list.
		 * We know how to handle that.
		 */
		lru = active + page_lru_base_type(page);
		lru_cache_add_lru(page, lru);
	} else {
		/*
		 * Put unevictable pages directly on zone's unevictable
		 * list.
		 */
		lru = LRU_UNEVICTABLE;
		add_page_to_unevictable_list(page);
		/*
		 * When racing with an mlock clearing (page is
		 * unlocked), make sure that if the other thread does
		 * not observe our setting of PG_lru and fails
		 * isolation, we see PG_mlocked cleared below and move
		 * the page back to the evictable list.
		 *
		 * The other side is TestClearPageMlocked().
		 */
		smp_mb();
	}

	/*
	 * page's status can change while we move it among lru. If an evictable
	 * page is on unevictable list, it never be freed. To avoid that,
	 * check after we added it to the list, again.
	 */
	if (lru == LRU_UNEVICTABLE && page_evictable(page, NULL)) {
		if (!isolate_lru_page(page)) {
			put_page(page);
			goto redo;
		}
		/* This means someone else dropped this page from LRU
		 * So, it will be freed or putback to LRU again. There is
		 * nothing to do here.
		 */
	}

	if (was_unevictable && lru != LRU_UNEVICTABLE)
		count_vm_event(UNEVICTABLE_PGRESCUED);
	else if (!was_unevictable && lru == LRU_UNEVICTABLE)
		count_vm_event(UNEVICTABLE_PGCULLED);

	put_page(page);		/* drop ref from isolate */
}