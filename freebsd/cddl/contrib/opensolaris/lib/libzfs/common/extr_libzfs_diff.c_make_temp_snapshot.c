#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  zc_value; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  zc_cleanup_fd; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
struct TYPE_13__ {int /*<<< orphan*/  libzfs_fd; } ;
typedef  TYPE_3__ libzfs_handle_t ;
struct TYPE_14__ {int /*<<< orphan*/  tmpsnap; int /*<<< orphan*/  ds; int /*<<< orphan*/  tosnap; int /*<<< orphan*/  errbuf; int /*<<< orphan*/  cleanupfd; TYPE_1__* zhp; } ;
typedef  TYPE_4__ differ_info_t ;
struct TYPE_11__ {TYPE_3__* zfs_hdl; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  EZFS_DIFF ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 char* ZDIFF_PREFIX ; 
 int /*<<< orphan*/  ZFS_IOC_TMP_SNAPSHOT ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_asprintf (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zfs_error (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zfs_standard_error (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_strdup (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
make_temp_snapshot(differ_info_t *di)
{
	libzfs_handle_t *hdl = di->zhp->zfs_hdl;
	zfs_cmd_t zc = { 0 };

	(void) snprintf(zc.zc_value, sizeof (zc.zc_value),
	    ZDIFF_PREFIX, getpid());
	(void) strlcpy(zc.zc_name, di->ds, sizeof (zc.zc_name));
	zc.zc_cleanup_fd = di->cleanupfd;

	if (ioctl(hdl->libzfs_fd, ZFS_IOC_TMP_SNAPSHOT, &zc) != 0) {
		int err = errno;
		if (err == EPERM) {
			(void) snprintf(di->errbuf, sizeof (di->errbuf),
			    dgettext(TEXT_DOMAIN, "The diff delegated "
			    "permission is needed in order\nto create a "
			    "just-in-time snapshot for diffing\n"));
			return (zfs_error(hdl, EZFS_DIFF, di->errbuf));
		} else {
			(void) snprintf(di->errbuf, sizeof (di->errbuf),
			    dgettext(TEXT_DOMAIN, "Cannot create just-in-time "
			    "snapshot of '%s'"), zc.zc_name);
			return (zfs_standard_error(hdl, err, di->errbuf));
		}
	}

	di->tmpsnap = zfs_strdup(hdl, zc.zc_value);
	di->tosnap = zfs_asprintf(hdl, "%s@%s", di->ds, di->tmpsnap);
	return (0);
}