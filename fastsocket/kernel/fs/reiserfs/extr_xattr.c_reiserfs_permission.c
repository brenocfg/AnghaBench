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
struct inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_PRIVATE (struct inode*) ; 
 scalar_t__ STAT_DATA_V1 ; 
 int generic_permission (struct inode*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ get_inode_sd_version (struct inode*) ; 
 int /*<<< orphan*/ * reiserfs_check_acl ; 

int reiserfs_permission(struct inode *inode, int mask)
{
	/*
	 * We don't do permission checks on the internal objects.
	 * Permissions are determined by the "owning" object.
	 */
	if (IS_PRIVATE(inode))
		return 0;

#ifdef CONFIG_REISERFS_FS_XATTR
	/*
	 * Stat data v1 doesn't support ACLs.
	 */
	if (get_inode_sd_version(inode) != STAT_DATA_V1)
		return generic_permission(inode, mask, reiserfs_check_acl);
#endif
	return generic_permission(inode, mask, NULL);
}