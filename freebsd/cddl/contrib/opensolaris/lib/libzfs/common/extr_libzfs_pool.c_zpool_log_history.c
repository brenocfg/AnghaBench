#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_9__ {int /*<<< orphan*/  libzfs_fd; } ;
typedef  TYPE_2__ libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_LOG_HISTORY ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_1__*) ; 
 int zcmd_write_src_nvlist (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 

int
zpool_log_history(libzfs_handle_t *hdl, const char *message)
{
	zfs_cmd_t zc = { 0 };
	nvlist_t *args;
	int err;

	args = fnvlist_alloc();
	fnvlist_add_string(args, "message", message);
	err = zcmd_write_src_nvlist(hdl, &zc, args);
	if (err == 0)
		err = ioctl(hdl->libzfs_fd, ZFS_IOC_LOG_HISTORY, &zc);
	nvlist_free(args);
	zcmd_free_nvlists(&zc);
	return (err);
}