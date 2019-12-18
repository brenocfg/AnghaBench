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
struct inode {scalar_t__ i_ino; scalar_t__ i_size; int /*<<< orphan*/  i_sb; } ;
struct iattr {int ia_valid; scalar_t__ ia_size; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {scalar_t__ sb_root; } ;

/* Variables and functions */
 int ATTR_SIZE ; 
 int EINVAL ; 
 TYPE_1__* hpfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_write_inode (struct inode*) ; 
 int inode_change_ok (struct inode*,struct iattr*) ; 
 int inode_setattr (struct inode*,struct iattr*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

int hpfs_setattr(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = dentry->d_inode;
	int error = -EINVAL;

	lock_kernel();
	if (inode->i_ino == hpfs_sb(inode->i_sb)->sb_root)
		goto out_unlock;
	if ((attr->ia_valid & ATTR_SIZE) && attr->ia_size > inode->i_size)
		goto out_unlock;

	error = inode_change_ok(inode, attr);
	if (error)
		goto out_unlock;

	error = inode_setattr(inode, attr);
	if (error)
		goto out_unlock;

	hpfs_write_inode(inode);

 out_unlock:
	unlock_kernel();
	return error;
}