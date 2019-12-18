#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {unsigned int s_blocksize; } ;
struct inode {unsigned int i_size; int /*<<< orphan*/ * i_op; TYPE_1__* i_mapping; struct super_block* i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {scalar_t__ i_data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 TYPE_2__* EXT2_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  NOBH ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int ext2_add_nondir (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  ext2_aops ; 
 int /*<<< orphan*/  ext2_fast_symlink_inode_operations ; 
 struct inode* ext2_new_inode (struct inode*,int) ; 
 int /*<<< orphan*/  ext2_nobh_aops ; 
 int /*<<< orphan*/  ext2_symlink_inode_operations ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 int page_symlink (struct inode*,char const*,unsigned int) ; 
 int strlen (char const*) ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static int ext2_symlink (struct inode * dir, struct dentry * dentry,
	const char * symname)
{
	struct super_block * sb = dir->i_sb;
	int err = -ENAMETOOLONG;
	unsigned l = strlen(symname)+1;
	struct inode * inode;

	if (l > sb->s_blocksize)
		goto out;

	inode = ext2_new_inode (dir, S_IFLNK | S_IRWXUGO);
	err = PTR_ERR(inode);
	if (IS_ERR(inode))
		goto out;

	if (l > sizeof (EXT2_I(inode)->i_data)) {
		/* slow symlink */
		inode->i_op = &ext2_symlink_inode_operations;
		if (test_opt(inode->i_sb, NOBH))
			inode->i_mapping->a_ops = &ext2_nobh_aops;
		else
			inode->i_mapping->a_ops = &ext2_aops;
		err = page_symlink(inode, symname, l);
		if (err)
			goto out_fail;
	} else {
		/* fast symlink */
		inode->i_op = &ext2_fast_symlink_inode_operations;
		memcpy((char*)(EXT2_I(inode)->i_data),symname,l);
		inode->i_size = l-1;
	}
	mark_inode_dirty(inode);

	err = ext2_add_nondir(dentry, inode);
out:
	return err;

out_fail:
	inode_dec_link_count(inode);
	unlock_new_inode(inode);
	iput (inode);
	goto out;
}