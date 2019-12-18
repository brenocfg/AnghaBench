#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_share_op_t ;
struct TYPE_6__ {int z_sharemax; int /*<<< orphan*/  z_sharetype; void* z_exportdata; void* z_sharedata; } ;
struct TYPE_7__ {TYPE_1__ zc_share; int /*<<< orphan*/  zc_string; int /*<<< orphan*/  zc_value; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  void* uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  libzfs_fd; } ;
typedef  TYPE_3__ libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_SHARE ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

int
zfs_deleg_share_nfs(libzfs_handle_t *hdl, char *dataset, char *path,
    char *resource, void *export, void *sharetab,
    int sharemax, zfs_share_op_t operation)
{
	zfs_cmd_t zc = { 0 };
	int error;

	(void) strlcpy(zc.zc_name, dataset, sizeof (zc.zc_name));
	(void) strlcpy(zc.zc_value, path, sizeof (zc.zc_value));
	if (resource)
		(void) strlcpy(zc.zc_string, resource, sizeof (zc.zc_string));
	zc.zc_share.z_sharedata = (uint64_t)(uintptr_t)sharetab;
	zc.zc_share.z_exportdata = (uint64_t)(uintptr_t)export;
	zc.zc_share.z_sharetype = operation;
	zc.zc_share.z_sharemax = sharemax;
	error = ioctl(hdl->libzfs_fd, ZFS_IOC_SHARE, &zc);
	return (error);
}