#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char* zfs_name; int /*<<< orphan*/ * zfs_hdl; int /*<<< orphan*/  zfs_type; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_15__ {char* zc_name; char* zc_value; int zc_cookie; int /*<<< orphan*/  zc_objset_type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
struct TYPE_16__ {scalar_t__ recurse; scalar_t__ nounmount; scalar_t__ forceunmount; } ;
typedef  TYPE_3__ renameflags_t ;
typedef  int /*<<< orphan*/  property ;
typedef  int /*<<< orphan*/  prop_changelist_t ;
typedef  int /*<<< orphan*/  parent ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  CL_GATHER_DONT_UNMOUNT ; 
 int /*<<< orphan*/  DMU_OST_ZFS ; 
 int /*<<< orphan*/  DMU_OST_ZVOL ; 
 scalar_t__ EEXIST ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  EZFS_BADTYPE ; 
 int /*<<< orphan*/  EZFS_CROSSTARGET ; 
 int /*<<< orphan*/  EZFS_EXISTS ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  EZFS_ZONED ; 
 scalar_t__ GLOBAL_ZONEID ; 
 int /*<<< orphan*/  MS_FORCE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_RENAME ; 
 scalar_t__ ZFS_IS_VOLUME (TYPE_1__*) ; 
 int ZFS_MAXPROPLEN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int /*<<< orphan*/  ZFS_PROP_NAME ; 
 int /*<<< orphan*/  ZFS_PROP_ZONED ; 
 int /*<<< orphan*/  ZFS_TYPE_BOOKMARK ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  changelist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * changelist_gather (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ changelist_haszonedchild (int /*<<< orphan*/ *) ; 
 int changelist_postfix (int /*<<< orphan*/ *) ; 
 int changelist_prefix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  changelist_rename (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ check_parents (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getzoneid () ; 
 scalar_t__ is_descendant (char*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* strchr (char const*,char const) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  verify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  zfs_get_name (TYPE_1__*) ; 
 int zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* zfs_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get (TYPE_1__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_standard_error (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 char* zfs_strdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  zfs_validate_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,scalar_t__) ; 

int
zfs_rename(zfs_handle_t *zhp, const char *source, const char *target,
    renameflags_t flags)
{
	int ret = 0;
	zfs_cmd_t zc = { 0 };
	char *delim;
	prop_changelist_t *cl = NULL;
	zfs_handle_t *zhrp = NULL;
	char *parentname = NULL;
	char parent[ZFS_MAX_DATASET_NAME_LEN];
	char property[ZFS_MAXPROPLEN];
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	char errbuf[1024];

	/* if we have the same exact name, just return success */
	if (strcmp(zhp->zfs_name, target) == 0)
		return (0);

	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "cannot rename to '%s'"), target);

	if (source != NULL) {
		/*
		 * This is recursive snapshots rename, put snapshot name
		 * (that might not exist) into zfs_name.
		 */
		assert(flags.recurse);

		(void) strlcat(zhp->zfs_name, "@", sizeof(zhp->zfs_name));
		(void) strlcat(zhp->zfs_name, source, sizeof(zhp->zfs_name));
		zhp->zfs_type = ZFS_TYPE_SNAPSHOT;
	}

	/* make sure source name is valid */
	if (!zfs_validate_name(hdl, zhp->zfs_name, zhp->zfs_type, B_TRUE))
		return (zfs_error(hdl, EZFS_INVALIDNAME, errbuf));

	/*
	 * Make sure the target name is valid
	 */
	if (zhp->zfs_type == ZFS_TYPE_SNAPSHOT ||
	    zhp->zfs_type == ZFS_TYPE_BOOKMARK) {
		const char sep = zhp->zfs_type == ZFS_TYPE_SNAPSHOT ? '@' : '#';

		if ((strchr(target, sep) == NULL) || *target == sep) {
			/*
			 * Snapshot target name is abbreviated,
			 * reconstruct full dataset name
			 */
			(void) strlcpy(parent, zhp->zfs_name, sizeof (parent));
			delim = strchr(parent, sep);
			if (strchr(target, sep) == NULL)
				*(++delim) = '\0';
			else
				*delim = '\0';
			(void) strlcat(parent, target, sizeof (parent));
			target = parent;
		} else {
			/*
			 * Make sure we're renaming within the same dataset.
			 */
			delim = strchr(target, sep);
			if (strncmp(zhp->zfs_name, target, delim - target)
			    != 0 || zhp->zfs_name[delim - target] != sep) {
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "%s must be part of same dataset"),
				    zhp->zfs_type == ZFS_TYPE_SNAPSHOT ?
				    "snapshots" : "bookmarks");
				return (zfs_error(hdl, EZFS_CROSSTARGET,
				    errbuf));
			}
		}

		if (!zfs_validate_name(hdl, target, zhp->zfs_type, B_TRUE))
			return (zfs_error(hdl, EZFS_INVALIDNAME, errbuf));
	} else {
		if (flags.recurse) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "recursive rename must be a snapshot"));
			return (zfs_error(hdl, EZFS_BADTYPE, errbuf));
		}

		if (!zfs_validate_name(hdl, target, zhp->zfs_type, B_TRUE))
			return (zfs_error(hdl, EZFS_INVALIDNAME, errbuf));

		/* validate parents */
		if (check_parents(hdl, target, NULL, B_FALSE, NULL) != 0)
			return (-1);

		/* make sure we're in the same pool */
		verify((delim = strchr(target, '/')) != NULL);
		if (strncmp(zhp->zfs_name, target, delim - target) != 0 ||
		    zhp->zfs_name[delim - target] != '/') {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "datasets must be within same pool"));
			return (zfs_error(hdl, EZFS_CROSSTARGET, errbuf));
		}

		/* new name cannot be a child of the current dataset name */
		if (is_descendant(zhp->zfs_name, target)) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "New dataset name cannot be a descendant of "
			    "current dataset name"));
			return (zfs_error(hdl, EZFS_INVALIDNAME, errbuf));
		}
	}

	(void) snprintf(errbuf, sizeof (errbuf),
	    dgettext(TEXT_DOMAIN, "cannot rename '%s'"), zhp->zfs_name);

	if (getzoneid() == GLOBAL_ZONEID &&
	    zfs_prop_get_int(zhp, ZFS_PROP_ZONED)) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "dataset is used in a non-global zone"));
		return (zfs_error(hdl, EZFS_ZONED, errbuf));
	}

	/*
	 * Avoid unmounting file systems with mountpoint property set to
	 * 'legacy' or 'none' even if -u option is not given.
	 */
	if (zhp->zfs_type == ZFS_TYPE_FILESYSTEM &&
	    !flags.recurse && !flags.nounmount &&
	    zfs_prop_get(zhp, ZFS_PROP_MOUNTPOINT, property,
	    sizeof (property), NULL, NULL, 0, B_FALSE) == 0 &&
	    (strcmp(property, "legacy") == 0 ||
	     strcmp(property, "none") == 0)) {
		flags.nounmount = B_TRUE;
	}
	if (flags.recurse) {
		parentname = zfs_strdup(zhp->zfs_hdl, zhp->zfs_name);
		if (parentname == NULL) {
			ret = -1;
			goto error;
		}
		delim = strchr(parentname, '@');
		*delim = '\0';
		zhrp = zfs_open(zhp->zfs_hdl, parentname, ZFS_TYPE_DATASET);
		if (zhrp == NULL) {
			ret = -1;
			goto error;
		}
	} else if (zhp->zfs_type != ZFS_TYPE_SNAPSHOT &&
	    zhp->zfs_type != ZFS_TYPE_BOOKMARK) {
		if ((cl = changelist_gather(zhp, ZFS_PROP_NAME,
		    flags.nounmount ? CL_GATHER_DONT_UNMOUNT : 0,
		    flags.forceunmount ? MS_FORCE : 0)) == NULL) {
			return (-1);
		}

		if (changelist_haszonedchild(cl)) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "child dataset with inherited mountpoint is used "
			    "in a non-global zone"));
			(void) zfs_error(hdl, EZFS_ZONED, errbuf);
			ret = -1;
			goto error;
		}

		if ((ret = changelist_prefix(cl)) != 0)
			goto error;
	}

	if (ZFS_IS_VOLUME(zhp))
		zc.zc_objset_type = DMU_OST_ZVOL;
	else
		zc.zc_objset_type = DMU_OST_ZFS;

	(void) strlcpy(zc.zc_name, zhp->zfs_name, sizeof (zc.zc_name));
	(void) strlcpy(zc.zc_value, target, sizeof (zc.zc_value));

	zc.zc_cookie = flags.recurse ? 1 : 0;
	if (flags.nounmount)
		zc.zc_cookie |= 2;

	if ((ret = zfs_ioctl(zhp->zfs_hdl, ZFS_IOC_RENAME, &zc)) != 0) {
		/*
		 * if it was recursive, the one that actually failed will
		 * be in zc.zc_name
		 */
		(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
		    "cannot rename '%s'"), zc.zc_name);

		if (flags.recurse && errno == EEXIST) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "a child dataset already has a snapshot "
			    "with the new name"));
			(void) zfs_error(hdl, EZFS_EXISTS, errbuf);
		} else if (errno == EINVAL) {
			(void) zfs_error(hdl, EZFS_INVALIDNAME, errbuf);
		} else {
			(void) zfs_standard_error(zhp->zfs_hdl, errno, errbuf);
		}

		/*
		 * On failure, we still want to remount any filesystems that
		 * were previously mounted, so we don't alter the system state.
		 */
		if (cl != NULL)
			(void) changelist_postfix(cl);
	} else {
		if (cl != NULL) {
			changelist_rename(cl, zfs_get_name(zhp), target);
			ret = changelist_postfix(cl);
		}
	}

error:
	if (parentname != NULL) {
		free(parentname);
	}
	if (zhrp != NULL) {
		zfs_close(zhrp);
	}
	if (cl != NULL) {
		changelist_free(cl);
	}
	return (ret);
}