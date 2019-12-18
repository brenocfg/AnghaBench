#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* t_journal; } ;
typedef  TYPE_1__ transaction_t ;
struct journal_head {scalar_t__ b_jlist; TYPE_1__* b_next_transaction; scalar_t__ b_modified; TYPE_1__* b_transaction; } ;
struct buffer_head {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  j_list_lock; TYPE_1__* j_committing_transaction; } ;
typedef  TYPE_2__ journal_t ;
struct TYPE_10__ {TYPE_1__* h_transaction; } ;
typedef  TYPE_3__ handle_t ;

/* Variables and functions */
 scalar_t__ BJ_Forget ; 
 int /*<<< orphan*/  BJ_Reserved ; 
 int EROFS ; 
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int /*<<< orphan*/  J_ASSERT_JH (struct journal_head*,int) ; 
 int /*<<< orphan*/  __journal_file_buffer (struct journal_head*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int buffer_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_buffer_dirty (int /*<<< orphan*/ ) ; 
 scalar_t__ is_handle_aborted (TYPE_3__*) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,struct journal_head*) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jh2bh (struct journal_head*) ; 
 struct journal_head* journal_add_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  journal_cancel_revoke (TYPE_3__*,struct journal_head*) ; 
 int /*<<< orphan*/  journal_put_journal_head (struct journal_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int journal_get_create_access(handle_t *handle, struct buffer_head *bh)
{
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal = transaction->t_journal;
	struct journal_head *jh = journal_add_journal_head(bh);
	int err;

	jbd_debug(5, "journal_head %p\n", jh);
	err = -EROFS;
	if (is_handle_aborted(handle))
		goto out;
	err = 0;

	JBUFFER_TRACE(jh, "entry");
	/*
	 * The buffer may already belong to this transaction due to pre-zeroing
	 * in the filesystem's new_block code.  It may also be on the previous,
	 * committing transaction's lists, but it HAS to be in Forget state in
	 * that case: the transaction must have deleted the buffer for it to be
	 * reused here.
	 */
	jbd_lock_bh_state(bh);
	spin_lock(&journal->j_list_lock);
	J_ASSERT_JH(jh, (jh->b_transaction == transaction ||
		jh->b_transaction == NULL ||
		(jh->b_transaction == journal->j_committing_transaction &&
			  jh->b_jlist == BJ_Forget)));

	J_ASSERT_JH(jh, jh->b_next_transaction == NULL);
	J_ASSERT_JH(jh, buffer_locked(jh2bh(jh)));

	if (jh->b_transaction == NULL) {
		/*
		 * Previous journal_forget() could have left the buffer
		 * with jbddirty bit set because it was being committed. When
		 * the commit finished, we've filed the buffer for
		 * checkpointing and marked it dirty. Now we are reallocating
		 * the buffer so the transaction freeing it must have
		 * committed and so it's safe to clear the dirty bit.
		 */
		clear_buffer_dirty(jh2bh(jh));
		jh->b_transaction = transaction;

		/* first access by this transaction */
		jh->b_modified = 0;

		JBUFFER_TRACE(jh, "file as BJ_Reserved");
		__journal_file_buffer(jh, transaction, BJ_Reserved);
	} else if (jh->b_transaction == journal->j_committing_transaction) {
		/* first access by this transaction */
		jh->b_modified = 0;

		JBUFFER_TRACE(jh, "set next transaction");
		jh->b_next_transaction = transaction;
	}
	spin_unlock(&journal->j_list_lock);
	jbd_unlock_bh_state(bh);

	/*
	 * akpm: I added this.  ext3_alloc_branch can pick up new indirect
	 * blocks which contain freed but then revoked metadata.  We need
	 * to cancel the revoke in case we end up freeing it yet again
	 * and the reallocating as data - this would cause a second revoke,
	 * which hits an assertion error.
	 */
	JBUFFER_TRACE(jh, "cancelling revoke");
	journal_cancel_revoke(handle, jh);
	journal_put_journal_head(jh);
out:
	return err;
}