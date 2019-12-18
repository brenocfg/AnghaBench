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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  scalar_t__ zfs_type_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  pool_path ;
typedef  int /*<<< orphan*/  parent ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  enum lzc_dataset_type { ____Placeholder_lzc_dataset_type } lzc_dataset_type ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
#define  EINVAL 132 
#define  ENOENT 131 
#define  ENOTSUP 130 
#define  EOVERFLOW 129 
#define  ERANGE 128 
 int /*<<< orphan*/  EZFS_BADPROP ; 
 int /*<<< orphan*/  EZFS_BADTYPE ; 
 int /*<<< orphan*/  EZFS_BADVERSION ; 
 int /*<<< orphan*/  EZFS_EXISTS ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  EZFS_NOENT ; 
 int /*<<< orphan*/  EZFS_VOLTOOBIG ; 
 int LZC_DATSET_TYPE_ZFS ; 
 int LZC_DATSET_TYPE_ZVOL ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_VOLBLOCKSIZE ; 
 int /*<<< orphan*/  ZFS_PROP_VOLSIZE ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 scalar_t__ ZFS_TYPE_VOLUME ; 
 scalar_t__ check_parents (int /*<<< orphan*/ *,char const*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dataset_nestcheck (char const*) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int lzc_create (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  parent_name (char const*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 scalar_t__ zfs_dataset_exists (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 int zfs_prop_default_numeric (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 
 int zfs_standard_error (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * zfs_valid_proplist (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zfs_validate_name (int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open (int /*<<< orphan*/ *,char*) ; 

int
zfs_create(libzfs_handle_t *hdl, const char *path, zfs_type_t type,
    nvlist_t *props)
{
	int ret;
	uint64_t size = 0;
	uint64_t blocksize = zfs_prop_default_numeric(ZFS_PROP_VOLBLOCKSIZE);
	char errbuf[1024];
	uint64_t zoned;
	enum lzc_dataset_type ost;
	zpool_handle_t *zpool_handle;

	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "cannot create '%s'"), path);

	/* validate the path, taking care to note the extended error message */
	if (!zfs_validate_name(hdl, path, type, B_TRUE))
		return (zfs_error(hdl, EZFS_INVALIDNAME, errbuf));

	if (dataset_nestcheck(path) != 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "maximum name nesting depth exceeded"));
		return (zfs_error(hdl, EZFS_INVALIDNAME, errbuf));
	}

	/* validate parents exist */
	if (check_parents(hdl, path, &zoned, B_FALSE, NULL) != 0)
		return (-1);

	/*
	 * The failure modes when creating a dataset of a different type over
	 * one that already exists is a little strange.  In particular, if you
	 * try to create a dataset on top of an existing dataset, the ioctl()
	 * will return ENOENT, not EEXIST.  To prevent this from happening, we
	 * first try to see if the dataset exists.
	 */
	if (zfs_dataset_exists(hdl, path, ZFS_TYPE_DATASET)) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "dataset already exists"));
		return (zfs_error(hdl, EZFS_EXISTS, errbuf));
	}

	if (type == ZFS_TYPE_VOLUME)
		ost = LZC_DATSET_TYPE_ZVOL;
	else
		ost = LZC_DATSET_TYPE_ZFS;

	/* open zpool handle for prop validation */
	char pool_path[ZFS_MAX_DATASET_NAME_LEN];
	(void) strlcpy(pool_path, path, sizeof (pool_path));

	/* truncate pool_path at first slash */
	char *p = strchr(pool_path, '/');
	if (p != NULL)
		*p = '\0';

	if ((zpool_handle = zpool_open(hdl, pool_path)) == NULL)
		return (-1);

	if (props && (props = zfs_valid_proplist(hdl, type, props,
	    zoned, NULL, zpool_handle, errbuf)) == 0) {
		zpool_close(zpool_handle);
		return (-1);
	}
	zpool_close(zpool_handle);

	if (type == ZFS_TYPE_VOLUME) {
		/*
		 * If we are creating a volume, the size and block size must
		 * satisfy a few restraints.  First, the blocksize must be a
		 * valid block size between SPA_{MIN,MAX}BLOCKSIZE.  Second, the
		 * volsize must be a multiple of the block size, and cannot be
		 * zero.
		 */
		if (props == NULL || nvlist_lookup_uint64(props,
		    zfs_prop_to_name(ZFS_PROP_VOLSIZE), &size) != 0) {
			nvlist_free(props);
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "missing volume size"));
			return (zfs_error(hdl, EZFS_BADPROP, errbuf));
		}

		if ((ret = nvlist_lookup_uint64(props,
		    zfs_prop_to_name(ZFS_PROP_VOLBLOCKSIZE),
		    &blocksize)) != 0) {
			if (ret == ENOENT) {
				blocksize = zfs_prop_default_numeric(
				    ZFS_PROP_VOLBLOCKSIZE);
			} else {
				nvlist_free(props);
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "missing volume block size"));
				return (zfs_error(hdl, EZFS_BADPROP, errbuf));
			}
		}

		if (size == 0) {
			nvlist_free(props);
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "volume size cannot be zero"));
			return (zfs_error(hdl, EZFS_BADPROP, errbuf));
		}

		if (size % blocksize != 0) {
			nvlist_free(props);
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "volume size must be a multiple of volume block "
			    "size"));
			return (zfs_error(hdl, EZFS_BADPROP, errbuf));
		}
	}

	/* create the dataset */
	ret = lzc_create(path, ost, props);
	nvlist_free(props);

	/* check for failure */
	if (ret != 0) {
		char parent[ZFS_MAX_DATASET_NAME_LEN];
		(void) parent_name(path, parent, sizeof (parent));

		switch (errno) {
		case ENOENT:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "no such parent '%s'"), parent);
			return (zfs_error(hdl, EZFS_NOENT, errbuf));

		case EINVAL:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "parent '%s' is not a filesystem"), parent);
			return (zfs_error(hdl, EZFS_BADTYPE, errbuf));

		case ENOTSUP:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "pool must be upgraded to set this "
			    "property or value"));
			return (zfs_error(hdl, EZFS_BADVERSION, errbuf));
		case ERANGE:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "invalid property value(s) specified"));
			return (zfs_error(hdl, EZFS_BADPROP, errbuf));
#ifdef _ILP32
		case EOVERFLOW:
			/*
			 * This platform can't address a volume this big.
			 */
			if (type == ZFS_TYPE_VOLUME)
				return (zfs_error(hdl, EZFS_VOLTOOBIG,
				    errbuf));
#endif
			/* FALLTHROUGH */
		default:
			return (zfs_standard_error(hdl, errno, errbuf));
		}
	}

	return (0);
}