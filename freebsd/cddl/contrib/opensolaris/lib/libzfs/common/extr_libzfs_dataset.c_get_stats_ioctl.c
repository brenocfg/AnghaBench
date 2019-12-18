#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  zfs_name; TYPE_3__* zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_10__ {int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_2__ zfs_cmd_t ;
struct TYPE_11__ {int /*<<< orphan*/  libzfs_fd; } ;
typedef  TYPE_3__ libzfs_handle_t ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  ZFS_IOC_OBJSET_STATS ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ zcmd_expand_dst_nvlist (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static int
get_stats_ioctl(zfs_handle_t *zhp, zfs_cmd_t *zc)
{
	libzfs_handle_t *hdl = zhp->zfs_hdl;

	(void) strlcpy(zc->zc_name, zhp->zfs_name, sizeof (zc->zc_name));

	while (ioctl(hdl->libzfs_fd, ZFS_IOC_OBJSET_STATS, zc) != 0) {
		if (errno == ENOMEM) {
			if (zcmd_expand_dst_nvlist(hdl, zc) != 0) {
				return (-1);
			}
		} else {
			return (-1);
		}
	}
	return (0);
}