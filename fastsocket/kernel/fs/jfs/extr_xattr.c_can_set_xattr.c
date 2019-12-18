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
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  XATTR_OS2_PREFIX ; 
 int /*<<< orphan*/  XATTR_OS2_PREFIX_LEN ; 
 int /*<<< orphan*/  XATTR_SECURITY_PREFIX ; 
 int /*<<< orphan*/  XATTR_SECURITY_PREFIX_LEN ; 
 int /*<<< orphan*/  XATTR_SYSTEM_PREFIX ; 
 int /*<<< orphan*/  XATTR_SYSTEM_PREFIX_LEN ; 
 int /*<<< orphan*/  XATTR_TRUSTED_PREFIX ; 
 int /*<<< orphan*/  XATTR_TRUSTED_PREFIX_LEN ; 
 int /*<<< orphan*/  XATTR_USER_PREFIX ; 
 int /*<<< orphan*/  XATTR_USER_PREFIX_LEN ; 
 int can_set_system_xattr (struct inode*,char const*,void const*,size_t) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int can_set_xattr(struct inode *inode, const char *name,
			 const void *value, size_t value_len)
{
	if (!strncmp(name, XATTR_SYSTEM_PREFIX, XATTR_SYSTEM_PREFIX_LEN))
		return can_set_system_xattr(inode, name, value, value_len);

	/*
	 * Don't allow setting an attribute in an unknown namespace.
	 */
	if (strncmp(name, XATTR_TRUSTED_PREFIX, XATTR_TRUSTED_PREFIX_LEN) &&
	    strncmp(name, XATTR_SECURITY_PREFIX, XATTR_SECURITY_PREFIX_LEN) &&
	    strncmp(name, XATTR_USER_PREFIX, XATTR_USER_PREFIX_LEN) &&
	    strncmp(name, XATTR_OS2_PREFIX, XATTR_OS2_PREFIX_LEN))
		return -EOPNOTSUPP;

	return 0;
}