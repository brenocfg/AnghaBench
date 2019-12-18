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
struct nameidata {int dummy; } ;
struct inode {TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  UFSD (char*,...) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int ufs_add_nondir (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  ufs_aops ; 
 int /*<<< orphan*/  ufs_file_inode_operations ; 
 int /*<<< orphan*/  ufs_file_operations ; 
 struct inode* ufs_new_inode (struct inode*,int) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int ufs_create (struct inode * dir, struct dentry * dentry, int mode,
		struct nameidata *nd)
{
	struct inode *inode;
	int err;

	UFSD("BEGIN\n");
	inode = ufs_new_inode(dir, mode);
	err = PTR_ERR(inode);

	if (!IS_ERR(inode)) {
		inode->i_op = &ufs_file_inode_operations;
		inode->i_fop = &ufs_file_operations;
		inode->i_mapping->a_ops = &ufs_aops;
		mark_inode_dirty(inode);
		lock_kernel();
		err = ufs_add_nondir(dentry, inode);
		unlock_kernel();
	}
	UFSD("END: err=%d\n", err);
	return err;
}