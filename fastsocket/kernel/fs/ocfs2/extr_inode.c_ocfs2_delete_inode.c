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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_2__ {int /*<<< orphan*/  ip_flags; int /*<<< orphan*/  ip_blkno; } ;

/* Variables and functions */
 int EDEADLK ; 
 int ENOENT ; 
 int /*<<< orphan*/  ML_ERROR ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INODE_DELETED ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  ocfs2_cleanup_delete_inode (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_inode_is_valid_to_delete (struct inode*) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_nfs_sync_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_nfs_sync_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_query_inode_wipe (struct inode*,struct buffer_head*,int*) ; 
 int ocfs2_wipe_inode (struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ocfs2_delete_inode(struct inode *inode)
{
	int wipe, status;
	sigset_t blocked, oldset;
	struct buffer_head *di_bh = NULL;

	mlog_entry("(inode->i_ino = %lu)\n", inode->i_ino);

	/* When we fail in read_inode() we mark inode as bad. The second test
	 * catches the case when inode allocation fails before allocating
	 * a block for inode. */
	if (is_bad_inode(inode) || !OCFS2_I(inode)->ip_blkno) {
		mlog(0, "Skipping delete of bad inode\n");
		goto bail;
	}

	if (!ocfs2_inode_is_valid_to_delete(inode)) {
		/* It's probably not necessary to truncate_inode_pages
		 * here but we do it for safety anyway (it will most
		 * likely be a no-op anyway) */
		ocfs2_cleanup_delete_inode(inode, 0);
		goto bail;
	}

	/* We want to block signals in delete_inode as the lock and
	 * messaging paths may return us -ERESTARTSYS. Which would
	 * cause us to exit early, resulting in inodes being orphaned
	 * forever. */
	sigfillset(&blocked);
	status = sigprocmask(SIG_BLOCK, &blocked, &oldset);
	if (status < 0) {
		mlog_errno(status);
		ocfs2_cleanup_delete_inode(inode, 1);
		goto bail;
	}

	/*
	 * Synchronize us against ocfs2_get_dentry. We take this in
	 * shared mode so that all nodes can still concurrently
	 * process deletes.
	 */
	status = ocfs2_nfs_sync_lock(OCFS2_SB(inode->i_sb), 0);
	if (status < 0) {
		mlog(ML_ERROR, "getting nfs sync lock(PR) failed %d\n", status);
		ocfs2_cleanup_delete_inode(inode, 0);
		goto bail_unblock;
	}
	/* Lock down the inode. This gives us an up to date view of
	 * it's metadata (for verification), and allows us to
	 * serialize delete_inode on multiple nodes.
	 *
	 * Even though we might be doing a truncate, we don't take the
	 * allocation lock here as it won't be needed - nobody will
	 * have the file open.
	 */
	status = ocfs2_inode_lock(inode, &di_bh, 1);
	if (status < 0) {
		if (status != -ENOENT)
			mlog_errno(status);
		ocfs2_cleanup_delete_inode(inode, 0);
		goto bail_unlock_nfs_sync;
	}

	/* Query the cluster. This will be the final decision made
	 * before we go ahead and wipe the inode. */
	status = ocfs2_query_inode_wipe(inode, di_bh, &wipe);
	if (!wipe || status < 0) {
		/* Error and remote inode busy both mean we won't be
		 * removing the inode, so they take almost the same
		 * path. */
		if (status < 0)
			mlog_errno(status);

		/* Someone in the cluster has disallowed a wipe of
		 * this inode, or it was never completely
		 * orphaned. Write out the pages and exit now. */
		ocfs2_cleanup_delete_inode(inode, 1);
		goto bail_unlock_inode;
	}

	ocfs2_cleanup_delete_inode(inode, 0);

	status = ocfs2_wipe_inode(inode, di_bh);
	if (status < 0) {
		if (status != -EDEADLK)
			mlog_errno(status);
		goto bail_unlock_inode;
	}

	/*
	 * Mark the inode as successfully deleted.
	 *
	 * This is important for ocfs2_clear_inode() as it will check
	 * this flag and skip any checkpointing work
	 *
	 * ocfs2_stuff_meta_lvb() also uses this flag to invalidate
	 * the LVB for other nodes.
	 */
	OCFS2_I(inode)->ip_flags |= OCFS2_INODE_DELETED;

bail_unlock_inode:
	ocfs2_inode_unlock(inode, 1);
	brelse(di_bh);

bail_unlock_nfs_sync:
	ocfs2_nfs_sync_unlock(OCFS2_SB(inode->i_sb), 0);

bail_unblock:
	status = sigprocmask(SIG_SETMASK, &oldset, NULL);
	if (status < 0)
		mlog_errno(status);
bail:
	clear_inode(inode);
	mlog_exit_void();
}