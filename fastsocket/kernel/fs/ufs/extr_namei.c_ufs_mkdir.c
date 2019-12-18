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
struct inode {scalar_t__ i_nlink; TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int EMLINK ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFDIR ; 
 scalar_t__ UFS_LINK_MAX ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  inode_inc_link_count (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int ufs_add_link (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  ufs_aops ; 
 int /*<<< orphan*/  ufs_dir_inode_operations ; 
 int /*<<< orphan*/  ufs_dir_operations ; 
 int ufs_make_empty (struct inode*,struct inode*) ; 
 struct inode* ufs_new_inode (struct inode*,int) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int ufs_mkdir(struct inode * dir, struct dentry * dentry, int mode)
{
	struct inode * inode;
	int err = -EMLINK;

	if (dir->i_nlink >= UFS_LINK_MAX)
		goto out;

	lock_kernel();
	inode_inc_link_count(dir);

	inode = ufs_new_inode(dir, S_IFDIR|mode);
	err = PTR_ERR(inode);
	if (IS_ERR(inode))
		goto out_dir;

	inode->i_op = &ufs_dir_inode_operations;
	inode->i_fop = &ufs_dir_operations;
	inode->i_mapping->a_ops = &ufs_aops;

	inode_inc_link_count(inode);

	err = ufs_make_empty(inode, dir);
	if (err)
		goto out_fail;

	err = ufs_add_link(dentry, inode);
	if (err)
		goto out_fail;
	unlock_kernel();

	d_instantiate(dentry, inode);
out:
	return err;

out_fail:
	inode_dec_link_count(inode);
	inode_dec_link_count(inode);
	iput (inode);
out_dir:
	inode_dec_link_count(dir);
	unlock_kernel();
	goto out;
}