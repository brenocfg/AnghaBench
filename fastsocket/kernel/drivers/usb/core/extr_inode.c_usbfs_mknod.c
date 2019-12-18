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
struct dentry {scalar_t__ d_inode; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int EEXIST ; 
 int EPERM ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 struct inode* usbfs_get_inode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbfs_mknod (struct inode *dir, struct dentry *dentry, int mode,
			dev_t dev)
{
	struct inode *inode = usbfs_get_inode(dir->i_sb, mode, dev);
	int error = -EPERM;

	if (dentry->d_inode)
		return -EEXIST;

	if (inode) {
		d_instantiate(dentry, inode);
		dget(dentry);
		error = 0;
	}
	return error;
}