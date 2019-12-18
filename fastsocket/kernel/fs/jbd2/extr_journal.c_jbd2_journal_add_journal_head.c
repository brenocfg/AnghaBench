#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct journal_head {int /*<<< orphan*/  b_jcount; struct buffer_head* b_bh; } ;
struct buffer_head {struct journal_head* b_private; TYPE_1__* b_page; int /*<<< orphan*/  b_count; } ;
struct TYPE_2__ {scalar_t__ mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  J_ASSERT_BH (struct buffer_head*,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct journal_head* bh2jh (struct buffer_head*) ; 
 scalar_t__ buffer_jbd (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_lock_bh_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_journal_head (struct buffer_head*) ; 
 struct journal_head* journal_alloc_journal_head () ; 
 int /*<<< orphan*/  journal_free_journal_head (struct journal_head*) ; 
 int /*<<< orphan*/  memset (struct journal_head*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_buffer_jbd (struct buffer_head*) ; 

struct journal_head *jbd2_journal_add_journal_head(struct buffer_head *bh)
{
	struct journal_head *jh;
	struct journal_head *new_jh = NULL;

repeat:
	if (!buffer_jbd(bh)) {
		new_jh = journal_alloc_journal_head();
		memset(new_jh, 0, sizeof(*new_jh));
	}

	jbd_lock_bh_journal_head(bh);
	if (buffer_jbd(bh)) {
		jh = bh2jh(bh);
	} else {
		J_ASSERT_BH(bh,
			(atomic_read(&bh->b_count) > 0) ||
			(bh->b_page && bh->b_page->mapping));

		if (!new_jh) {
			jbd_unlock_bh_journal_head(bh);
			goto repeat;
		}

		jh = new_jh;
		new_jh = NULL;		/* We consumed it */
		set_buffer_jbd(bh);
		bh->b_private = jh;
		jh->b_bh = bh;
		get_bh(bh);
		BUFFER_TRACE(bh, "added journal_head");
	}
	jh->b_jcount++;
	jbd_unlock_bh_journal_head(bh);
	if (new_jh)
		journal_free_journal_head(new_jh);
	return bh->b_private;
}