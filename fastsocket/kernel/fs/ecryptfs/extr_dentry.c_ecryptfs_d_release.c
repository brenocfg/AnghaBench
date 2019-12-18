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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dput (scalar_t__) ; 
 int /*<<< orphan*/  ecryptfs_dentry_info_cache ; 
 scalar_t__ ecryptfs_dentry_to_lower (struct dentry*) ; 
 int /*<<< orphan*/  ecryptfs_dentry_to_lower_mnt (struct dentry*) ; 
 scalar_t__ ecryptfs_dentry_to_private (struct dentry*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mntput (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecryptfs_d_release(struct dentry *dentry)
{
	if (ecryptfs_dentry_to_private(dentry)) {
		if (ecryptfs_dentry_to_lower(dentry)) {
			dput(ecryptfs_dentry_to_lower(dentry));
			mntput(ecryptfs_dentry_to_lower_mnt(dentry));
		}
		kmem_cache_free(ecryptfs_dentry_info_cache,
				ecryptfs_dentry_to_private(dentry));
	}
	return;
}