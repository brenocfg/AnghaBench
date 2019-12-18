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
 scalar_t__ PageUnevictable (struct page*) ; 
 int SWAP_MLOCK ; 
 scalar_t__ TestClearPageMlocked (struct page*) ; 
 int /*<<< orphan*/  UNEVICTABLE_PGMUNLOCKED ; 
 int /*<<< orphan*/  UNEVICTABLE_PGSTRANDED ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isolate_lru_page (struct page*) ; 
 int /*<<< orphan*/  putback_lru_page (struct page*) ; 
 int try_to_munlock (struct page*) ; 

void munlock_vma_page(struct page *page)
{
	BUG_ON(!PageLocked(page));

	if (TestClearPageMlocked(page)) {
		dec_zone_page_state(page, NR_MLOCK);
		if (!isolate_lru_page(page)) {
			int ret = try_to_munlock(page);
			/*
			 * did try_to_unlock() succeed or punt?
			 */
			if (ret != SWAP_MLOCK)
				count_vm_event(UNEVICTABLE_PGMUNLOCKED);

			putback_lru_page(page);
		} else {
			/*
			 * We lost the race.  let try_to_unmap() deal
			 * with it.  At least we get the page state and
			 * mlock stats right.  However, page is still on
			 * the noreclaim list.  We'll fix that up when
			 * the page is eventually freed or we scan the
			 * noreclaim list.
			 */
			if (PageUnevictable(page))
				count_vm_event(UNEVICTABLE_PGSTRANDED);
			else
				count_vm_event(UNEVICTABLE_PGMUNLOCKED);
		}
	}
}