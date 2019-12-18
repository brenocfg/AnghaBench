#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int zprop_type_t ;
typedef  scalar_t__ zfs_type_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  data_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DATA_TYPE_STRING ; 
 int /*<<< orphan*/  DATA_TYPE_UINT64 ; 
 int /*<<< orphan*/  EZFS_BADPROP ; 
#define  PROP_TYPE_INDEX 131 
#define  PROP_TYPE_NUMBER 130 
#define  PROP_TYPE_STRING 129 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  ZFS_MAXPROPLEN ; 
 int ZFS_PROP_FILESYSTEM_LIMIT ; 
 int ZFS_PROP_QUOTA ; 
 int ZFS_PROP_REFQUOTA ; 
#define  ZFS_PROP_REFRESERVATION 128 
 int ZFS_PROP_SNAPSHOT_LIMIT ; 
 scalar_t__ ZFS_TYPE_DATASET ; 
 scalar_t__ ZFS_TYPE_POOL ; 
 scalar_t__ ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  no_memory (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,char const*,char*) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_string (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  nvpair_value_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  zfs_nicestrtonum (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int zfs_prop_get_type (int) ; 
 char* zfs_prop_to_name (int) ; 
 int zpool_prop_get_type (int) ; 
 char* zpool_prop_to_name (int) ; 
 int /*<<< orphan*/  zprop_string_to_index (int,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zprop_values (int,scalar_t__) ; 

int
zprop_parse_value(libzfs_handle_t *hdl, nvpair_t *elem, int prop,
    zfs_type_t type, nvlist_t *ret, char **svalp, uint64_t *ivalp,
    const char *errbuf)
{
	data_type_t datatype = nvpair_type(elem);
	zprop_type_t proptype;
	const char *propname;
	char *value;
	boolean_t isnone = B_FALSE;
	boolean_t isauto = B_FALSE;

	if (type == ZFS_TYPE_POOL) {
		proptype = zpool_prop_get_type(prop);
		propname = zpool_prop_to_name(prop);
	} else {
		proptype = zfs_prop_get_type(prop);
		propname = zfs_prop_to_name(prop);
	}

	/*
	 * Convert any properties to the internal DSL value types.
	 */
	*svalp = NULL;
	*ivalp = 0;

	switch (proptype) {
	case PROP_TYPE_STRING:
		if (datatype != DATA_TYPE_STRING) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "'%s' must be a string"), nvpair_name(elem));
			goto error;
		}
		(void) nvpair_value_string(elem, svalp);
		if (strlen(*svalp) >= ZFS_MAXPROPLEN) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "'%s' is too long"), nvpair_name(elem));
			goto error;
		}
		break;

	case PROP_TYPE_NUMBER:
		if (datatype == DATA_TYPE_STRING) {
			(void) nvpair_value_string(elem, &value);
			if (strcmp(value, "none") == 0) {
				isnone = B_TRUE;
			} else if (strcmp(value, "auto") == 0) {
				isauto = B_TRUE;
			} else if (zfs_nicestrtonum(hdl, value, ivalp) != 0) {
				goto error;
			}
		} else if (datatype == DATA_TYPE_UINT64) {
			(void) nvpair_value_uint64(elem, ivalp);
		} else {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "'%s' must be a number"), nvpair_name(elem));
			goto error;
		}

		/*
		 * Quota special: force 'none' and don't allow 0.
		 */
		if ((type & ZFS_TYPE_DATASET) && *ivalp == 0 && !isnone &&
		    (prop == ZFS_PROP_QUOTA || prop == ZFS_PROP_REFQUOTA)) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "use 'none' to disable quota/refquota"));
			goto error;
		}

		/*
		 * Special handling for "*_limit=none". In this case it's not
		 * 0 but UINT64_MAX.
		 */
		if ((type & ZFS_TYPE_DATASET) && isnone &&
		    (prop == ZFS_PROP_FILESYSTEM_LIMIT ||
		    prop == ZFS_PROP_SNAPSHOT_LIMIT)) {
			*ivalp = UINT64_MAX;
		}

		/*
		 * Special handling for setting 'refreservation' to 'auto'.  Use
		 * UINT64_MAX to tell the caller to use zfs_fix_auto_resv().
		 * 'auto' is only allowed on volumes.
		 */
		if (isauto) {
			switch (prop) {
			case ZFS_PROP_REFRESERVATION:
				if ((type & ZFS_TYPE_VOLUME) == 0) {
					zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
					    "'%s=auto' only allowed on "
					    "volumes"), nvpair_name(elem));
					goto error;
				}
				*ivalp = UINT64_MAX;
				break;
			default:
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "'auto' is invalid value for '%s'"),
				    nvpair_name(elem));
				goto error;
			}
		}

		break;

	case PROP_TYPE_INDEX:
		if (datatype != DATA_TYPE_STRING) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "'%s' must be a string"), nvpair_name(elem));
			goto error;
		}

		(void) nvpair_value_string(elem, &value);

		if (zprop_string_to_index(prop, value, ivalp, type) != 0) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "'%s' must be one of '%s'"), propname,
			    zprop_values(prop, type));
			goto error;
		}
		break;

	default:
		abort();
	}

	/*
	 * Add the result to our return set of properties.
	 */
	if (*svalp != NULL) {
		if (nvlist_add_string(ret, propname, *svalp) != 0) {
			(void) no_memory(hdl);
			return (-1);
		}
	} else {
		if (nvlist_add_uint64(ret, propname, *ivalp) != 0) {
			(void) no_memory(hdl);
			return (-1);
		}
	}

	return (0);
error:
	(void) zfs_error(hdl, EZFS_BADPROP, errbuf);
	return (-1);
}