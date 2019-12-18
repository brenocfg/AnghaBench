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
 scalar_t__ PageSlab (struct page*) ; 
 int PageTail (struct page*) ; 
 int /*<<< orphan*/  __get_page_tail_foll (struct page*,int) ; 
 unsigned long compound_lock_irqsave (struct page*) ; 
 struct page* compound_trans_head (struct page*) ; 
 int /*<<< orphan*/  compound_unlock_irqrestore (struct page*,unsigned long) ; 
 scalar_t__ get_page_unless_zero (struct page*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool __get_page_tail(struct page *page)
{
	/*
	 * This takes care of get_page() if run on a tail page
	 * returned by one of the get_user_pages/follow_page variants.
	 * get_user_pages/follow_page itself doesn't need the compound
	 * lock because it runs __get_page_tail_foll() under the
	 * proper PT lock that already serializes against
	 * split_huge_page().
	 */
	unsigned long flags;
	bool got = false;
	struct page *page_head = compound_trans_head(page);

	if (likely(page != page_head && get_page_unless_zero(page_head))) {

		/* Ref to put_compound_page() comment. */
		if (PageSlab(page_head)) {
			if (likely(PageTail(page))) {
				__get_page_tail_foll(page, false);
				return true;
			} else {
				put_page(page_head);
				return false;
			}
		}

		/*
		 * page_head wasn't a dangling pointer but it
		 * may not be a head page anymore by the time
		 * we obtain the lock. That is ok as long as it
		 * can't be freed from under us.
		 */
		flags = compound_lock_irqsave(page_head);
		/* here __split_huge_page_refcount won't run anymore */
		if (likely(PageTail(page))) {
			__get_page_tail_foll(page, false);
			got = true;
		}
		compound_unlock_irqrestore(page_head, flags);
		if (unlikely(!got))
			put_page(page_head);
	}
	return got;
}