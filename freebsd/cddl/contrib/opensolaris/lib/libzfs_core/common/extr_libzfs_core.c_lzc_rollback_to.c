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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_ROLLBACK ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int lzc_ioctl (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

int
lzc_rollback_to(const char *fsname, const char *snapname)
{
	nvlist_t *args;
	nvlist_t *result;
	int err;

	args = fnvlist_alloc();
	fnvlist_add_string(args, "target", snapname);
	err = lzc_ioctl(ZFS_IOC_ROLLBACK, fsname, args, &result);
	nvlist_free(args);
	nvlist_free(result);
	return (err);
}