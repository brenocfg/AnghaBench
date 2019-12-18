#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t zc_nvlist_dst_size; } ;
typedef  TYPE_1__ zfs_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ SPA_VERSION_13 ; 
 scalar_t__ SPA_VERSION_14 ; 
 scalar_t__ SPA_VERSION_15 ; 
 int ZFS_CMD_COMPAT_DEADMAN ; 
 int ZFS_CMD_COMPAT_EDBP ; 
 int ZFS_CMD_COMPAT_INLANES ; 
 int ZFS_CMD_COMPAT_LZC ; 
 int ZFS_CMD_COMPAT_NONE ; 
 int ZFS_CMD_COMPAT_RESUME ; 
 int ZFS_CMD_COMPAT_V15 ; 
 int ZFS_CMD_COMPAT_V28 ; 
 int ZFS_CMD_COMPAT_ZCMD ; 
#define  ZFS_IOCVER_DEADMAN 133 
#define  ZFS_IOCVER_EDBP 132 
#define  ZFS_IOCVER_INLANES 131 
#define  ZFS_IOCVER_LZC 130 
#define  ZFS_IOCVER_RESUME 129 
 int ZFS_IOCVER_UNDEF ; 
#define  ZFS_IOCVER_ZCMD 128 
 int /*<<< orphan*/  errno ; 
 int get_zfs_ioctl_version () ; 
 scalar_t__ get_zfs_spa_version () ; 
 int zcmd_ioctl_compat (int,int,TYPE_1__*,int) ; 
 int zfs_ioctl_version ; 
 scalar_t__ zfs_spa_version ; 

int
zcmd_ioctl(int fd, int request, zfs_cmd_t *zc)
{
	size_t oldsize;
	int ret, cflag = ZFS_CMD_COMPAT_NONE;

	if (zfs_ioctl_version == ZFS_IOCVER_UNDEF)
		zfs_ioctl_version = get_zfs_ioctl_version();

	if (zfs_ioctl_version >= ZFS_IOCVER_DEADMAN) {
		switch (zfs_ioctl_version) {
		case ZFS_IOCVER_INLANES:
			cflag = ZFS_CMD_COMPAT_INLANES;
			break;
		case ZFS_IOCVER_RESUME:
			cflag = ZFS_CMD_COMPAT_RESUME;
			break;
		case ZFS_IOCVER_EDBP:
			cflag = ZFS_CMD_COMPAT_EDBP;
			break;
		case ZFS_IOCVER_ZCMD:
			cflag = ZFS_CMD_COMPAT_ZCMD;
			break;
		case ZFS_IOCVER_LZC:
			cflag = ZFS_CMD_COMPAT_LZC;
			break;
		case ZFS_IOCVER_DEADMAN:
			cflag = ZFS_CMD_COMPAT_DEADMAN;
			break;
		}
	} else {
		/*
		 * If vfs.zfs.version.ioctl is not defined, assume we have v28
		 * compatible binaries and use vfs.zfs.version.spa to test for v15
		 */
		cflag = ZFS_CMD_COMPAT_V28;

		if (zfs_spa_version < 0)
			zfs_spa_version = get_zfs_spa_version();

		if (zfs_spa_version == SPA_VERSION_15 ||
		    zfs_spa_version == SPA_VERSION_14 ||
		    zfs_spa_version == SPA_VERSION_13)
			cflag = ZFS_CMD_COMPAT_V15;
	}

	oldsize = zc->zc_nvlist_dst_size;
	ret = zcmd_ioctl_compat(fd, request, zc, cflag);

	if (ret == 0 && oldsize < zc->zc_nvlist_dst_size) {
		ret = -1;
		errno = ENOMEM;
	}

	return (ret);
}