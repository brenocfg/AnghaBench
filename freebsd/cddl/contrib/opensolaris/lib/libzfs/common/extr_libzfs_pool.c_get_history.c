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
struct TYPE_9__ {void* zc_history_offset; void* zc_history_len; void* zc_history; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  void* uint64_t ;
struct TYPE_10__ {int /*<<< orphan*/  libzfs_fd; } ;
typedef  TYPE_3__ libzfs_handle_t ;

/* Variables and functions */
#define  ENOENT 130 
#define  ENOTSUP 129 
#define  EPERM 128 
 int /*<<< orphan*/  EZFS_BADVERSION ; 
 int /*<<< orphan*/  EZFS_NOHISTORY ; 
 int /*<<< orphan*/  EZFS_PERM ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_GET_HISTORY ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int zfs_error_fmt (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zpool_standard_error_fmt (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_history(zpool_handle_t *zhp, char *buf, uint64_t *off, uint64_t *len)
{
	zfs_cmd_t zc = { 0 };
	libzfs_handle_t *hdl = zhp->zpool_hdl;

	(void) strlcpy(zc.zc_name, zhp->zpool_name, sizeof (zc.zc_name));

	zc.zc_history = (uint64_t)(uintptr_t)buf;
	zc.zc_history_len = *len;
	zc.zc_history_offset = *off;

	if (ioctl(hdl->libzfs_fd, ZFS_IOC_POOL_GET_HISTORY, &zc) != 0) {
		switch (errno) {
		case EPERM:
			return (zfs_error_fmt(hdl, EZFS_PERM,
			    dgettext(TEXT_DOMAIN,
			    "cannot show history for pool '%s'"),
			    zhp->zpool_name));
		case ENOENT:
			return (zfs_error_fmt(hdl, EZFS_NOHISTORY,
			    dgettext(TEXT_DOMAIN, "cannot get history for pool "
			    "'%s'"), zhp->zpool_name));
		case ENOTSUP:
			return (zfs_error_fmt(hdl, EZFS_BADVERSION,
			    dgettext(TEXT_DOMAIN, "cannot get history for pool "
			    "'%s', pool must be upgraded"), zhp->zpool_name));
		default:
			return (zpool_standard_error_fmt(hdl, errno,
			    dgettext(TEXT_DOMAIN,
			    "cannot get history for '%s'"), zhp->zpool_name));
		}
	}

	*len = zc.zc_history_len;
	*off = zc.zc_history_offset;

	return (0);
}