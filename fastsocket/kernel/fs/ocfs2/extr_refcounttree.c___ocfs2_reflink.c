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
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_mutex; } ;
struct dentry {struct inode* d_inode; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int ip_dyn_features; } ;

/* Variables and functions */
 int OCFS2_HAS_XATTR_FL ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int filemap_fdatawait (int /*<<< orphan*/ ) ; 
 int filemap_fdatawrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ocfs2_attach_refcount_tree (struct inode*,struct buffer_head*) ; 
 int ocfs2_complete_reflink (struct inode*,struct buffer_head*,struct inode*,struct buffer_head*,int) ; 
 int ocfs2_create_reflink_node (struct inode*,struct buffer_head*,struct inode*,struct buffer_head*,int) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_reflink_xattrs (struct inode*,struct buffer_head*,struct inode*,struct buffer_head*,int) ; 

__attribute__((used)) static int __ocfs2_reflink(struct dentry *old_dentry,
			   struct buffer_head *old_bh,
			   struct inode *new_inode,
			   bool preserve)
{
	int ret;
	struct inode *inode = old_dentry->d_inode;
	struct buffer_head *new_bh = NULL;

	ret = filemap_fdatawrite(inode->i_mapping);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_attach_refcount_tree(inode, old_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	mutex_lock(&new_inode->i_mutex);
	ret = ocfs2_inode_lock(new_inode, &new_bh, 1);
	if (ret) {
		mlog_errno(ret);
		goto out_unlock;
	}

	ret = ocfs2_create_reflink_node(inode, old_bh,
					new_inode, new_bh, preserve);
	if (ret) {
		mlog_errno(ret);
		goto inode_unlock;
	}

	if (OCFS2_I(inode)->ip_dyn_features & OCFS2_HAS_XATTR_FL) {
		ret = ocfs2_reflink_xattrs(inode, old_bh,
					   new_inode, new_bh,
					   preserve);
		if (ret) {
			mlog_errno(ret);
			goto inode_unlock;
		}
	}

	ret = ocfs2_complete_reflink(inode, old_bh,
				     new_inode, new_bh, preserve);
	if (ret)
		mlog_errno(ret);

inode_unlock:
	ocfs2_inode_unlock(new_inode, 1);
	brelse(new_bh);
out_unlock:
	mutex_unlock(&new_inode->i_mutex);
out:
	if (!ret) {
		ret = filemap_fdatawait(inode->i_mapping);
		if (ret)
			mlog_errno(ret);
	}
	return ret;
}