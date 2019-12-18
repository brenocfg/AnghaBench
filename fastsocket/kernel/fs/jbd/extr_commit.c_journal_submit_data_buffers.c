#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct journal_head* t_sync_datalist; } ;
typedef  TYPE_1__ transaction_t ;
struct journal_head {scalar_t__ b_jlist; TYPE_1__* b_transaction; } ;
struct buffer_head {int dummy; } ;
struct TYPE_10__ {int j_wbufsize; int /*<<< orphan*/  j_list_lock; struct buffer_head** j_wbuf; } ;
typedef  TYPE_2__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  BJ_Locked ; 
 scalar_t__ BJ_SyncData ; 
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int EIO ; 
 int /*<<< orphan*/  __journal_file_buffer (struct journal_head*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __journal_unfile_buffer (struct journal_head*) ; 
 struct journal_head* bh2jh (struct buffer_head*) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_jbd (struct buffer_head*) ; 
 scalar_t__ buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  inverted_lock (TYPE_2__*,struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 struct buffer_head* jh2bh (struct journal_head*) ; 
 int /*<<< orphan*/  journal_do_submit_data (struct buffer_head**,int,int) ; 
 int /*<<< orphan*/  journal_remove_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  release_data_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ spin_needbreak (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  trace_jbd_do_submit_data (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  trylock_buffer (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int journal_submit_data_buffers(journal_t *journal,
				       transaction_t *commit_transaction,
				       int write_op)
{
	struct journal_head *jh;
	struct buffer_head *bh;
	int locked;
	int bufs = 0;
	struct buffer_head **wbuf = journal->j_wbuf;
	int err = 0;

	/*
	 * Whenever we unlock the journal and sleep, things can get added
	 * onto ->t_sync_datalist, so we have to keep looping back to
	 * write_out_data until we *know* that the list is empty.
	 *
	 * Cleanup any flushed data buffers from the data list.  Even in
	 * abort mode, we want to flush this out as soon as possible.
	 */
write_out_data:
	cond_resched();
	spin_lock(&journal->j_list_lock);

	while (commit_transaction->t_sync_datalist) {
		jh = commit_transaction->t_sync_datalist;
		bh = jh2bh(jh);
		locked = 0;

		/* Get reference just to make sure buffer does not disappear
		 * when we are forced to drop various locks */
		get_bh(bh);
		/* If the buffer is dirty, we need to submit IO and hence
		 * we need the buffer lock. We try to lock the buffer without
		 * blocking. If we fail, we need to drop j_list_lock and do
		 * blocking lock_buffer().
		 */
		if (buffer_dirty(bh)) {
			if (!trylock_buffer(bh)) {
				BUFFER_TRACE(bh, "needs blocking lock");
				spin_unlock(&journal->j_list_lock);
				trace_jbd_do_submit_data(journal,
						     commit_transaction);
				/* Write out all data to prevent deadlocks */
				journal_do_submit_data(wbuf, bufs, write_op);
				bufs = 0;
				lock_buffer(bh);
				spin_lock(&journal->j_list_lock);
			}
			locked = 1;
		}
		/* We have to get bh_state lock. Again out of order, sigh. */
		if (!inverted_lock(journal, bh)) {
			jbd_lock_bh_state(bh);
			spin_lock(&journal->j_list_lock);
		}
		/* Someone already cleaned up the buffer? */
		if (!buffer_jbd(bh) || bh2jh(bh) != jh
			|| jh->b_transaction != commit_transaction
			|| jh->b_jlist != BJ_SyncData) {
			jbd_unlock_bh_state(bh);
			if (locked)
				unlock_buffer(bh);
			BUFFER_TRACE(bh, "already cleaned up");
			release_data_buffer(bh);
			continue;
		}
		if (locked && test_clear_buffer_dirty(bh)) {
			BUFFER_TRACE(bh, "needs writeout, adding to array");
			wbuf[bufs++] = bh;
			__journal_file_buffer(jh, commit_transaction,
						BJ_Locked);
			jbd_unlock_bh_state(bh);
			if (bufs == journal->j_wbufsize) {
				spin_unlock(&journal->j_list_lock);
				trace_jbd_do_submit_data(journal,
						     commit_transaction);
				journal_do_submit_data(wbuf, bufs, write_op);
				bufs = 0;
				goto write_out_data;
			}
		} else if (!locked && buffer_locked(bh)) {
			__journal_file_buffer(jh, commit_transaction,
						BJ_Locked);
			jbd_unlock_bh_state(bh);
			put_bh(bh);
		} else {
			BUFFER_TRACE(bh, "writeout complete: unfile");
			if (unlikely(!buffer_uptodate(bh)))
				err = -EIO;
			__journal_unfile_buffer(jh);
			jbd_unlock_bh_state(bh);
			if (locked)
				unlock_buffer(bh);
			journal_remove_journal_head(bh);
			/* One for our safety reference, other for
			 * journal_remove_journal_head() */
			put_bh(bh);
			release_data_buffer(bh);
		}

		if (need_resched() || spin_needbreak(&journal->j_list_lock)) {
			spin_unlock(&journal->j_list_lock);
			goto write_out_data;
		}
	}
	spin_unlock(&journal->j_list_lock);
	trace_jbd_do_submit_data(journal, commit_transaction);
	journal_do_submit_data(wbuf, bufs, write_op);

	return err;
}