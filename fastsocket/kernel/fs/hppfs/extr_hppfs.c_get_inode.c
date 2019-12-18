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
struct inode {int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  proc_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_1__* HPPFS_I (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  hppfs_dir_fops ; 
 int /*<<< orphan*/  hppfs_dir_iops ; 
 int /*<<< orphan*/  hppfs_file_fops ; 
 int /*<<< orphan*/  hppfs_file_iops ; 
 int /*<<< orphan*/  hppfs_link_iops ; 
 struct inode* new_inode (struct super_block*) ; 

__attribute__((used)) static struct inode *get_inode(struct super_block *sb, struct dentry *dentry)
{
	struct inode *proc_ino = dentry->d_inode;
	struct inode *inode = new_inode(sb);

	if (!inode)
		return ERR_PTR(-ENOMEM);

	if (S_ISDIR(dentry->d_inode->i_mode)) {
		inode->i_op = &hppfs_dir_iops;
		inode->i_fop = &hppfs_dir_fops;
	} else if (S_ISLNK(dentry->d_inode->i_mode)) {
		inode->i_op = &hppfs_link_iops;
		inode->i_fop = &hppfs_file_fops;
	} else {
		inode->i_op = &hppfs_file_iops;
		inode->i_fop = &hppfs_file_fops;
	}

	HPPFS_I(inode)->proc_dentry = dget(dentry);

	inode->i_uid = proc_ino->i_uid;
	inode->i_gid = proc_ino->i_gid;
	inode->i_atime = proc_ino->i_atime;
	inode->i_mtime = proc_ino->i_mtime;
	inode->i_ctime = proc_ino->i_ctime;
	inode->i_ino = proc_ino->i_ino;
	inode->i_mode = proc_ino->i_mode;
	inode->i_nlink = proc_ino->i_nlink;
	inode->i_size = proc_ino->i_size;
	inode->i_blocks = proc_ino->i_blocks;

	return inode;
}