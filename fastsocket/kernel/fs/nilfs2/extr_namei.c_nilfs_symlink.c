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
struct super_block {unsigned int s_blocksize; } ;
struct nilfs_transaction_info {int dummy; } ;
struct inode {struct super_block* i_sb; TYPE_1__* i_mapping; int /*<<< orphan*/ * i_op; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int nilfs_add_nondir (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  nilfs_aops ; 
 struct inode* nilfs_new_inode (struct inode*,int) ; 
 int /*<<< orphan*/  nilfs_symlink_inode_operations ; 
 int /*<<< orphan*/  nilfs_transaction_abort (struct super_block*) ; 
 int nilfs_transaction_begin (struct super_block*,struct nilfs_transaction_info*,int) ; 
 int nilfs_transaction_commit (struct super_block*) ; 
 int page_symlink (struct inode*,char const*,unsigned int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int nilfs_symlink(struct inode *dir, struct dentry *dentry,
			 const char *symname)
{
	struct nilfs_transaction_info ti;
	struct super_block *sb = dir->i_sb;
	unsigned l = strlen(symname)+1;
	struct inode *inode;
	int err;

	if (l > sb->s_blocksize)
		return -ENAMETOOLONG;

	err = nilfs_transaction_begin(dir->i_sb, &ti, 1);
	if (err)
		return err;

	inode = nilfs_new_inode(dir, S_IFLNK | S_IRWXUGO);
	err = PTR_ERR(inode);
	if (IS_ERR(inode))
		goto out;

	/* slow symlink */
	inode->i_op = &nilfs_symlink_inode_operations;
	inode->i_mapping->a_ops = &nilfs_aops;
	err = page_symlink(inode, symname, l);
	if (err)
		goto out_fail;

	/* mark_inode_dirty(inode); */
	/* nilfs_new_inode() and page_symlink() do this */

	err = nilfs_add_nondir(dentry, inode);
out:
	if (!err)
		err = nilfs_transaction_commit(dir->i_sb);
	else
		nilfs_transaction_abort(dir->i_sb);

	return err;

out_fail:
	inode_dec_link_count(inode);
	iput(inode);
	goto out;
}