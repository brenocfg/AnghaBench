#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {TYPE_2__* sb; int /*<<< orphan*/  root_blkno; } ;
struct ocfs2_dir_lookup_result {int /*<<< orphan*/ * member_0; } ;
struct ocfs2_dinode {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_7__ {int /*<<< orphan*/  ip_blkno; } ;
struct TYPE_6__ {TYPE_1__* dq_op; } ;
struct TYPE_5__ {scalar_t__ (* alloc_inode ) (struct inode*,int) ;} ;

/* Variables and functions */
 int EDQUOT ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSPC ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ NO_QUOTA ; 
 TYPE_4__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_ORPHAN_NAMELEN ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ocfs2_blkno_stringify (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_free_dir_lookup_result (struct ocfs2_dir_lookup_result*) ; 
 struct inode* ocfs2_get_init_inode (struct inode*,int) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_mknod_credits (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_mknod_locked (struct ocfs2_super*,struct inode*,struct inode*,int /*<<< orphan*/ ,struct buffer_head**,struct buffer_head*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*) ; 
 int ocfs2_open_lock (struct inode*) ; 
 int ocfs2_orphan_add (struct ocfs2_super*,int /*<<< orphan*/ *,struct inode*,struct ocfs2_dinode*,char*,struct ocfs2_dir_lookup_result*,struct inode*) ; 
 int ocfs2_prepare_orphan_dir (struct ocfs2_super*,struct inode**,int /*<<< orphan*/ ,char*,struct ocfs2_dir_lookup_result*) ; 
 int ocfs2_reserve_new_inode (struct ocfs2_super*,struct ocfs2_alloc_context**) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 scalar_t__ sb_any_quota_active (TYPE_2__*) ; 
 scalar_t__ stub1 (struct inode*,int) ; 
 int /*<<< orphan*/  vfs_dq_free_inode (struct inode*) ; 

int ocfs2_create_inode_in_orphan(struct inode *dir,
				 int mode,
				 struct inode **new_inode)
{
	int status, did_quota_inode = 0;
	struct inode *inode = NULL;
	struct inode *orphan_dir = NULL;
	struct ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	struct ocfs2_dinode *di = NULL;
	handle_t *handle = NULL;
	char orphan_name[OCFS2_ORPHAN_NAMELEN + 1];
	struct buffer_head *parent_di_bh = NULL;
	struct buffer_head *new_di_bh = NULL;
	struct ocfs2_alloc_context *inode_ac = NULL;
	struct ocfs2_dir_lookup_result orphan_insert = { NULL, };

	status = ocfs2_inode_lock(dir, &parent_di_bh, 1);
	if (status < 0) {
		if (status != -ENOENT)
			mlog_errno(status);
		return status;
	}

	/*
	 * We give the orphan dir the root blkno to fake an orphan name,
	 * and allocate enough space for our insertion.
	 */
	status = ocfs2_prepare_orphan_dir(osb, &orphan_dir,
					  osb->root_blkno,
					  orphan_name, &orphan_insert);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	/* reserve an inode spot */
	status = ocfs2_reserve_new_inode(osb, &inode_ac);
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto leave;
	}

	inode = ocfs2_get_init_inode(dir, mode);
	if (!inode) {
		status = -ENOMEM;
		mlog_errno(status);
		goto leave;
	}

	handle = ocfs2_start_trans(osb, ocfs2_mknod_credits(osb->sb, 0, 0));
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		handle = NULL;
		mlog_errno(status);
		goto leave;
	}

	/* We don't use standard VFS wrapper because we don't want vfs_dq_init
	 * to be called. */
	if (sb_any_quota_active(osb->sb) &&
	    osb->sb->dq_op->alloc_inode(inode, 1) == NO_QUOTA) {
		status = -EDQUOT;
		goto leave;
	}
	did_quota_inode = 1;

	/* do the real work now. */
	status = ocfs2_mknod_locked(osb, dir, inode,
				    0, &new_di_bh, parent_di_bh, handle,
				    inode_ac);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	status = ocfs2_blkno_stringify(OCFS2_I(inode)->ip_blkno, orphan_name);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	di = (struct ocfs2_dinode *)new_di_bh->b_data;
	status = ocfs2_orphan_add(osb, handle, inode, di, orphan_name,
				  &orphan_insert, orphan_dir);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	/* get open lock so that only nodes can't remove it from orphan dir. */
	status = ocfs2_open_lock(inode);
	if (status < 0)
		mlog_errno(status);

leave:
	if (status < 0 && did_quota_inode)
		vfs_dq_free_inode(inode);
	if (handle)
		ocfs2_commit_trans(osb, handle);

	if (orphan_dir) {
		/* This was locked for us in ocfs2_prepare_orphan_dir() */
		ocfs2_inode_unlock(orphan_dir, 1);
		mutex_unlock(&orphan_dir->i_mutex);
		iput(orphan_dir);
	}

	if (status == -ENOSPC)
		mlog(0, "Disk is full\n");

	if ((status < 0) && inode) {
		clear_nlink(inode);
		iput(inode);
	}

	if (inode_ac)
		ocfs2_free_alloc_context(inode_ac);

	brelse(new_di_bh);

	if (!status)
		*new_inode = inode;

	ocfs2_free_dir_lookup_result(&orphan_insert);

	ocfs2_inode_unlock(dir, 1);
	brelse(parent_di_bh);
	return status;
}