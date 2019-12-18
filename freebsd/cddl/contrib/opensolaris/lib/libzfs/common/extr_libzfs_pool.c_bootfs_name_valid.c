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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_SNAPSHOT ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  zfs_name_valid (char*,int) ; 

__attribute__((used)) static boolean_t
bootfs_name_valid(const char *pool, char *bootfs)
{
	int len = strlen(pool);

	if (!zfs_name_valid(bootfs, ZFS_TYPE_FILESYSTEM|ZFS_TYPE_SNAPSHOT))
		return (B_FALSE);

	if (strncmp(pool, bootfs, len) == 0 &&
	    (bootfs[len] == '/' || bootfs[len] == '\0'))
		return (B_TRUE);

	return (B_FALSE);
}