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
typedef  scalar_t__ zfs_prop_t ;
struct TYPE_8__ {char const* zfs_name; int /*<<< orphan*/ * zfs_hdl; int /*<<< orphan*/  zfs_type; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  zc_value; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  prop_changelist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  EZFS_BADPROP ; 
 int /*<<< orphan*/  EZFS_PROPNONINHERIT ; 
 int /*<<< orphan*/  EZFS_PROPREADONLY ; 
 int /*<<< orphan*/  EZFS_PROPTYPE ; 
 int /*<<< orphan*/  EZFS_ZONED ; 
 scalar_t__ GLOBAL_ZONEID ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_INHERIT_PROP ; 
 scalar_t__ ZFS_PROP_MOUNTPOINT ; 
 int /*<<< orphan*/  ZFS_PROP_ZONED ; 
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  changelist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * changelist_gather (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ changelist_haszonedchild (int /*<<< orphan*/ *) ; 
 int changelist_postfix (int /*<<< orphan*/ *) ; 
 int changelist_prefix (int /*<<< orphan*/ *) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  get_stats (TYPE_1__*) ; 
 scalar_t__ getzoneid () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 int zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ zfs_name_to_prop (char const*) ; 
 scalar_t__ zfs_prop_get_int (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_inheritable (scalar_t__) ; 
 scalar_t__ zfs_prop_readonly (scalar_t__) ; 
 char* zfs_prop_to_name (scalar_t__) ; 
 int /*<<< orphan*/  zfs_prop_user (char const*) ; 
 int /*<<< orphan*/  zfs_prop_valid_for_type (scalar_t__,int /*<<< orphan*/ ) ; 
 int zfs_standard_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

int
zfs_prop_inherit(zfs_handle_t *zhp, const char *propname, boolean_t received)
{
	zfs_cmd_t zc = { 0 };
	int ret;
	prop_changelist_t *cl;
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	char errbuf[1024];
	zfs_prop_t prop;

	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "cannot inherit %s for '%s'"), propname, zhp->zfs_name);

	zc.zc_cookie = received;
	if ((prop = zfs_name_to_prop(propname)) == ZPROP_INVAL) {
		/*
		 * For user properties, the amount of work we have to do is very
		 * small, so just do it here.
		 */
		if (!zfs_prop_user(propname)) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "invalid property"));
			return (zfs_error(hdl, EZFS_BADPROP, errbuf));
		}

		(void) strlcpy(zc.zc_name, zhp->zfs_name, sizeof (zc.zc_name));
		(void) strlcpy(zc.zc_value, propname, sizeof (zc.zc_value));

		if (zfs_ioctl(zhp->zfs_hdl, ZFS_IOC_INHERIT_PROP, &zc) != 0)
			return (zfs_standard_error(hdl, errno, errbuf));

		return (0);
	}

	/*
	 * Verify that this property is inheritable.
	 */
	if (zfs_prop_readonly(prop))
		return (zfs_error(hdl, EZFS_PROPREADONLY, errbuf));

	if (!zfs_prop_inheritable(prop) && !received)
		return (zfs_error(hdl, EZFS_PROPNONINHERIT, errbuf));

	/*
	 * Check to see if the value applies to this type
	 */
	if (!zfs_prop_valid_for_type(prop, zhp->zfs_type))
		return (zfs_error(hdl, EZFS_PROPTYPE, errbuf));

	/*
	 * Normalize the name, to get rid of shorthand abbreviations.
	 */
	propname = zfs_prop_to_name(prop);
	(void) strlcpy(zc.zc_name, zhp->zfs_name, sizeof (zc.zc_name));
	(void) strlcpy(zc.zc_value, propname, sizeof (zc.zc_value));

	if (prop == ZFS_PROP_MOUNTPOINT && getzoneid() == GLOBAL_ZONEID &&
	    zfs_prop_get_int(zhp, ZFS_PROP_ZONED)) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "dataset is used in a non-global zone"));
		return (zfs_error(hdl, EZFS_ZONED, errbuf));
	}

	/*
	 * Determine datasets which will be affected by this change, if any.
	 */
	if ((cl = changelist_gather(zhp, prop, 0, 0)) == NULL)
		return (-1);

	if (prop == ZFS_PROP_MOUNTPOINT && changelist_haszonedchild(cl)) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "child dataset with inherited mountpoint is used "
		    "in a non-global zone"));
		ret = zfs_error(hdl, EZFS_ZONED, errbuf);
		goto error;
	}

	if ((ret = changelist_prefix(cl)) != 0)
		goto error;

	if ((ret = zfs_ioctl(zhp->zfs_hdl, ZFS_IOC_INHERIT_PROP, &zc)) != 0) {
		return (zfs_standard_error(hdl, errno, errbuf));
	} else {

		if ((ret = changelist_postfix(cl)) != 0)
			goto error;

		/*
		 * Refresh the statistics so the new property is reflected.
		 */
		(void) get_stats(zhp);
	}

error:
	changelist_free(cl);
	return (ret);
}