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

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EPERM ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 int MAY_WRITE ; 
 scalar_t__ S_ISDIR (int) ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 int S_ISVTX ; 
 int /*<<< orphan*/  XATTR_SECURITY_PREFIX ; 
 int /*<<< orphan*/  XATTR_SECURITY_PREFIX_LEN ; 
 int /*<<< orphan*/  XATTR_SYSTEM_PREFIX ; 
 int /*<<< orphan*/  XATTR_SYSTEM_PREFIX_LEN ; 
 int /*<<< orphan*/  XATTR_TRUSTED_PREFIX ; 
 int /*<<< orphan*/  XATTR_TRUSTED_PREFIX_LEN ; 
 int /*<<< orphan*/  XATTR_USER_PREFIX ; 
 int /*<<< orphan*/  XATTR_USER_PREFIX_LEN ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int inode_permission (struct inode*,int) ; 
 int /*<<< orphan*/  is_owner_or_cap (struct inode*) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xattr_permission(struct inode *inode, const char *name, int mask)
{
	/*
	 * We can never set or remove an extended attribute on a read-only
	 * filesystem  or on an immutable / append-only inode.
	 */
	if (mask & MAY_WRITE) {
		if (IS_IMMUTABLE(inode) || IS_APPEND(inode))
			return -EPERM;
	}

	/*
	 * No restriction for security.* and system.* from the VFS.  Decision
	 * on these is left to the underlying filesystem / security module.
	 */
	if (!strncmp(name, XATTR_SECURITY_PREFIX, XATTR_SECURITY_PREFIX_LEN) ||
	    !strncmp(name, XATTR_SYSTEM_PREFIX, XATTR_SYSTEM_PREFIX_LEN))
		return 0;

	/*
	 * The trusted.* namespace can only be accessed by a privileged user.
	 */
	if (!strncmp(name, XATTR_TRUSTED_PREFIX, XATTR_TRUSTED_PREFIX_LEN))
		return (capable(CAP_SYS_ADMIN) ? 0 : -EPERM);

	/* In user.* namespace, only regular files and directories can have
	 * extended attributes. For sticky directories, only the owner and
	 * privileged user can write attributes.
	 */
	if (!strncmp(name, XATTR_USER_PREFIX, XATTR_USER_PREFIX_LEN)) {
		if (!S_ISREG(inode->i_mode) && !S_ISDIR(inode->i_mode))
			return -EPERM;
		if (S_ISDIR(inode->i_mode) && (inode->i_mode & S_ISVTX) &&
		    (mask & MAY_WRITE) && !is_owner_or_cap(inode))
			return -EPERM;
	}

	return inode_permission(inode, mask);
}