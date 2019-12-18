#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int zfs_ioc_t ;
struct TYPE_3__ {int /*<<< orphan*/  zc_nvlist_dst_filled; } ;
typedef  TYPE_1__ zfs_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ ZFS_IOCVER_LZC ; 
#define  ZFS_IOC_CLONE 132 
#define  ZFS_IOC_CREATE 131 
#define  ZFS_IOC_DESTROY_SNAPS 130 
#define  ZFS_IOC_SNAPSHOT 129 
#define  ZFS_IOC_SPACE_SNAPS 128 
 scalar_t__ zfs_ioctl_version ; 

void
lzc_compat_post(zfs_cmd_t *zc, const zfs_ioc_t ioc)
{
	if (zfs_ioctl_version >= ZFS_IOCVER_LZC)
		return;

	switch (ioc) {
	case ZFS_IOC_CREATE:
	case ZFS_IOC_CLONE:
	case ZFS_IOC_SNAPSHOT:
	case ZFS_IOC_SPACE_SNAPS:
	case ZFS_IOC_DESTROY_SNAPS:
		zc->zc_nvlist_dst_filled = B_FALSE;
	break;
	}
}