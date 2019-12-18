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
 int ACL_TYPE_ACCESS ; 
 int ACL_TYPE_DEFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFS2_POSIX_ACL_ACCESS ; 
 int /*<<< orphan*/  GFS2_POSIX_ACL_DEFAULT ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfs2_acl_type(const char *name)
{
	if (strcmp(name, GFS2_POSIX_ACL_ACCESS) == 0)
		return ACL_TYPE_ACCESS;
	if (strcmp(name, GFS2_POSIX_ACL_DEFAULT) == 0)
		return ACL_TYPE_DEFAULT;
	return -EINVAL;
}