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
struct inode {int /*<<< orphan*/  i_ino; scalar_t__ i_nlink; struct super_block* i_sb; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int ENOSPC ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int hfsplus_create_cat (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  hfsplus_delete_inode (struct inode*) ; 
 int /*<<< orphan*/  hfsplus_instantiate (struct dentry*,struct inode*,int /*<<< orphan*/ ) ; 
 struct inode* hfsplus_new_inode (struct super_block*,int) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int page_symlink (struct inode*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int hfsplus_symlink(struct inode *dir, struct dentry *dentry,
			   const char *symname)
{
	struct super_block *sb;
	struct inode *inode;
	int res;

	sb = dir->i_sb;
	inode = hfsplus_new_inode(sb, S_IFLNK | S_IRWXUGO);
	if (!inode)
		return -ENOSPC;

	res = page_symlink(inode, symname, strlen(symname) + 1);
	if (res) {
		inode->i_nlink = 0;
		hfsplus_delete_inode(inode);
		iput(inode);
		return res;
	}

	mark_inode_dirty(inode);
	res = hfsplus_create_cat(inode->i_ino, dir, &dentry->d_name, inode);

	if (!res) {
		hfsplus_instantiate(dentry, inode, inode->i_ino);
		mark_inode_dirty(inode);
	}

	return res;
}