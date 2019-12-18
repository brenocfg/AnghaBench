#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct journal_head {scalar_t__ b_jlist; int /*<<< orphan*/ * b_transaction; int /*<<< orphan*/ * b_cp_transaction; int /*<<< orphan*/ * b_next_transaction; } ;
struct buffer_head {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  j_list_lock; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 scalar_t__ BJ_None ; 
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int /*<<< orphan*/  __brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  __jbd2_journal_remove_checkpoint (struct journal_head*) ; 
 struct journal_head* bh2jh (struct buffer_head*) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd2_journal_remove_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__journal_try_to_free_buffer(journal_t *journal, struct buffer_head *bh)
{
	struct journal_head *jh;

	jh = bh2jh(bh);

	if (buffer_locked(bh) || buffer_dirty(bh))
		goto out;

	if (jh->b_next_transaction != NULL)
		goto out;

	spin_lock(&journal->j_list_lock);
	if (jh->b_cp_transaction != NULL && jh->b_transaction == NULL) {
		/* written-back checkpointed metadata buffer */
		if (jh->b_jlist == BJ_None) {
			JBUFFER_TRACE(jh, "remove from checkpoint list");
			__jbd2_journal_remove_checkpoint(jh);
			jbd2_journal_remove_journal_head(bh);
			__brelse(bh);
		}
	}
	spin_unlock(&journal->j_list_lock);
out:
	return;
}