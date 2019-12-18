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
struct TYPE_3__ {int /*<<< orphan*/  zc_perm_action; int /*<<< orphan*/  zc_objset_type; int /*<<< orphan*/  zc_cookie; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 scalar_t__ ZFS_IOCVER_LZC ; 
#define  ZFS_IOC_SPACE_SNAPS 128 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 scalar_t__ zfs_ioctl_version ; 

int
lzc_compat_outnvl(zfs_cmd_t *zc, const zfs_ioc_t ioc, nvlist_t **outnvl)
{
	nvlist_t *nvl;

	if (zfs_ioctl_version >= ZFS_IOCVER_LZC)
		return (0);

	switch (ioc) {
	case ZFS_IOC_SPACE_SNAPS:
		nvl = fnvlist_alloc();
		fnvlist_add_uint64(nvl, "used", zc->zc_cookie);
		fnvlist_add_uint64(nvl, "compressed", zc->zc_objset_type);
		fnvlist_add_uint64(nvl, "uncompressed", zc->zc_perm_action);
		*outnvl = nvl;
	break;
	}

	return (0);
}