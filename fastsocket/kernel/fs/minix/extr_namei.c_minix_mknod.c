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
struct inode {int i_mode; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int EINVAL ; 
 int add_nondir (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 struct inode* minix_new_inode (struct inode*,int*) ; 
 int /*<<< orphan*/  minix_set_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_valid_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int minix_mknod(struct inode * dir, struct dentry *dentry, int mode, dev_t rdev)
{
	int error;
	struct inode *inode;

	if (!old_valid_dev(rdev))
		return -EINVAL;

	inode = minix_new_inode(dir, &error);

	if (inode) {
		inode->i_mode = mode;
		minix_set_inode(inode, rdev);
		mark_inode_dirty(inode);
		error = add_nondir(dentry, inode);
	}
	return error;
}