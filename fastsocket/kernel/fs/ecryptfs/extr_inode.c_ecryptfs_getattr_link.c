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
struct kstat {size_t size; } ;
struct ecryptfs_mount_crypt_stat {int flags; } ;
struct dentry {int /*<<< orphan*/  d_inode; int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {struct ecryptfs_mount_crypt_stat mount_crypt_stat; } ;

/* Variables and functions */
 int ECRYPTFS_GLOBAL_ENCRYPT_FILENAMES ; 
 int ecryptfs_readlink_lower (struct dentry*,char**,size_t*) ; 
 TYPE_1__* ecryptfs_superblock_to_private (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (int /*<<< orphan*/ ,struct kstat*) ; 
 int /*<<< orphan*/  kfree (char*) ; 

int ecryptfs_getattr_link(struct vfsmount *mnt, struct dentry *dentry,
			  struct kstat *stat)
{
	struct ecryptfs_mount_crypt_stat *mount_crypt_stat;
	int rc = 0;

	mount_crypt_stat = &ecryptfs_superblock_to_private(
						dentry->d_sb)->mount_crypt_stat;
	generic_fillattr(dentry->d_inode, stat);
	if (mount_crypt_stat->flags & ECRYPTFS_GLOBAL_ENCRYPT_FILENAMES) {
		char *target;
		size_t targetsiz;

		rc = ecryptfs_readlink_lower(dentry, &target, &targetsiz);
		if (!rc) {
			kfree(target);
			stat->size = targetsiz;
		}
	}
	return rc;
}