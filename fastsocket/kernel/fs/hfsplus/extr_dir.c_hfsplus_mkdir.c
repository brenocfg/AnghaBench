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
struct inode {int /*<<< orphan*/  i_ino; scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int ENOSPC ; 
 int S_IFDIR ; 
 int hfsplus_create_cat (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  hfsplus_delete_inode (struct inode*) ; 
 int /*<<< orphan*/  hfsplus_instantiate (struct dentry*,struct inode*,int /*<<< orphan*/ ) ; 
 struct inode* hfsplus_new_inode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 

__attribute__((used)) static int hfsplus_mkdir(struct inode *dir, struct dentry *dentry, int mode)
{
	struct inode *inode;
	int res;

	inode = hfsplus_new_inode(dir->i_sb, S_IFDIR | mode);
	if (!inode)
		return -ENOSPC;

	res = hfsplus_create_cat(inode->i_ino, dir, &dentry->d_name, inode);
	if (res) {
		inode->i_nlink = 0;
		hfsplus_delete_inode(inode);
		iput(inode);
		return res;
	}
	hfsplus_instantiate(dentry, inode, inode->i_ino);
	mark_inode_dirty(inode);
	return 0;
}