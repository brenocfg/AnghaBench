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

/* Variables and functions */
 int /*<<< orphan*/  XATTR_SECURITY_PREFIX ; 
 int /*<<< orphan*/  XATTR_SECURITY_PREFIX_LEN ; 
 int /*<<< orphan*/  XATTR_SYSTEM_PREFIX ; 
 int /*<<< orphan*/  XATTR_SYSTEM_PREFIX_LEN ; 
 int /*<<< orphan*/  XATTR_TRUSTED_PREFIX ; 
 int /*<<< orphan*/  XATTR_TRUSTED_PREFIX_LEN ; 
 int /*<<< orphan*/  XATTR_USER_PREFIX ; 
 int /*<<< orphan*/  XATTR_USER_PREFIX_LEN ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool btrfs_is_valid_xattr(const char *name)
{
	return !strncmp(name, XATTR_SECURITY_PREFIX,
			XATTR_SECURITY_PREFIX_LEN) ||
	       !strncmp(name, XATTR_SYSTEM_PREFIX, XATTR_SYSTEM_PREFIX_LEN) ||
	       !strncmp(name, XATTR_TRUSTED_PREFIX, XATTR_TRUSTED_PREFIX_LEN) ||
	       !strncmp(name, XATTR_USER_PREFIX, XATTR_USER_PREFIX_LEN);
}