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
struct ocfs2_super {struct ocfs2_journal* journal; int /*<<< orphan*/ * commit_task; } ;
struct ocfs2_journal {scalar_t__ j_state; int /*<<< orphan*/ * j_bh; int /*<<< orphan*/ * j_journal; int /*<<< orphan*/  j_num_trans; struct inode* j_inode; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_open_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 scalar_t__ OCFS2_JOURNAL_FREE ; 
 scalar_t__ OCFS2_JOURNAL_IN_SHUTDOWN ; 
 scalar_t__ OCFS2_JOURNAL_LOADED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  jbd2_journal_destroy (int /*<<< orphan*/ *) ; 
 int jbd2_journal_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_lock_updates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_unlock_updates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_journal_toggle_dirty (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_mount_local (struct ocfs2_super*) ; 

void ocfs2_journal_shutdown(struct ocfs2_super *osb)
{
	struct ocfs2_journal *journal = NULL;
	int status = 0;
	struct inode *inode = NULL;
	int num_running_trans = 0;

	mlog_entry_void();

	BUG_ON(!osb);

	journal = osb->journal;
	if (!journal)
		goto done;

	inode = journal->j_inode;

	if (journal->j_state != OCFS2_JOURNAL_LOADED)
		goto done;

	/* need to inc inode use count - jbd2_journal_destroy will iput. */
	if (!igrab(inode))
		BUG();

	num_running_trans = atomic_read(&(osb->journal->j_num_trans));
	if (num_running_trans > 0)
		mlog(0, "Shutting down journal: must wait on %d "
		     "running transactions!\n",
		     num_running_trans);

	/* Do a commit_cache here. It will flush our journal, *and*
	 * release any locks that are still held.
	 * set the SHUTDOWN flag and release the trans lock.
	 * the commit thread will take the trans lock for us below. */
	journal->j_state = OCFS2_JOURNAL_IN_SHUTDOWN;

	/* The OCFS2_JOURNAL_IN_SHUTDOWN will signal to commit_cache to not
	 * drop the trans_lock (which we want to hold until we
	 * completely destroy the journal. */
	if (osb->commit_task) {
		/* Wait for the commit thread */
		mlog(0, "Waiting for ocfs2commit to exit....\n");
		kthread_stop(osb->commit_task);
		osb->commit_task = NULL;
	}

	BUG_ON(atomic_read(&(osb->journal->j_num_trans)) != 0);

	if (ocfs2_mount_local(osb)) {
		jbd2_journal_lock_updates(journal->j_journal);
		status = jbd2_journal_flush(journal->j_journal);
		jbd2_journal_unlock_updates(journal->j_journal);
		if (status < 0)
			mlog_errno(status);
	}

	if (status == 0) {
		/*
		 * Do not toggle if flush was unsuccessful otherwise
		 * will leave dirty metadata in a "clean" journal
		 */
		status = ocfs2_journal_toggle_dirty(osb, 0, 0);
		if (status < 0)
			mlog_errno(status);
	}

	/* Shutdown the kernel journal system */
	jbd2_journal_destroy(journal->j_journal);
	journal->j_journal = NULL;

	OCFS2_I(inode)->ip_open_count--;

	/* unlock our journal */
	ocfs2_inode_unlock(inode, 1);

	brelse(journal->j_bh);
	journal->j_bh = NULL;

	journal->j_state = OCFS2_JOURNAL_FREE;

//	up_write(&journal->j_trans_barrier);
done:
	if (inode)
		iput(inode);
	mlog_exit_void();
}