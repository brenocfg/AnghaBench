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
struct inode {int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_ino; } ;
struct dentry {int /*<<< orphan*/  d_name; struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int ENOTEMPTY ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int hfsplus_delete_cat (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfsplus_delete_inode (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 

__attribute__((used)) static int hfsplus_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode;
	int res;

	inode = dentry->d_inode;
	if (inode->i_size != 2)
		return -ENOTEMPTY;
	res = hfsplus_delete_cat(inode->i_ino, dir, &dentry->d_name);
	if (res)
		return res;
	clear_nlink(inode);
	inode->i_ctime = CURRENT_TIME_SEC;
	hfsplus_delete_inode(inode);
	mark_inode_dirty(inode);
	return 0;
}