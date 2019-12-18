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
struct TYPE_9__ {int zfs_type; int /*<<< orphan*/  zfs_name; TYPE_3__* zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_10__ {int zc_jailid; int /*<<< orphan*/  zc_objset_type; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
struct TYPE_11__ {int /*<<< orphan*/  libzfs_fd; } ;
typedef  TYPE_3__ libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_OST_ZFS ; 
 int /*<<< orphan*/  EZFS_BADTYPE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 unsigned long ZFS_IOC_JAIL ; 
 unsigned long ZFS_IOC_UNJAIL ; 
 int ZFS_TYPE_FILESYSTEM ; 
#define  ZFS_TYPE_SNAPSHOT 129 
#define  ZFS_TYPE_VOLUME 128 
 int /*<<< orphan*/  assert (int) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,unsigned long,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int zfs_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  zfs_standard_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 

int
zfs_jail(zfs_handle_t *zhp, int jailid, int attach)
{
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	zfs_cmd_t zc = { 0 };
	char errbuf[1024];
	unsigned long cmd;
	int ret;

	if (attach) {
		(void) snprintf(errbuf, sizeof (errbuf),
		    dgettext(TEXT_DOMAIN, "cannot jail '%s'"), zhp->zfs_name);
	} else {
		(void) snprintf(errbuf, sizeof (errbuf),
		    dgettext(TEXT_DOMAIN, "cannot unjail '%s'"), zhp->zfs_name);
	}

	switch (zhp->zfs_type) {
	case ZFS_TYPE_VOLUME:
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "volumes can not be jailed"));
		return (zfs_error(hdl, EZFS_BADTYPE, errbuf));
	case ZFS_TYPE_SNAPSHOT:
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "snapshots can not be jailed"));
		return (zfs_error(hdl, EZFS_BADTYPE, errbuf));
	}
	assert(zhp->zfs_type == ZFS_TYPE_FILESYSTEM);

	(void) strlcpy(zc.zc_name, zhp->zfs_name, sizeof (zc.zc_name));
	zc.zc_objset_type = DMU_OST_ZFS;
	zc.zc_jailid = jailid;

	cmd = attach ? ZFS_IOC_JAIL : ZFS_IOC_UNJAIL;
	if ((ret = ioctl(hdl->libzfs_fd, cmd, &zc)) != 0)
		zfs_standard_error(hdl, errno, errbuf);

	return (ret);
}