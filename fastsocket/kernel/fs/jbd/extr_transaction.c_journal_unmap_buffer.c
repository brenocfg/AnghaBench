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
typedef  int /*<<< orphan*/  transaction_t ;
struct journal_head {scalar_t__ b_jlist; int /*<<< orphan*/ * b_next_transaction; int /*<<< orphan*/  b_cp_transaction; int /*<<< orphan*/ * b_transaction; } ;
struct buffer_head {int /*<<< orphan*/ * b_bdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_list_lock; int /*<<< orphan*/ * j_running_transaction; int /*<<< orphan*/ * j_committing_transaction; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 scalar_t__ BJ_Locked ; 
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int /*<<< orphan*/  J_ASSERT (int) ; 
 int /*<<< orphan*/  J_ASSERT_BH (struct buffer_head*,int) ; 
 int /*<<< orphan*/  J_ASSERT_JH (struct journal_head*,int) ; 
 int __dispose_buffer (struct journal_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_jbd (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_jbddirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_jbddirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_req (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 struct journal_head* journal_grab_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  journal_put_journal_head (struct journal_head*) ; 
 int /*<<< orphan*/  set_buffer_freed (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int journal_unmap_buffer(journal_t *journal, struct buffer_head *bh)
{
	transaction_t *transaction;
	struct journal_head *jh;
	int may_free = 1;
	int ret;

	BUFFER_TRACE(bh, "entry");

	/*
	 * It is safe to proceed here without the j_list_lock because the
	 * buffers cannot be stolen by try_to_free_buffers as long as we are
	 * holding the page lock. --sct
	 */

	if (!buffer_jbd(bh))
		goto zap_buffer_unlocked;

	spin_lock(&journal->j_state_lock);
	jbd_lock_bh_state(bh);
	spin_lock(&journal->j_list_lock);

	jh = journal_grab_journal_head(bh);
	if (!jh)
		goto zap_buffer_no_jh;

	transaction = jh->b_transaction;
	if (transaction == NULL) {
		/* First case: not on any transaction.  If it
		 * has no checkpoint link, then we can zap it:
		 * it's a writeback-mode buffer so we don't care
		 * if it hits disk safely. */
		if (!jh->b_cp_transaction) {
			JBUFFER_TRACE(jh, "not on any transaction: zap");
			goto zap_buffer;
		}

		if (!buffer_dirty(bh)) {
			/* bdflush has written it.  We can drop it now */
			goto zap_buffer;
		}

		/* OK, it must be in the journal but still not
		 * written fully to disk: it's metadata or
		 * journaled data... */

		if (journal->j_running_transaction) {
			/* ... and once the current transaction has
			 * committed, the buffer won't be needed any
			 * longer. */
			JBUFFER_TRACE(jh, "checkpointed: add to BJ_Forget");
			ret = __dispose_buffer(jh,
					journal->j_running_transaction);
			journal_put_journal_head(jh);
			spin_unlock(&journal->j_list_lock);
			jbd_unlock_bh_state(bh);
			spin_unlock(&journal->j_state_lock);
			return ret;
		} else {
			/* There is no currently-running transaction. So the
			 * orphan record which we wrote for this file must have
			 * passed into commit.  We must attach this buffer to
			 * the committing transaction, if it exists. */
			if (journal->j_committing_transaction) {
				JBUFFER_TRACE(jh, "give to committing trans");
				ret = __dispose_buffer(jh,
					journal->j_committing_transaction);
				journal_put_journal_head(jh);
				spin_unlock(&journal->j_list_lock);
				jbd_unlock_bh_state(bh);
				spin_unlock(&journal->j_state_lock);
				return ret;
			} else {
				/* The orphan record's transaction has
				 * committed.  We can cleanse this buffer */
				clear_buffer_jbddirty(bh);
				goto zap_buffer;
			}
		}
	} else if (transaction == journal->j_committing_transaction) {
		JBUFFER_TRACE(jh, "on committing transaction");
		if (jh->b_jlist == BJ_Locked) {
			/*
			 * The buffer is on the committing transaction's locked
			 * list.  We have the buffer locked, so I/O has
			 * completed.  So we can nail the buffer now.
			 */
			may_free = __dispose_buffer(jh, transaction);
			goto zap_buffer;
		}
		/*
		 * If it is committing, we simply cannot touch it.  We
		 * can remove it's next_transaction pointer from the
		 * running transaction if that is set, but nothing
		 * else. */
		set_buffer_freed(bh);
		if (jh->b_next_transaction) {
			J_ASSERT(jh->b_next_transaction ==
					journal->j_running_transaction);
			jh->b_next_transaction = NULL;
		}
		journal_put_journal_head(jh);
		spin_unlock(&journal->j_list_lock);
		jbd_unlock_bh_state(bh);
		spin_unlock(&journal->j_state_lock);
		return 0;
	} else {
		/* Good, the buffer belongs to the running transaction.
		 * We are writing our own transaction's data, not any
		 * previous one's, so it is safe to throw it away
		 * (remember that we expect the filesystem to have set
		 * i_size already for this truncate so recovery will not
		 * expose the disk blocks we are discarding here.) */
		J_ASSERT_JH(jh, transaction == journal->j_running_transaction);
		JBUFFER_TRACE(jh, "on running transaction");
		may_free = __dispose_buffer(jh, transaction);
	}

zap_buffer:
	journal_put_journal_head(jh);
zap_buffer_no_jh:
	spin_unlock(&journal->j_list_lock);
	jbd_unlock_bh_state(bh);
	spin_unlock(&journal->j_state_lock);
zap_buffer_unlocked:
	clear_buffer_dirty(bh);
	J_ASSERT_BH(bh, !buffer_jbddirty(bh));
	clear_buffer_mapped(bh);
	clear_buffer_req(bh);
	clear_buffer_new(bh);
	bh->b_bdev = NULL;
	return may_free;
}