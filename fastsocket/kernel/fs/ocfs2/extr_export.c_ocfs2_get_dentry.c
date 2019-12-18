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
typedef  scalar_t__ u64 ;
struct super_block {int dummy; } ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_inode_handle {scalar_t__ ih_blkno; scalar_t__ ih_generation; } ;
struct inode {scalar_t__ i_generation; int /*<<< orphan*/ * d_op; } ;
struct dentry {scalar_t__ i_generation; int /*<<< orphan*/ * d_op; } ;

/* Variables and functions */
 int EINVAL ; 
 struct inode* ERR_PTR (int) ; 
 int ESTALE ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 int /*<<< orphan*/  PTR_ERR (struct inode*) ; 
 struct inode* d_obtain_alias (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct super_block*,struct ocfs2_inode_handle*) ; 
 int /*<<< orphan*/  mlog_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_exit_ptr (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_dentry_ops ; 
 struct inode* ocfs2_iget (struct ocfs2_super*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* ocfs2_ilookup (struct super_block*,scalar_t__) ; 
 int ocfs2_nfs_sync_lock (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_nfs_sync_unlock (struct ocfs2_super*,int) ; 
 int ocfs2_test_inode_bit (struct ocfs2_super*,scalar_t__,int*) ; 

__attribute__((used)) static struct dentry *ocfs2_get_dentry(struct super_block *sb,
		struct ocfs2_inode_handle *handle)
{
	struct inode *inode;
	struct ocfs2_super *osb = OCFS2_SB(sb);
	u64 blkno = handle->ih_blkno;
	int status, set;
	struct dentry *result;

	mlog_entry("(0x%p, 0x%p)\n", sb, handle);

	if (blkno == 0) {
		mlog(0, "nfs wants inode with blkno: 0\n");
		result = ERR_PTR(-ESTALE);
		goto bail;
	}

	inode = ocfs2_ilookup(sb, blkno);
	/*
	 * If the inode exists in memory, we only need to check it's
	 * generation number
	 */
	if (inode)
		goto check_gen;

	/*
	 * This will synchronize us against ocfs2_delete_inode() on
	 * all nodes
	 */
	status = ocfs2_nfs_sync_lock(osb, 1);
	if (status < 0) {
		mlog(ML_ERROR, "getting nfs sync lock(EX) failed %d\n", status);
		goto check_err;
	}

	status = ocfs2_test_inode_bit(osb, blkno, &set);
	if (status < 0) {
		if (status == -EINVAL) {
			/*
			 * The blkno NFS gave us doesn't even show up
			 * as an inode, we return -ESTALE to be
			 * nice
			 */
			mlog(0, "test inode bit failed %d\n", status);
			status = -ESTALE;
		} else {
			mlog(ML_ERROR, "test inode bit failed %d\n", status);
		}
		goto unlock_nfs_sync;
	}

	/* If the inode allocator bit is clear, this inode must be stale */
	if (!set) {
		mlog(0, "inode %llu suballoc bit is clear\n",
		     (unsigned long long)blkno);
		status = -ESTALE;
		goto unlock_nfs_sync;
	}

	inode = ocfs2_iget(osb, blkno, 0, 0);

unlock_nfs_sync:
	ocfs2_nfs_sync_unlock(osb, 1);

check_err:
	if (status < 0) {
		if (status == -ESTALE) {
			mlog(0, "stale inode ino: %llu generation: %u\n",
			     (unsigned long long)blkno, handle->ih_generation);
		}
		result = ERR_PTR(status);
		goto bail;
	}

	if (IS_ERR(inode)) {
		mlog_errno(PTR_ERR(inode));
		result = (void *)inode;
		goto bail;
	}

check_gen:
	if (handle->ih_generation != inode->i_generation) {
		iput(inode);
		mlog(0, "stale inode ino: %llu generation: %u\n",
		     (unsigned long long)blkno, handle->ih_generation);
		result = ERR_PTR(-ESTALE);
		goto bail;
	}

	result = d_obtain_alias(inode);
	if (!IS_ERR(result))
		result->d_op = &ocfs2_dentry_ops;
	else
		mlog_errno(PTR_ERR(result));

bail:
	mlog_exit_ptr(result);
	return result;
}