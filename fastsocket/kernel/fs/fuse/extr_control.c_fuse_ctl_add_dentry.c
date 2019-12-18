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
struct inode_operations {int dummy; } ;
struct inode {int i_mode; int i_nlink; struct fuse_conn* i_private; struct file_operations const* i_fop; struct inode_operations const* i_op; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct fuse_conn {scalar_t__ ctl_ndents; int /*<<< orphan*/  group_id; int /*<<< orphan*/  user_id; struct dentry** ctl_dentry; } ;
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 scalar_t__ FUSE_CTL_NUM_DENTRIES ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (struct dentry*,char const*) ; 
 int /*<<< orphan*/  fuse_control_sb ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *fuse_ctl_add_dentry(struct dentry *parent,
					  struct fuse_conn *fc,
					  const char *name,
					  int mode, int nlink,
					  const struct inode_operations *iop,
					  const struct file_operations *fop)
{
	struct dentry *dentry;
	struct inode *inode;

	BUG_ON(fc->ctl_ndents >= FUSE_CTL_NUM_DENTRIES);
	dentry = d_alloc_name(parent, name);
	if (!dentry)
		return NULL;

	fc->ctl_dentry[fc->ctl_ndents++] = dentry;
	inode = new_inode(fuse_control_sb);
	if (!inode)
		return NULL;

	inode->i_mode = mode;
	inode->i_uid = fc->user_id;
	inode->i_gid = fc->group_id;
	inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
	/* setting ->i_op to NULL is not allowed */
	if (iop)
		inode->i_op = iop;
	inode->i_fop = fop;
	inode->i_nlink = nlink;
	inode->i_private = fc;
	d_add(dentry, inode);
	return dentry;
}