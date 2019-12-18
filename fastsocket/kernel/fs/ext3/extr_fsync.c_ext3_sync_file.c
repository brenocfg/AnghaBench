#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct inode {TYPE_1__* i_sb; } ;
struct file {int dummy; } ;
struct ext3_inode_info {int /*<<< orphan*/  i_sync_tid; int /*<<< orphan*/  i_datasync_tid; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_6__ {int /*<<< orphan*/ * s_journal; } ;
struct TYPE_5__ {int s_flags; int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BARRIER ; 
 struct ext3_inode_info* EXT3_I (struct inode*) ; 
 TYPE_3__* EXT3_SB (TYPE_1__*) ; 
 int /*<<< orphan*/  J_ASSERT (int /*<<< orphan*/ ) ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkdev_issue_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ext3_force_commit (TYPE_1__*) ; 
 int /*<<< orphan*/ * ext3_journal_current_handle () ; 
 scalar_t__ ext3_should_journal_data (struct inode*) ; 
 scalar_t__ log_start_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_wait_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext3_sync_file_enter (struct file*,int) ; 
 int /*<<< orphan*/  trace_ext3_sync_file_exit (struct inode*,int) ; 

int ext3_sync_file(struct file * file, struct dentry *dentry, int datasync)
{
	struct inode *inode = dentry->d_inode;
	struct ext3_inode_info *ei = EXT3_I(inode);
	journal_t *journal = EXT3_SB(inode->i_sb)->s_journal;
	int ret = 0;
	tid_t commit_tid;

	J_ASSERT(ext3_journal_current_handle() == NULL);

	trace_ext3_sync_file_enter(file, datasync);

	if (inode->i_sb->s_flags & MS_RDONLY)
		return 0;


	/*
	 * data=writeback,ordered:
	 *  The caller's filemap_fdatawrite()/wait will sync the data.
	 *  Metadata is in the journal, we wait for a proper transaction
	 *  to commit here.
	 *
	 * data=journal:
	 *  filemap_fdatawrite won't do anything (the buffers are clean).
	 *  ext3_force_commit will write the file data into the journal and
	 *  will wait on that.
	 *  filemap_fdatawait() will encounter a ton of newly-dirtied pages
	 *  (they were dirtied by commit).  But that's OK - the blocks are
	 *  safe in-journal, which is all fsync() needs to ensure.
	 */
	if (ext3_should_journal_data(inode)) {
		ret = ext3_force_commit(inode->i_sb);
		goto out;
	}

	if (datasync)
		commit_tid = atomic_read(&ei->i_datasync_tid);
	else
		commit_tid = atomic_read(&ei->i_sync_tid);

	if (log_start_commit(journal, commit_tid)) {
		log_wait_commit(journal, commit_tid);
		goto out;
	}

	/*
	 * In case we didn't commit a transaction, we have to flush
	 * disk caches manually so that data really is on persistent
	 * storage
	 */
	if (test_opt(inode->i_sb, BARRIER))
		blkdev_issue_flush(inode->i_sb->s_bdev, NULL);
out:
	trace_ext3_sync_file_exit(inode, ret);
	return ret;
}