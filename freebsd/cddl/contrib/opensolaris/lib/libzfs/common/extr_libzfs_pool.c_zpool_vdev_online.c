#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zpool_name; int /*<<< orphan*/ * zpool_hdl; } ;
typedef  TYPE_1__ zpool_handle_t ;
struct TYPE_8__ {int zc_obj; int /*<<< orphan*/  zc_cookie; scalar_t__ zc_guid; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  vdev_state_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  EZFS_ISSPARE ; 
 int /*<<< orphan*/  EZFS_NODEVICE ; 
 int /*<<< orphan*/  EZFS_POSTSPLIT_ONLINE ; 
 int /*<<< orphan*/  EZFS_VDEVNOTSUP ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  VDEV_STATE_ONLINE ; 
 int /*<<< orphan*/  ZFS_DISK_ROOT ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_SET_STATE ; 
 int ZFS_ONLINE_EXPAND ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_WHOLE_DISK ; 
 int /*<<< orphan*/  ZPOOL_PROP_AUTOEXPAND ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify (int) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * zpool_find_vdev (TYPE_1__*,char const*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ zpool_get_prop_int (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_relabel_disk (int /*<<< orphan*/ *,char*) ; 
 int zpool_standard_error (int /*<<< orphan*/ *,scalar_t__,char*) ; 

int
zpool_vdev_online(zpool_handle_t *zhp, const char *path, int flags,
    vdev_state_t *newstate)
{
	zfs_cmd_t zc = { 0 };
	char msg[1024];
	char *pathname;
	nvlist_t *tgt;
	boolean_t avail_spare, l2cache, islog;
	libzfs_handle_t *hdl = zhp->zpool_hdl;

	if (flags & ZFS_ONLINE_EXPAND) {
		(void) snprintf(msg, sizeof (msg),
		    dgettext(TEXT_DOMAIN, "cannot expand %s"), path);
	} else {
		(void) snprintf(msg, sizeof (msg),
		    dgettext(TEXT_DOMAIN, "cannot online %s"), path);
	}

	(void) strlcpy(zc.zc_name, zhp->zpool_name, sizeof (zc.zc_name));
	if ((tgt = zpool_find_vdev(zhp, path, &avail_spare, &l2cache,
	    &islog)) == NULL)
		return (zfs_error(hdl, EZFS_NODEVICE, msg));

	verify(nvlist_lookup_uint64(tgt, ZPOOL_CONFIG_GUID, &zc.zc_guid) == 0);

	if (avail_spare)
		return (zfs_error(hdl, EZFS_ISSPARE, msg));

	if ((flags & ZFS_ONLINE_EXPAND ||
	    zpool_get_prop_int(zhp, ZPOOL_PROP_AUTOEXPAND, NULL)) &&
	    nvlist_lookup_string(tgt, ZPOOL_CONFIG_PATH, &pathname) == 0) {
		uint64_t wholedisk = 0;

		(void) nvlist_lookup_uint64(tgt, ZPOOL_CONFIG_WHOLE_DISK,
		    &wholedisk);

		/*
		 * XXX - L2ARC 1.0 devices can't support expansion.
		 */
		if (l2cache) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "cannot expand cache devices"));
			return (zfs_error(hdl, EZFS_VDEVNOTSUP, msg));
		}

		if (wholedisk) {
			pathname += strlen(ZFS_DISK_ROOT) + 1;
			(void) zpool_relabel_disk(hdl, pathname);
		}
	}

	zc.zc_cookie = VDEV_STATE_ONLINE;
	zc.zc_obj = flags;

	if (zfs_ioctl(hdl, ZFS_IOC_VDEV_SET_STATE, &zc) != 0) {
		if (errno == EINVAL) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "was split "
			    "from this pool into a new one.  Use '%s' "
			    "instead"), "zpool detach");
			return (zfs_error(hdl, EZFS_POSTSPLIT_ONLINE, msg));
		}
		return (zpool_standard_error(hdl, errno, msg));
	}

	*newstate = zc.zc_cookie;
	return (0);
}