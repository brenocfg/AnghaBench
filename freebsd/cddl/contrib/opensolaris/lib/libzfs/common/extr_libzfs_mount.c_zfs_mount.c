#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* zfs_name; int /*<<< orphan*/  zpool_hdl; int /*<<< orphan*/ * zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  mountpoint ;
typedef  int /*<<< orphan*/  mntopts ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 scalar_t__ ENOTSUP ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  EZFS_MOUNTFAILED ; 
 int /*<<< orphan*/  MNTOPT_REMOUNT ; 
 int /*<<< orphan*/  MNTTYPE_ZFS ; 
 int MNT_LINE_MAX ; 
 int MS_OVERLAY ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZFS_MAXPROPLEN ; 
 int /*<<< orphan*/  ZFS_PROP_VERSION ; 
 int /*<<< orphan*/  ZPOOL_PROP_READONLY ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dir_is_empty (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  libzfs_mnttab_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ mkdirp (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int) ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/ * strstr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 int zfs_error_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  zfs_get_name (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_is_mountable (TYPE_1__*,char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_prop_get_int (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_spa_version (TYPE_1__*,int*) ; 
 scalar_t__ zmount (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ zpool_get_prop_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
zfs_mount(zfs_handle_t *zhp, const char *options, int flags)
{
	struct stat buf;
	char mountpoint[ZFS_MAXPROPLEN];
	char mntopts[MNT_LINE_MAX];
	libzfs_handle_t *hdl = zhp->zfs_hdl;

	if (options == NULL)
		mntopts[0] = '\0';
	else
		(void) strlcpy(mntopts, options, sizeof (mntopts));

	/*
	 * If the pool is imported read-only then all mounts must be read-only
	 */
	if (zpool_get_prop_int(zhp->zpool_hdl, ZPOOL_PROP_READONLY, NULL))
		flags |= MS_RDONLY;

	if (!zfs_is_mountable(zhp, mountpoint, sizeof (mountpoint), NULL))
		return (0);

	/* Create the directory if it doesn't already exist */
	if (lstat(mountpoint, &buf) != 0) {
		if (mkdirp(mountpoint, 0755) != 0) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "failed to create mountpoint"));
			return (zfs_error_fmt(hdl, EZFS_MOUNTFAILED,
			    dgettext(TEXT_DOMAIN, "cannot mount '%s'"),
			    mountpoint));
		}
	}

#ifdef illumos	/* FreeBSD: overlay mounts are not checked. */
	/*
	 * Determine if the mountpoint is empty.  If so, refuse to perform the
	 * mount.  We don't perform this check if MS_OVERLAY is specified, which
	 * would defeat the point.  We also avoid this check if 'remount' is
	 * specified.
	 */
	if ((flags & MS_OVERLAY) == 0 &&
	    strstr(mntopts, MNTOPT_REMOUNT) == NULL &&
	    !dir_is_empty(mountpoint)) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "directory is not empty"));
		return (zfs_error_fmt(hdl, EZFS_MOUNTFAILED,
		    dgettext(TEXT_DOMAIN, "cannot mount '%s'"), mountpoint));
	}
#endif

	/* perform the mount */
	if (zmount(zfs_get_name(zhp), mountpoint, flags,
	    MNTTYPE_ZFS, NULL, 0, mntopts, sizeof (mntopts)) != 0) {
		/*
		 * Generic errors are nasty, but there are just way too many
		 * from mount(), and they're well-understood.  We pick a few
		 * common ones to improve upon.
		 */
		if (errno == EBUSY) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "mountpoint or dataset is busy"));
		} else if (errno == EPERM) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Insufficient privileges"));
		} else if (errno == ENOTSUP) {
			char buf[256];
			int spa_version;

			VERIFY(zfs_spa_version(zhp, &spa_version) == 0);
			(void) snprintf(buf, sizeof (buf),
			    dgettext(TEXT_DOMAIN, "Can't mount a version %lld "
			    "file system on a version %d pool. Pool must be"
			    " upgraded to mount this file system."),
			    (u_longlong_t)zfs_prop_get_int(zhp,
			    ZFS_PROP_VERSION), spa_version);
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, buf));
		} else {
			zfs_error_aux(hdl, strerror(errno));
		}
		return (zfs_error_fmt(hdl, EZFS_MOUNTFAILED,
		    dgettext(TEXT_DOMAIN, "cannot mount '%s'"),
		    zhp->zfs_name));
	}

	/* add the mounted entry into our cache */
	libzfs_mnttab_add(hdl, zfs_get_name(zhp), mountpoint,
	    mntopts);
	return (0);
}