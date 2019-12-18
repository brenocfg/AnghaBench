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
struct inode {unsigned int i_size; int /*<<< orphan*/ * i_op; TYPE_1__* i_mapping; struct super_block* i_sb; } ;
struct exofs_i_info {int /*<<< orphan*/  i_data; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int exofs_add_nondir (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  exofs_aops ; 
 int /*<<< orphan*/  exofs_fast_symlink_inode_operations ; 
 struct exofs_i_info* exofs_i (struct inode*) ; 
 struct inode* exofs_new_inode (struct inode*,int) ; 
 int /*<<< orphan*/  exofs_symlink_inode_operations ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int page_symlink (struct inode*,char const*,unsigned int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int exofs_symlink(struct inode *dir, struct dentry *dentry,
			  const char *symname)
{
	struct super_block *sb = dir->i_sb;
	int err = -ENAMETOOLONG;
	unsigned l = strlen(symname)+1;
	struct inode *inode;
	struct exofs_i_info *oi;

	if (l > sb->s_blocksize)
		goto out;

	inode = exofs_new_inode(dir, S_IFLNK | S_IRWXUGO);
	err = PTR_ERR(inode);
	if (IS_ERR(inode))
		goto out;

	oi = exofs_i(inode);
	if (l > sizeof(oi->i_data)) {
		/* slow symlink */
		inode->i_op = &exofs_symlink_inode_operations;
		inode->i_mapping->a_ops = &exofs_aops;
		memset(oi->i_data, 0, sizeof(oi->i_data));

		err = page_symlink(inode, symname, l);
		if (err)
			goto out_fail;
	} else {
		/* fast symlink */
		inode->i_op = &exofs_fast_symlink_inode_operations;
		memcpy(oi->i_data, symname, l);
		inode->i_size = l-1;
	}
	mark_inode_dirty(inode);

	err = exofs_add_nondir(dentry, inode);
out:
	return err;

out_fail:
	inode_dec_link_count(inode);
	iput(inode);
	goto out;
}