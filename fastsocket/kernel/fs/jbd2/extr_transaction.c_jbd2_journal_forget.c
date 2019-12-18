#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* t_journal; } ;
typedef  TYPE_1__ transaction_t ;
struct journal_head {int b_modified; TYPE_1__* b_next_transaction; TYPE_1__* b_transaction; scalar_t__ b_cp_transaction; int /*<<< orphan*/  b_frozen_data; int /*<<< orphan*/  b_committed_data; } ;
struct buffer_head {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  j_list_lock; TYPE_1__* j_committing_transaction; } ;
typedef  TYPE_2__ journal_t ;
struct TYPE_8__ {int /*<<< orphan*/  h_buffer_credits; TYPE_1__* h_transaction; } ;
typedef  TYPE_3__ handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BJ_Forget ; 
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int EIO ; 
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int /*<<< orphan*/  J_ASSERT (int) ; 
 int /*<<< orphan*/  J_ASSERT_JH (struct journal_head*,int) ; 
 int /*<<< orphan*/  J_EXPECT_JH (struct journal_head*,int,char*) ; 
 int /*<<< orphan*/  __bforget (struct buffer_head*) ; 
 int /*<<< orphan*/  __brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  __jbd2_journal_file_buffer (struct journal_head*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __jbd2_journal_temp_unlink_buffer (struct journal_head*) ; 
 int /*<<< orphan*/  __jbd2_journal_unfile_buffer (struct journal_head*) ; 
 struct journal_head* bh2jh (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_jbd (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_jbddirty (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd2_journal_remove_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int jbd2_journal_forget (handle_t *handle, struct buffer_head *bh)
{
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal = transaction->t_journal;
	struct journal_head *jh;
	int drop_reserve = 0;
	int err = 0;
	int was_modified = 0;

	BUFFER_TRACE(bh, "entry");

	jbd_lock_bh_state(bh);
	spin_lock(&journal->j_list_lock);

	if (!buffer_jbd(bh))
		goto not_jbd;
	jh = bh2jh(bh);

	/* Critical error: attempting to delete a bitmap buffer, maybe?
	 * Don't do any jbd operations, and return an error. */
	if (!J_EXPECT_JH(jh, !jh->b_committed_data,
			 "inconsistent data on disk")) {
		err = -EIO;
		goto not_jbd;
	}

	/* keep track of wether or not this transaction modified us */
	was_modified = jh->b_modified;

	/*
	 * The buffer's going from the transaction, we must drop
	 * all references -bzzz
	 */
	jh->b_modified = 0;

	if (jh->b_transaction == handle->h_transaction) {
		J_ASSERT_JH(jh, !jh->b_frozen_data);

		/* If we are forgetting a buffer which is already part
		 * of this transaction, then we can just drop it from
		 * the transaction immediately. */
		clear_buffer_dirty(bh);
		clear_buffer_jbddirty(bh);

		JBUFFER_TRACE(jh, "belongs to current transaction: unfile");

		/*
		 * we only want to drop a reference if this transaction
		 * modified the buffer
		 */
		if (was_modified)
			drop_reserve = 1;

		/*
		 * We are no longer going to journal this buffer.
		 * However, the commit of this transaction is still
		 * important to the buffer: the delete that we are now
		 * processing might obsolete an old log entry, so by
		 * committing, we can satisfy the buffer's checkpoint.
		 *
		 * So, if we have a checkpoint on the buffer, we should
		 * now refile the buffer on our BJ_Forget list so that
		 * we know to remove the checkpoint after we commit.
		 */

		if (jh->b_cp_transaction) {
			__jbd2_journal_temp_unlink_buffer(jh);
			__jbd2_journal_file_buffer(jh, transaction, BJ_Forget);
		} else {
			__jbd2_journal_unfile_buffer(jh);
			jbd2_journal_remove_journal_head(bh);
			__brelse(bh);
			if (!buffer_jbd(bh)) {
				spin_unlock(&journal->j_list_lock);
				jbd_unlock_bh_state(bh);
				__bforget(bh);
				goto drop;
			}
		}
	} else if (jh->b_transaction) {
		J_ASSERT_JH(jh, (jh->b_transaction ==
				 journal->j_committing_transaction));
		/* However, if the buffer is still owned by a prior
		 * (committing) transaction, we can't drop it yet... */
		JBUFFER_TRACE(jh, "belongs to older transaction");
		/* ... but we CAN drop it from the new transaction if we
		 * have also modified it since the original commit. */

		if (jh->b_next_transaction) {
			J_ASSERT(jh->b_next_transaction == transaction);
			jh->b_next_transaction = NULL;

			/*
			 * only drop a reference if this transaction modified
			 * the buffer
			 */
			if (was_modified)
				drop_reserve = 1;
		}
	}

not_jbd:
	spin_unlock(&journal->j_list_lock);
	jbd_unlock_bh_state(bh);
	__brelse(bh);
drop:
	if (drop_reserve) {
		/* no need to reserve log space for this block -bzzz */
		handle->h_buffer_credits++;
	}
	return err;
}