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
struct super_block {int dummy; } ;
struct nilfs_transaction_info {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct iattr {int ia_valid; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int ATTR_MODE ; 
 int inode_change_ok (struct inode*,struct iattr*) ; 
 int inode_setattr (struct inode*,struct iattr*) ; 
 scalar_t__ likely (int) ; 
 int nilfs_acl_chmod (struct inode*) ; 
 int /*<<< orphan*/  nilfs_transaction_abort (struct super_block*) ; 
 int nilfs_transaction_begin (struct super_block*,struct nilfs_transaction_info*,int /*<<< orphan*/ ) ; 
 int nilfs_transaction_commit (struct super_block*) ; 
 scalar_t__ unlikely (int) ; 

int nilfs_setattr(struct dentry *dentry, struct iattr *iattr)
{
	struct nilfs_transaction_info ti;
	struct inode *inode = dentry->d_inode;
	struct super_block *sb = inode->i_sb;
	int err;

	err = inode_change_ok(inode, iattr);
	if (err)
		return err;

	err = nilfs_transaction_begin(sb, &ti, 0);
	if (unlikely(err))
		return err;
	err = inode_setattr(inode, iattr);
	if (!err && (iattr->ia_valid & ATTR_MODE))
		err = nilfs_acl_chmod(inode);
	if (likely(!err))
		err = nilfs_transaction_commit(sb);
	else
		nilfs_transaction_abort(sb);

	return err;
}