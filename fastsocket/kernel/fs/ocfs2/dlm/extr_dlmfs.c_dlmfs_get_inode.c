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
struct super_block {int dummy; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; TYPE_1__* i_mapping; int /*<<< orphan*/  i_uid; struct super_block* i_sb; } ;
struct dlmfs_inode_private {int /*<<< orphan*/  ip_parent; int /*<<< orphan*/  ip_lockres; int /*<<< orphan*/  ip_dlm; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * backing_dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 struct dlmfs_inode_private* DLMFS_I (struct inode*) ; 
 int /*<<< orphan*/  DLM_LVB_LEN ; 
#define  S_IFDIR 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 scalar_t__ S_ISDIR (int) ; 
 int S_ISGID ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  dlmfs_backing_dev_info ; 
 int /*<<< orphan*/  dlmfs_dir_inode_operations ; 
 int /*<<< orphan*/  dlmfs_file_inode_operations ; 
 int /*<<< orphan*/  dlmfs_file_operations ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 int /*<<< orphan*/  user_dlm_lock_res_init (int /*<<< orphan*/ *,struct dentry*) ; 

__attribute__((used)) static struct inode *dlmfs_get_inode(struct inode *parent,
				     struct dentry *dentry,
				     int mode)
{
	struct super_block *sb = parent->i_sb;
	struct inode * inode = new_inode(sb);
	struct dlmfs_inode_private *ip;

	if (!inode)
		return NULL;

	inode->i_mode = mode;
	inode->i_uid = current_fsuid();
	inode->i_gid = current_fsgid();
	inode->i_mapping->backing_dev_info = &dlmfs_backing_dev_info;
	inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;

	ip = DLMFS_I(inode);
	ip->ip_dlm = DLMFS_I(parent)->ip_dlm;

	switch (mode & S_IFMT) {
	default:
		/* for now we don't support anything other than
		 * directories and regular files. */
		BUG();
		break;
	case S_IFREG:
		inode->i_op = &dlmfs_file_inode_operations;
		inode->i_fop = &dlmfs_file_operations;

		i_size_write(inode,  DLM_LVB_LEN);

		user_dlm_lock_res_init(&ip->ip_lockres, dentry);

		/* released at clear_inode time, this insures that we
		 * get to drop the dlm reference on each lock *before*
		 * we call the unregister code for releasing parent
		 * directories. */
		ip->ip_parent = igrab(parent);
		BUG_ON(!ip->ip_parent);
		break;
	case S_IFDIR:
		inode->i_op = &dlmfs_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;

		/* directory inodes start off with i_nlink ==
		 * 2 (for "." entry) */
		inc_nlink(inode);
		break;
	}

	if (parent->i_mode & S_ISGID) {
		inode->i_gid = parent->i_gid;
		if (S_ISDIR(mode))
			inode->i_mode |= S_ISGID;
	}

	return inode;
}