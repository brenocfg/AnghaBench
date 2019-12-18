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
struct ocfs2_super {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int /*<<< orphan*/ * d_fsdata; struct inode* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_blkno; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_move (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_dentry_attach_lock (struct dentry*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_dentry_lock_put (struct ocfs2_super*,int /*<<< orphan*/ *) ; 

void ocfs2_dentry_move(struct dentry *dentry, struct dentry *target,
		       struct inode *old_dir, struct inode *new_dir)
{
	int ret;
	struct ocfs2_super *osb = OCFS2_SB(old_dir->i_sb);
	struct inode *inode = dentry->d_inode;

	/*
	 * Move within the same directory, so the actual lock info won't
	 * change.
	 *
	 * XXX: Is there any advantage to dropping the lock here?
	 */
	if (old_dir == new_dir)
		goto out_move;

	ocfs2_dentry_lock_put(osb, dentry->d_fsdata);

	dentry->d_fsdata = NULL;
	ret = ocfs2_dentry_attach_lock(dentry, inode, OCFS2_I(new_dir)->ip_blkno);
	if (ret)
		mlog_errno(ret);

out_move:
	d_move(dentry, target);
}