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
struct journal_head {scalar_t__ b_jcount; int /*<<< orphan*/  b_transaction; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  J_ASSERT_JH (struct journal_head*,int) ; 
 int /*<<< orphan*/  __brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  __journal_remove_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_lock_bh_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_journal_head (struct buffer_head*) ; 
 struct buffer_head* jh2bh (struct journal_head*) ; 

void jbd2_journal_put_journal_head(struct journal_head *jh)
{
	struct buffer_head *bh = jh2bh(jh);

	jbd_lock_bh_journal_head(bh);
	J_ASSERT_JH(jh, jh->b_jcount > 0);
	--jh->b_jcount;
	if (!jh->b_jcount && !jh->b_transaction) {
		__journal_remove_journal_head(bh);
		__brelse(bh);
	}
	jbd_unlock_bh_journal_head(bh);
}