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
struct dentry {int /*<<< orphan*/  d_inode; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  XATTR_SYSTEM_PREFIX ; 
 int /*<<< orphan*/  XATTR_SYSTEM_PREFIX_LEN ; 
 int /*<<< orphan*/  __btrfs_getxattr (int /*<<< orphan*/ ,char const*,void*,size_t) ; 
 int /*<<< orphan*/  btrfs_is_valid_xattr (char const*) ; 
 int /*<<< orphan*/  generic_getxattr (struct dentry*,char const*,void*,size_t) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ssize_t btrfs_getxattr(struct dentry *dentry, const char *name,
		       void *buffer, size_t size)
{
	/*
	 * If this is a request for a synthetic attribute in the system.*
	 * namespace use the generic infrastructure to resolve a handler
	 * for it via sb->s_xattr.
	 */
	if (!strncmp(name, XATTR_SYSTEM_PREFIX, XATTR_SYSTEM_PREFIX_LEN))
		return generic_getxattr(dentry, name, buffer, size);

	if (!btrfs_is_valid_xattr(name))
		return -EOPNOTSUPP;
	return __btrfs_getxattr(dentry->d_inode, name, buffer, size);
}