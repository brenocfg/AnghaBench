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
struct TYPE_8__ {int /*<<< orphan*/  zpool_name; int /*<<< orphan*/ * zpool_hdl; } ;
typedef  TYPE_1__ zpool_handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  EBUSY 133 
#define  EDOM 132 
#define  EINVAL 131 
#define  ENOTBLK 130 
#define  ENOTSUP 129 
#define  EOVERFLOW 128 
 int /*<<< orphan*/  EZFS_BADDEV ; 
 int /*<<< orphan*/  EZFS_BADVERSION ; 
 int /*<<< orphan*/  EZFS_POOL_NOTSUP ; 
 int /*<<< orphan*/  SPA_MINDEVSIZE ; 
 scalar_t__ SPA_VERSION_L2CACHE ; 
 scalar_t__ SPA_VERSION_SPARES ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_ADD ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_L2CACHE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SPARES ; 
 int /*<<< orphan*/  ZPOOL_PROP_VERSION ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_2__*) ; 
 scalar_t__ zcmd_write_conf_nvlist (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_nicenum (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ zpool_get_prop_int (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_standard_error (int /*<<< orphan*/ *,int,char*) ; 

int
zpool_add(zpool_handle_t *zhp, nvlist_t *nvroot)
{
	zfs_cmd_t zc = { 0 };
	int ret;
	libzfs_handle_t *hdl = zhp->zpool_hdl;
	char msg[1024];
	nvlist_t **spares, **l2cache;
	uint_t nspares, nl2cache;

	(void) snprintf(msg, sizeof (msg), dgettext(TEXT_DOMAIN,
	    "cannot add to '%s'"), zhp->zpool_name);

	if (zpool_get_prop_int(zhp, ZPOOL_PROP_VERSION, NULL) <
	    SPA_VERSION_SPARES &&
	    nvlist_lookup_nvlist_array(nvroot, ZPOOL_CONFIG_SPARES,
	    &spares, &nspares) == 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "pool must be "
		    "upgraded to add hot spares"));
		return (zfs_error(hdl, EZFS_BADVERSION, msg));
	}

	if (zpool_get_prop_int(zhp, ZPOOL_PROP_VERSION, NULL) <
	    SPA_VERSION_L2CACHE &&
	    nvlist_lookup_nvlist_array(nvroot, ZPOOL_CONFIG_L2CACHE,
	    &l2cache, &nl2cache) == 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "pool must be "
		    "upgraded to add cache devices"));
		return (zfs_error(hdl, EZFS_BADVERSION, msg));
	}

	if (zcmd_write_conf_nvlist(hdl, &zc, nvroot) != 0)
		return (-1);
	(void) strlcpy(zc.zc_name, zhp->zpool_name, sizeof (zc.zc_name));

	if (zfs_ioctl(hdl, ZFS_IOC_VDEV_ADD, &zc) != 0) {
		switch (errno) {
		case EBUSY:
			/*
			 * This can happen if the user has specified the same
			 * device multiple times.  We can't reliably detect this
			 * until we try to add it and see we already have a
			 * label.
			 */
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "one or more vdevs refer to the same device"));
			(void) zfs_error(hdl, EZFS_BADDEV, msg);
			break;

		case EINVAL:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "invalid config; a pool with removing/removed "
			    "vdevs does not support adding raidz vdevs"));
			(void) zfs_error(hdl, EZFS_BADDEV, msg);
			break;

		case EOVERFLOW:
			/*
			 * This occurrs when one of the devices is below
			 * SPA_MINDEVSIZE.  Unfortunately, we can't detect which
			 * device was the problem device since there's no
			 * reliable way to determine device size from userland.
			 */
			{
				char buf[64];

				zfs_nicenum(SPA_MINDEVSIZE, buf, sizeof (buf));

				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "device is less than the minimum "
				    "size (%s)"), buf);
			}
			(void) zfs_error(hdl, EZFS_BADDEV, msg);
			break;

		case ENOTSUP:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "pool must be upgraded to add these vdevs"));
			(void) zfs_error(hdl, EZFS_BADVERSION, msg);
			break;

		case EDOM:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "root pool can not have multiple vdevs"
			    " or separate logs"));
			(void) zfs_error(hdl, EZFS_POOL_NOTSUP, msg);
			break;

		case ENOTBLK:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "cache device must be a disk or disk slice"));
			(void) zfs_error(hdl, EZFS_BADDEV, msg);
			break;

		default:
			(void) zpool_standard_error(hdl, errno, msg);
		}

		ret = -1;
	} else {
		ret = 0;
	}

	zcmd_free_nvlists(&zc);

	return (ret);
}