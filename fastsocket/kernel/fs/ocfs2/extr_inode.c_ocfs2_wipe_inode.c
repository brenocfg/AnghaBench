#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ocfs2_super {int dummy; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_orphaned_slot; } ;
struct inode {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int EEXIST ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ORPHAN_DIR_SYSTEM_INODE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ocfs2_check_orphan_recovery_state (struct ocfs2_super*,int) ; 
 int ocfs2_dx_dir_truncate (struct inode*,struct buffer_head*) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_remove_inode (struct inode*,struct buffer_head*,struct inode*,struct buffer_head*) ; 
 int ocfs2_remove_refcount_tree (struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_signal_wipe_completion (struct ocfs2_super*,int) ; 
 int ocfs2_truncate_for_delete (struct ocfs2_super*,struct inode*,struct buffer_head*) ; 
 int ocfs2_xattr_remove (struct inode*,struct buffer_head*) ; 

__attribute__((used)) static int ocfs2_wipe_inode(struct inode *inode,
			    struct buffer_head *di_bh)
{
	int status, orphaned_slot;
	struct inode *orphan_dir_inode = NULL;
	struct buffer_head *orphan_dir_bh = NULL;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_dinode *di;

	di = (struct ocfs2_dinode *) di_bh->b_data;
	orphaned_slot = le16_to_cpu(di->i_orphaned_slot);

	status = ocfs2_check_orphan_recovery_state(osb, orphaned_slot);
	if (status)
		return status;

	orphan_dir_inode = ocfs2_get_system_file_inode(osb,
						       ORPHAN_DIR_SYSTEM_INODE,
						       orphaned_slot);
	if (!orphan_dir_inode) {
		status = -EEXIST;
		mlog_errno(status);
		goto bail;
	}

	/* Lock the orphan dir. The lock will be held for the entire
	 * delete_inode operation. We do this now to avoid races with
	 * recovery completion on other nodes. */
	mutex_lock(&orphan_dir_inode->i_mutex);
	status = ocfs2_inode_lock(orphan_dir_inode, &orphan_dir_bh, 1);
	if (status < 0) {
		mutex_unlock(&orphan_dir_inode->i_mutex);

		mlog_errno(status);
		goto bail;
	}

	/* we do this while holding the orphan dir lock because we
	 * don't want recovery being run from another node to try an
	 * inode delete underneath us -- this will result in two nodes
	 * truncating the same file! */
	status = ocfs2_truncate_for_delete(osb, inode, di_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail_unlock_dir;
	}

	/* Remove any dir index tree */
	if (S_ISDIR(inode->i_mode)) {
		status = ocfs2_dx_dir_truncate(inode, di_bh);
		if (status) {
			mlog_errno(status);
			goto bail_unlock_dir;
		}
	}

	/*Free extended attribute resources associated with this inode.*/
	status = ocfs2_xattr_remove(inode, di_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail_unlock_dir;
	}

	status = ocfs2_remove_refcount_tree(inode, di_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail_unlock_dir;
	}

	status = ocfs2_remove_inode(inode, di_bh, orphan_dir_inode,
				    orphan_dir_bh);
	if (status < 0)
		mlog_errno(status);

bail_unlock_dir:
	ocfs2_inode_unlock(orphan_dir_inode, 1);
	mutex_unlock(&orphan_dir_inode->i_mutex);
	brelse(orphan_dir_bh);
bail:
	iput(orphan_dir_inode);
	ocfs2_signal_wipe_completion(osb, orphaned_slot);

	return status;
}