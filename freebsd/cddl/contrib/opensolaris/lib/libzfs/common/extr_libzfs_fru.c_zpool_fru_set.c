#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* zpool_name; int /*<<< orphan*/  zpool_hdl; } ;
typedef  TYPE_1__ zpool_handle_t ;
struct TYPE_6__ {int /*<<< orphan*/  zc_guid; int /*<<< orphan*/  zc_value; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_SETFRU ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int zpool_standard_error_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
zpool_fru_set(zpool_handle_t *zhp, uint64_t vdev_guid, const char *fru)
{
	zfs_cmd_t zc = { 0 };

	(void) strncpy(zc.zc_name, zhp->zpool_name, sizeof (zc.zc_name));
	(void) strncpy(zc.zc_value, fru, sizeof (zc.zc_value));
	zc.zc_guid = vdev_guid;

	if (zfs_ioctl(zhp->zpool_hdl, ZFS_IOC_VDEV_SETFRU, &zc) != 0)
		return (zpool_standard_error_fmt(zhp->zpool_hdl, errno,
		    dgettext(TEXT_DOMAIN, "cannot set FRU")));

	return (0);
}