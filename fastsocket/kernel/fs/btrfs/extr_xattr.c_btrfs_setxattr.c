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
struct dentry {int /*<<< orphan*/  d_inode; } ;
struct btrfs_root {int dummy; } ;
struct TYPE_2__ {struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
 int EROFS ; 
 int /*<<< orphan*/  XATTR_SYSTEM_PREFIX ; 
 int /*<<< orphan*/  XATTR_SYSTEM_PREFIX_LEN ; 
 int __btrfs_setxattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,void const*,size_t,int) ; 
 int /*<<< orphan*/  btrfs_is_valid_xattr (char const*) ; 
 scalar_t__ btrfs_root_readonly (struct btrfs_root*) ; 
 int generic_setxattr (struct dentry*,char const*,void const*,size_t,int) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int btrfs_setxattr(struct dentry *dentry, const char *name, const void *value,
		   size_t size, int flags)
{
	struct btrfs_root *root = BTRFS_I(dentry->d_inode)->root;

	/*
	 * The permission on security.* and system.* is not checked
	 * in permission().
	 */
	if (btrfs_root_readonly(root))
		return -EROFS;

	/*
	 * If this is a request for a synthetic attribute in the system.*
	 * namespace use the generic infrastructure to resolve a handler
	 * for it via sb->s_xattr.
	 */
	if (!strncmp(name, XATTR_SYSTEM_PREFIX, XATTR_SYSTEM_PREFIX_LEN))
		return generic_setxattr(dentry, name, value, size, flags);

	if (!btrfs_is_valid_xattr(name))
		return -EOPNOTSUPP;

	if (size == 0)
		value = "";  /* empty EA, do not remove */

	return __btrfs_setxattr(NULL, dentry->d_inode, name, value, size,
				flags);
}