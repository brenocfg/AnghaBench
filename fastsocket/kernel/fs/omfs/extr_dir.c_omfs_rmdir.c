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
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int ENOTEMPTY ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 scalar_t__ omfs_dir_is_empty (struct inode*) ; 
 int omfs_unlink (struct inode*,struct dentry*) ; 

__attribute__((used)) static int omfs_rmdir(struct inode *dir, struct dentry *dentry)
{
	int err = -ENOTEMPTY;
	struct inode *inode = dentry->d_inode;

	if (omfs_dir_is_empty(inode)) {
		err = omfs_unlink(dir, dentry);
		if (!err)
			inode_dec_link_count(inode);
	}
	return err;
}