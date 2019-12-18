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
struct kstat {int /*<<< orphan*/  blocks; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecryptfs_dentry_to_lower (struct dentry*) ; 
 int /*<<< orphan*/  ecryptfs_dentry_to_lower_mnt (struct dentry*) ; 
 int /*<<< orphan*/  generic_fillattr (int /*<<< orphan*/ ,struct kstat*) ; 
 int vfs_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kstat*) ; 

int ecryptfs_getattr(struct vfsmount *mnt, struct dentry *dentry,
		     struct kstat *stat)
{
	struct kstat lower_stat;
	int rc;

	rc = vfs_getattr(ecryptfs_dentry_to_lower_mnt(dentry),
			 ecryptfs_dentry_to_lower(dentry), &lower_stat);
	if (!rc) {
		generic_fillattr(dentry->d_inode, stat);
		stat->blocks = lower_stat.blocks;
	}
	return rc;
}