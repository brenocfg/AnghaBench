#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct inode {TYPE_4__* i_sb; } ;
struct file {int dummy; } ;
struct ext4_inode_info {int /*<<< orphan*/  i_sync_tid; int /*<<< orphan*/  i_datasync_tid; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_7__ {int j_flags; } ;
typedef  TYPE_1__ journal_t ;
struct TYPE_9__ {TYPE_1__* s_journal; } ;
struct TYPE_8__ {int s_flags; int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 TYPE_5__* EXT4_SB (TYPE_4__*) ; 
 int JBD2_BARRIER ; 
 int /*<<< orphan*/  J_ASSERT (int /*<<< orphan*/ ) ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  blkdev_issue_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ext4_force_commit (TYPE_4__*) ; 
 int /*<<< orphan*/ * ext4_journal_current_handle () ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 int flush_aio_dio_completed_IO (struct inode*) ; 
 int jbd2_complete_transaction (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_trans_will_send_data_barrier (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int simple_fsync (struct file*,struct dentry*,int) ; 
 int /*<<< orphan*/  trace_ext4_sync_file (struct file*,struct dentry*,int) ; 

int ext4_sync_file(struct file *file, struct dentry *dentry, int datasync)
{
	struct inode *inode = dentry->d_inode;
	struct ext4_inode_info *ei = EXT4_I(inode);
	journal_t *journal = EXT4_SB(inode->i_sb)->s_journal;
	int ret;
	tid_t commit_tid;
	bool needs_barrier = false;

	J_ASSERT(ext4_journal_current_handle() == NULL);

	trace_ext4_sync_file(file, dentry, datasync);

	if (inode->i_sb->s_flags & MS_RDONLY)
		return 0;

	ret = flush_aio_dio_completed_IO(inode);
	if (ret < 0)
		return ret;

	if (!journal)
		return simple_fsync(file, dentry, datasync);

	/*
	 * data=writeback,ordered:
	 *  The caller's filemap_fdatawrite()/wait will sync the data.
	 *  Metadata is in the journal, we wait for proper transaction to
	 *  commit here.
	 *
	 * data=journal:
	 *  filemap_fdatawrite won't do anything (the buffers are clean).
	 *  ext4_force_commit will write the file data into the journal and
	 *  will wait on that.
	 *  filemap_fdatawait() will encounter a ton of newly-dirtied pages
	 *  (they were dirtied by commit).  But that's OK - the blocks are
	 *  safe in-journal, which is all fsync() needs to ensure.
	 */
	if (ext4_should_journal_data(inode))
		return ext4_force_commit(inode->i_sb);

	commit_tid = datasync ? ei->i_datasync_tid : ei->i_sync_tid;
	if (journal->j_flags & JBD2_BARRIER &&
	    !jbd2_trans_will_send_data_barrier(journal, commit_tid))
		needs_barrier = true;
	ret = jbd2_complete_transaction(journal, commit_tid);
	if (needs_barrier)
		blkdev_issue_flush(inode->i_sb->s_bdev, NULL);
	return ret;
}