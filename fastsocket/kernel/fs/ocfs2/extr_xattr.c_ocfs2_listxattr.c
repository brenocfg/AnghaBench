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
struct ocfs2_inode_info {int ip_dyn_features; int /*<<< orphan*/  ip_xattr_sem; } ;
struct ocfs2_dinode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_inode; int /*<<< orphan*/  d_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int OCFS2_HAS_XATTR_FL ; 
 struct ocfs2_inode_info* OCFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_inode_lock (int /*<<< orphan*/ ,struct buffer_head**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_supports_xattr (int /*<<< orphan*/ ) ; 
 int ocfs2_xattr_block_list (int /*<<< orphan*/ ,struct ocfs2_dinode*,char*,size_t) ; 
 int ocfs2_xattr_ibody_list (int /*<<< orphan*/ ,struct ocfs2_dinode*,char*,size_t) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

ssize_t ocfs2_listxattr(struct dentry *dentry,
			char *buffer,
			size_t size)
{
	int ret = 0, i_ret = 0, b_ret = 0;
	struct buffer_head *di_bh = NULL;
	struct ocfs2_dinode *di = NULL;
	struct ocfs2_inode_info *oi = OCFS2_I(dentry->d_inode);

	if (!ocfs2_supports_xattr(OCFS2_SB(dentry->d_sb)))
		return -EOPNOTSUPP;

	if (!(oi->ip_dyn_features & OCFS2_HAS_XATTR_FL))
		return ret;

	ret = ocfs2_inode_lock(dentry->d_inode, &di_bh, 0);
	if (ret < 0) {
		mlog_errno(ret);
		return ret;
	}

	di = (struct ocfs2_dinode *)di_bh->b_data;

	down_read(&oi->ip_xattr_sem);
	i_ret = ocfs2_xattr_ibody_list(dentry->d_inode, di, buffer, size);
	if (i_ret < 0)
		b_ret = 0;
	else {
		if (buffer) {
			buffer += i_ret;
			size -= i_ret;
		}
		b_ret = ocfs2_xattr_block_list(dentry->d_inode, di,
					       buffer, size);
		if (b_ret < 0)
			i_ret = 0;
	}
	up_read(&oi->ip_xattr_sem);
	ocfs2_inode_unlock(dentry->d_inode, 0);

	brelse(di_bh);

	return i_ret + b_ret;
}