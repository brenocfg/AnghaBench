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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int omfs_add_link (struct dentry*,struct inode*) ; 
 int omfs_make_empty (struct inode*,int /*<<< orphan*/ ) ; 
 struct inode* omfs_new_inode (struct inode*,int) ; 

__attribute__((used)) static int omfs_add_node(struct inode *dir, struct dentry *dentry, int mode)
{
	int err;
	struct inode *inode = omfs_new_inode(dir, mode);

	if (IS_ERR(inode))
		return PTR_ERR(inode);

	err = omfs_make_empty(inode, dir->i_sb);
	if (err)
		goto out_free_inode;

	err = omfs_add_link(dentry, inode);
	if (err)
		goto out_free_inode;

	d_instantiate(dentry, inode);
	return 0;

out_free_inode:
	iput(inode);
	return err;
}