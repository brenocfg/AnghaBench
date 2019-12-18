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
struct vfsmount {int dummy; } ;
struct kstat {int dummy; } ;
struct inode {TYPE_1__* i_op; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {int (* getattr ) (struct vfsmount*,struct dentry*,struct kstat*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 int security_inode_getattr (struct vfsmount*,struct dentry*) ; 
 int stub1 (struct vfsmount*,struct dentry*,struct kstat*) ; 

int vfs_getattr(struct vfsmount *mnt, struct dentry *dentry, struct kstat *stat)
{
	struct inode *inode = dentry->d_inode;
	int retval;

	retval = security_inode_getattr(mnt, dentry);
	if (retval)
		return retval;

	if (inode->i_op->getattr)
		return inode->i_op->getattr(mnt, dentry, stat);

	generic_fillattr(inode, stat);
	return 0;
}