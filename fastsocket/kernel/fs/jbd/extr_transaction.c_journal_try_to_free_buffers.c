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
struct journal_head {int dummy; } ;
struct buffer_head {struct buffer_head* b_this_page; } ;
typedef  int /*<<< orphan*/  journal_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  J_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  __journal_try_to_free_buffer (int /*<<< orphan*/ *,struct buffer_head*) ; 
 scalar_t__ buffer_jbd (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 struct journal_head* journal_grab_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  journal_put_journal_head (struct journal_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int try_to_free_buffers (struct page*) ; 

int journal_try_to_free_buffers(journal_t *journal,
				struct page *page, gfp_t gfp_mask)
{
	struct buffer_head *head;
	struct buffer_head *bh;
	int ret = 0;

	J_ASSERT(PageLocked(page));

	head = page_buffers(page);
	bh = head;
	do {
		struct journal_head *jh;

		/*
		 * We take our own ref against the journal_head here to avoid
		 * having to add tons of locking around each instance of
		 * journal_remove_journal_head() and journal_put_journal_head().
		 */
		jh = journal_grab_journal_head(bh);
		if (!jh)
			continue;

		jbd_lock_bh_state(bh);
		__journal_try_to_free_buffer(journal, bh);
		journal_put_journal_head(jh);
		jbd_unlock_bh_state(bh);
		if (buffer_jbd(bh))
			goto busy;
	} while ((bh = bh->b_this_page) != head);

	ret = try_to_free_buffers(page);

busy:
	return ret;
}