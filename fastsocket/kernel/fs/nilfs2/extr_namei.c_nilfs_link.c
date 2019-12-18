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
struct nilfs_transaction_info {int dummy; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_count; int /*<<< orphan*/  i_ctime; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EMLINK ; 
 scalar_t__ NILFS_LINK_MAX ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_inc_link_count (struct inode*) ; 
 int nilfs_add_nondir (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  nilfs_transaction_abort (int /*<<< orphan*/ ) ; 
 int nilfs_transaction_begin (int /*<<< orphan*/ ,struct nilfs_transaction_info*,int) ; 
 int nilfs_transaction_commit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_link(struct dentry *old_dentry, struct inode *dir,
		      struct dentry *dentry)
{
	struct inode *inode = old_dentry->d_inode;
	struct nilfs_transaction_info ti;
	int err;

	if (inode->i_nlink >= NILFS_LINK_MAX)
		return -EMLINK;

	err = nilfs_transaction_begin(dir->i_sb, &ti, 1);
	if (err)
		return err;

	inode->i_ctime = CURRENT_TIME;
	inode_inc_link_count(inode);
	atomic_inc(&inode->i_count);

	err = nilfs_add_nondir(dentry, inode);
	if (!err)
		err = nilfs_transaction_commit(dir->i_sb);
	else
		nilfs_transaction_abort(dir->i_sb);

	return err;
}