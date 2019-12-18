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
struct vfsmount {int dummy; } ;
struct kstat {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_fillattr (int /*<<< orphan*/ ,struct kstat*) ; 
 int smb_revalidate_inode (struct dentry*) ; 

int smb_getattr(struct vfsmount *mnt, struct dentry *dentry, struct kstat *stat)
{
	int err = smb_revalidate_inode(dentry);
	if (!err)
		generic_fillattr(dentry->d_inode, stat);
	return err;
}