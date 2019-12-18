#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  t_tid; } ;
typedef  TYPE_1__ transaction_t ;
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_11__ {unsigned int j_tail; unsigned int j_head; scalar_t__ j_tail_sequence; scalar_t__ j_transaction_sequence; int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/ * j_checkpoint_transactions; TYPE_1__* j_committing_transaction; TYPE_1__* j_running_transaction; int /*<<< orphan*/  j_list_lock; int /*<<< orphan*/  j_checkpoint_mutex; } ;
typedef  TYPE_2__ journal_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  J_ASSERT (int) ; 
 int /*<<< orphan*/  __log_start_commit (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_journal_tail (TYPE_2__*) ; 
 scalar_t__ is_journal_aborted (TYPE_2__*) ; 
 int /*<<< orphan*/  journal_update_superblock (TYPE_2__*,int) ; 
 int log_do_checkpoint (TYPE_2__*) ; 
 int /*<<< orphan*/  log_wait_commit (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int journal_flush(journal_t *journal)
{
	int err = 0;
	transaction_t *transaction = NULL;
	unsigned int old_tail;

	spin_lock(&journal->j_state_lock);

	/* Force everything buffered to the log... */
	if (journal->j_running_transaction) {
		transaction = journal->j_running_transaction;
		__log_start_commit(journal, transaction->t_tid);
	} else if (journal->j_committing_transaction)
		transaction = journal->j_committing_transaction;

	/* Wait for the log commit to complete... */
	if (transaction) {
		tid_t tid = transaction->t_tid;

		spin_unlock(&journal->j_state_lock);
		log_wait_commit(journal, tid);
	} else {
		spin_unlock(&journal->j_state_lock);
	}

	/* ...and flush everything in the log out to disk. */
	spin_lock(&journal->j_list_lock);
	while (!err && journal->j_checkpoint_transactions != NULL) {
		spin_unlock(&journal->j_list_lock);
		mutex_lock(&journal->j_checkpoint_mutex);
		err = log_do_checkpoint(journal);
		mutex_unlock(&journal->j_checkpoint_mutex);
		spin_lock(&journal->j_list_lock);
	}
	spin_unlock(&journal->j_list_lock);

	if (is_journal_aborted(journal))
		return -EIO;

	cleanup_journal_tail(journal);

	/* Finally, mark the journal as really needing no recovery.
	 * This sets s_start==0 in the underlying superblock, which is
	 * the magic code for a fully-recovered superblock.  Any future
	 * commits of data to the journal will restore the current
	 * s_start value. */
	spin_lock(&journal->j_state_lock);
	old_tail = journal->j_tail;
	journal->j_tail = 0;
	spin_unlock(&journal->j_state_lock);
	journal_update_superblock(journal, 1);
	spin_lock(&journal->j_state_lock);
	journal->j_tail = old_tail;

	J_ASSERT(!journal->j_running_transaction);
	J_ASSERT(!journal->j_committing_transaction);
	J_ASSERT(!journal->j_checkpoint_transactions);
	J_ASSERT(journal->j_head == journal->j_tail);
	J_ASSERT(journal->j_tail_sequence == journal->j_transaction_sequence);
	spin_unlock(&journal->j_state_lock);
	return 0;
}