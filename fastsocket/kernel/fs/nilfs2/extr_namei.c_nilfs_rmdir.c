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
struct inode {int /*<<< orphan*/  i_sb; scalar_t__ i_size; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int ENOTEMPTY ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 scalar_t__ nilfs_empty_dir (struct inode*) ; 
 int /*<<< orphan*/  nilfs_transaction_abort (int /*<<< orphan*/ ) ; 
 int nilfs_transaction_begin (int /*<<< orphan*/ ,struct nilfs_transaction_info*,int /*<<< orphan*/ ) ; 
 int nilfs_transaction_commit (int /*<<< orphan*/ ) ; 
 int nilfs_unlink (struct inode*,struct dentry*) ; 

__attribute__((used)) static int nilfs_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = dentry->d_inode;
	struct nilfs_transaction_info ti;
	int err;

	err = nilfs_transaction_begin(dir->i_sb, &ti, 0);
	if (err)
		return err;

	err = -ENOTEMPTY;
	if (nilfs_empty_dir(inode)) {
		err = nilfs_unlink(dir, dentry);
		if (!err) {
			inode->i_size = 0;
			inode_dec_link_count(inode);
			inode_dec_link_count(dir);
		}
	}
	if (!err)
		err = nilfs_transaction_commit(dir->i_sb);
	else
		nilfs_transaction_abort(dir->i_sb);

	return err;
}