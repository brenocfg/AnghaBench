#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* j_wbuf; scalar_t__ j_revoke; scalar_t__ j_inode; scalar_t__ j_proc_entry; scalar_t__ j_sb_buffer; scalar_t__ j_transaction_sequence; scalar_t__ j_tail_sequence; scalar_t__ j_tail; int /*<<< orphan*/  j_list_lock; int /*<<< orphan*/ * j_checkpoint_transactions; int /*<<< orphan*/ * j_committing_transaction; int /*<<< orphan*/ * j_running_transaction; int /*<<< orphan*/  j_checkpoint_mutex; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  J_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (scalar_t__) ; 
 int /*<<< orphan*/  iput (scalar_t__) ; 
 int /*<<< orphan*/  is_journal_aborted (TYPE_1__*) ; 
 int /*<<< orphan*/  jbd2_journal_commit_transaction (TYPE_1__*) ; 
 int /*<<< orphan*/  jbd2_journal_destroy_revoke (TYPE_1__*) ; 
 int /*<<< orphan*/  jbd2_journal_update_superblock (TYPE_1__*,int) ; 
 int /*<<< orphan*/  jbd2_log_do_checkpoint (TYPE_1__*) ; 
 int /*<<< orphan*/  jbd2_stats_proc_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  journal_kill_thread (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int jbd2_journal_destroy(journal_t *journal)
{
	int err = 0;

	/* Wait for the commit thread to wake up and die. */
	journal_kill_thread(journal);

	/* Force a final log commit */
	if (journal->j_running_transaction)
		jbd2_journal_commit_transaction(journal);

	/* Force any old transactions to disk */

	/* Totally anal locking here... */
	spin_lock(&journal->j_list_lock);
	while (journal->j_checkpoint_transactions != NULL) {
		spin_unlock(&journal->j_list_lock);
		mutex_lock(&journal->j_checkpoint_mutex);
		jbd2_log_do_checkpoint(journal);
		mutex_unlock(&journal->j_checkpoint_mutex);
		spin_lock(&journal->j_list_lock);
	}

	J_ASSERT(journal->j_running_transaction == NULL);
	J_ASSERT(journal->j_committing_transaction == NULL);
	J_ASSERT(journal->j_checkpoint_transactions == NULL);
	spin_unlock(&journal->j_list_lock);

	if (journal->j_sb_buffer) {
		if (!is_journal_aborted(journal)) {
			/* We can now mark the journal as empty. */
			journal->j_tail = 0;
			journal->j_tail_sequence =
				++journal->j_transaction_sequence;
			jbd2_journal_update_superblock(journal, 1);
		} else {
			err = -EIO;
		}
		brelse(journal->j_sb_buffer);
	}

	if (journal->j_proc_entry)
		jbd2_stats_proc_exit(journal);
	if (journal->j_inode)
		iput(journal->j_inode);
	if (journal->j_revoke)
		jbd2_journal_destroy_revoke(journal);
	kfree(journal->j_wbuf);
	kfree(journal);

	return err;
}