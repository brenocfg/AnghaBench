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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int reiserfs_commit_for_inode (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reiserfs_dir_fsync(struct file *filp, struct dentry *dentry,
			      int datasync)
{
	struct inode *inode = dentry->d_inode;
	int err;
	reiserfs_write_lock(inode->i_sb);
	err = reiserfs_commit_for_inode(inode);
	reiserfs_write_unlock(inode->i_sb);
	if (err < 0)
		return err;
	return 0;
}