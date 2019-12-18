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
struct jfs_ea {scalar_t__ namelen; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  XATTR_SECURITY_PREFIX ; 
 scalar_t__ XATTR_SECURITY_PREFIX_LEN ; 
 int /*<<< orphan*/  XATTR_SYSTEM_PREFIX ; 
 scalar_t__ XATTR_SYSTEM_PREFIX_LEN ; 
 int /*<<< orphan*/  XATTR_TRUSTED_PREFIX ; 
 scalar_t__ XATTR_TRUSTED_PREFIX_LEN ; 
 int /*<<< orphan*/  XATTR_USER_PREFIX ; 
 scalar_t__ XATTR_USER_PREFIX_LEN ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int is_os2_xattr(struct jfs_ea *ea)
{
	/*
	 * Check for "system."
	 */
	if ((ea->namelen >= XATTR_SYSTEM_PREFIX_LEN) &&
	    !strncmp(ea->name, XATTR_SYSTEM_PREFIX, XATTR_SYSTEM_PREFIX_LEN))
		return false;
	/*
	 * Check for "user."
	 */
	if ((ea->namelen >= XATTR_USER_PREFIX_LEN) &&
	    !strncmp(ea->name, XATTR_USER_PREFIX, XATTR_USER_PREFIX_LEN))
		return false;
	/*
	 * Check for "security."
	 */
	if ((ea->namelen >= XATTR_SECURITY_PREFIX_LEN) &&
	    !strncmp(ea->name, XATTR_SECURITY_PREFIX,
		     XATTR_SECURITY_PREFIX_LEN))
		return false;
	/*
	 * Check for "trusted."
	 */
	if ((ea->namelen >= XATTR_TRUSTED_PREFIX_LEN) &&
	    !strncmp(ea->name, XATTR_TRUSTED_PREFIX, XATTR_TRUSTED_PREFIX_LEN))
		return false;
	/*
	 * Add any other valid namespace prefixes here
	 */

	/*
	 * We assume it's OS/2's flat namespace
	 */
	return true;
}