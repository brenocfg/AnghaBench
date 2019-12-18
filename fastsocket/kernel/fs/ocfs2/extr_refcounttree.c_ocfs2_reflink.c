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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct dentry {struct inode* d_inode; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_xattr_sem; int /*<<< orphan*/  ip_alloc_sem; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int __ocfs2_reflink (struct dentry*,struct buffer_head*,struct inode*,int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_create_inode_in_orphan (struct inode*,int /*<<< orphan*/ ,struct inode**) ; 
 int ocfs2_init_security_and_acl (struct inode*,struct inode*) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_mv_orphaned_inode_to_new (struct inode*,struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  ocfs2_open_unlock (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_refcount_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_reflink(struct dentry *old_dentry, struct inode *dir,
			 struct dentry *new_dentry, bool preserve)
{
	int error;
	struct inode *inode = old_dentry->d_inode;
	struct buffer_head *old_bh = NULL;
	struct inode *new_orphan_inode = NULL;

	if (!ocfs2_refcount_tree(OCFS2_SB(inode->i_sb)))
		return -EOPNOTSUPP;

	error = ocfs2_create_inode_in_orphan(dir, inode->i_mode,
					     &new_orphan_inode);
	if (error) {
		mlog_errno(error);
		goto out;
	}

	error = ocfs2_inode_lock(inode, &old_bh, 1);
	if (error) {
		mlog_errno(error);
		goto out;
	}

	down_write(&OCFS2_I(inode)->ip_xattr_sem);
	down_write(&OCFS2_I(inode)->ip_alloc_sem);
	error = __ocfs2_reflink(old_dentry, old_bh,
				new_orphan_inode, preserve);
	up_write(&OCFS2_I(inode)->ip_alloc_sem);
	up_write(&OCFS2_I(inode)->ip_xattr_sem);

	ocfs2_inode_unlock(inode, 1);
	brelse(old_bh);

	if (error) {
		mlog_errno(error);
		goto out;
	}

	/* If the security isn't preserved, we need to re-initialize them. */
	if (!preserve) {
		error = ocfs2_init_security_and_acl(dir, new_orphan_inode);
		if (error)
			mlog_errno(error);
	}
out:
	if (!error) {
		error = ocfs2_mv_orphaned_inode_to_new(dir, new_orphan_inode,
						       new_dentry);
		if (error)
			mlog_errno(error);
	}

	if (new_orphan_inode) {
		/*
		 * We need to open_unlock the inode no matter whether we
		 * succeed or not, so that other nodes can delete it later.
		 */
		ocfs2_open_unlock(new_orphan_inode);
		if (error)
			iput(new_orphan_inode);
	}

	return error;
}