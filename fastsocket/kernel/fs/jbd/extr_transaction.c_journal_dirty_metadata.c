#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* t_journal; } ;
typedef  TYPE_1__ transaction_t ;
struct journal_head {int b_modified; scalar_t__ b_jlist; int /*<<< orphan*/ * b_frozen_data; TYPE_1__* b_next_transaction; TYPE_1__* b_transaction; } ;
struct buffer_head {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  j_list_lock; TYPE_1__* j_committing_transaction; TYPE_1__* j_running_transaction; } ;
typedef  TYPE_2__ journal_t ;
struct TYPE_9__ {scalar_t__ h_buffer_credits; TYPE_1__* h_transaction; } ;
typedef  TYPE_3__ handle_t ;

/* Variables and functions */
 scalar_t__ BJ_Metadata ; 
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int /*<<< orphan*/  J_ASSERT_JH (struct journal_head*,int) ; 
 int /*<<< orphan*/  __journal_file_buffer (struct journal_head*,TYPE_1__*,scalar_t__) ; 
 struct journal_head* bh2jh (struct buffer_head*) ; 
 scalar_t__ is_handle_aborted (TYPE_3__*) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,struct journal_head*) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_jbddirty (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int journal_dirty_metadata(handle_t *handle, struct buffer_head *bh)
{
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal = transaction->t_journal;
	struct journal_head *jh = bh2jh(bh);

	jbd_debug(5, "journal_head %p\n", jh);
	JBUFFER_TRACE(jh, "entry");
	if (is_handle_aborted(handle))
		goto out;

	jbd_lock_bh_state(bh);

	if (jh->b_modified == 0) {
		/*
		 * This buffer's got modified and becoming part
		 * of the transaction. This needs to be done
		 * once a transaction -bzzz
		 */
		jh->b_modified = 1;
		J_ASSERT_JH(jh, handle->h_buffer_credits > 0);
		handle->h_buffer_credits--;
	}

	/*
	 * fastpath, to avoid expensive locking.  If this buffer is already
	 * on the running transaction's metadata list there is nothing to do.
	 * Nobody can take it off again because there is a handle open.
	 * I _think_ we're OK here with SMP barriers - a mistaken decision will
	 * result in this test being false, so we go in and take the locks.
	 */
	if (jh->b_transaction == transaction && jh->b_jlist == BJ_Metadata) {
		JBUFFER_TRACE(jh, "fastpath");
		J_ASSERT_JH(jh, jh->b_transaction ==
					journal->j_running_transaction);
		goto out_unlock_bh;
	}

	set_buffer_jbddirty(bh);

	/*
	 * Metadata already on the current transaction list doesn't
	 * need to be filed.  Metadata on another transaction's list must
	 * be committing, and will be refiled once the commit completes:
	 * leave it alone for now.
	 */
	if (jh->b_transaction != transaction) {
		JBUFFER_TRACE(jh, "already on other transaction");
		J_ASSERT_JH(jh, jh->b_transaction ==
					journal->j_committing_transaction);
		J_ASSERT_JH(jh, jh->b_next_transaction == transaction);
		/* And this case is illegal: we can't reuse another
		 * transaction's data buffer, ever. */
		goto out_unlock_bh;
	}

	/* That test should have eliminated the following case: */
	J_ASSERT_JH(jh, jh->b_frozen_data == NULL);

	JBUFFER_TRACE(jh, "file as BJ_Metadata");
	spin_lock(&journal->j_list_lock);
	__journal_file_buffer(jh, handle->h_transaction, BJ_Metadata);
	spin_unlock(&journal->j_list_lock);
out_unlock_bh:
	jbd_unlock_bh_state(bh);
out:
	JBUFFER_TRACE(jh, "exit");
	return 0;
}