#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zpool_name; TYPE_3__* zpool_hdl; } ;
typedef  TYPE_1__ zpool_handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  zc_obj; int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_guid; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  vdev_aux_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_10__ {int /*<<< orphan*/  libzfs_fd; } ;
typedef  TYPE_3__ libzfs_handle_t ;

/* Variables and functions */
#define  EBUSY 128 
 int /*<<< orphan*/  EZFS_NOREPLICAS ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  VDEV_STATE_FAULTED ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_SET_STATE ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int zfs_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int zpool_standard_error (TYPE_3__*,int,char*) ; 

int
zpool_vdev_fault(zpool_handle_t *zhp, uint64_t guid, vdev_aux_t aux)
{
	zfs_cmd_t zc = { 0 };
	char msg[1024];
	libzfs_handle_t *hdl = zhp->zpool_hdl;

	(void) snprintf(msg, sizeof (msg),
	    dgettext(TEXT_DOMAIN, "cannot fault %llu"), guid);

	(void) strlcpy(zc.zc_name, zhp->zpool_name, sizeof (zc.zc_name));
	zc.zc_guid = guid;
	zc.zc_cookie = VDEV_STATE_FAULTED;
	zc.zc_obj = aux;

	if (ioctl(hdl->libzfs_fd, ZFS_IOC_VDEV_SET_STATE, &zc) == 0)
		return (0);

	switch (errno) {
	case EBUSY:

		/*
		 * There are no other replicas of this device.
		 */
		return (zfs_error(hdl, EZFS_NOREPLICAS, msg));

	default:
		return (zpool_standard_error(hdl, errno, msg));
	}

}