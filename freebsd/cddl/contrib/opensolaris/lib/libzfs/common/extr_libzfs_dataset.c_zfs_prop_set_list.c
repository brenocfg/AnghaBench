#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int zfs_prop_t ;
struct TYPE_16__ {char* zfs_name; int /*<<< orphan*/  zpool_hdl; int /*<<< orphan*/  zfs_type; int /*<<< orphan*/ * zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_17__ {scalar_t__ zc_nvlist_dst_filled; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  prop_changelist_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ ENOSPC ; 
 int /*<<< orphan*/  EZFS_PERM ; 
 int /*<<< orphan*/  EZFS_ZONED ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 scalar_t__ ZFS_CANMOUNT_OFF ; 
 int /*<<< orphan*/  ZFS_IOC_SET_PROP ; 
 int ZFS_PROP_CANMOUNT ; 
#define  ZFS_PROP_DEVICES 133 
#define  ZFS_PROP_ISCSIOPTIONS 132 
#define  ZFS_PROP_MLSLABEL 131 
 int ZFS_PROP_MOUNTPOINT ; 
#define  ZFS_PROP_NBMAND 130 
 scalar_t__ ZFS_PROP_VOLSIZE ; 
#define  ZFS_PROP_VSCAN 129 
#define  ZFS_PROP_XATTR 128 
 scalar_t__ ZFS_PROP_ZONED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ ** calloc (int,int) ; 
 int /*<<< orphan*/  changelist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * changelist_gather (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ changelist_haszonedchild (int /*<<< orphan*/ *) ; 
 int changelist_postfix (int /*<<< orphan*/ *) ; 
 int changelist_prefix (int /*<<< orphan*/ *) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ fnvpair_value_uint64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_stats (TYPE_1__*) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int zcmd_alloc_dst_nvlist (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_2__*) ; 
 scalar_t__ zcmd_read_dst_nvlist (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **) ; 
 scalar_t__ zcmd_write_src_nvlist (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int zfs_add_synthetic_resv (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 int zfs_fix_auto_resv (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ zfs_is_mounted (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_name_to_prop (char*) ; 
 int /*<<< orphan*/  zfs_prop_get_int (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  zfs_prop_to_name (scalar_t__) ; 
 int /*<<< orphan*/  zfs_setprop_error (int /*<<< orphan*/ *,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  zfs_standard_error (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/ * zfs_valid_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

int
zfs_prop_set_list(zfs_handle_t *zhp, nvlist_t *props)
{
	zfs_cmd_t zc = { 0 };
	int ret = -1;
	prop_changelist_t **cls = NULL;
	int cl_idx;
	char errbuf[1024];
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	nvlist_t *nvl;
	int nvl_len;
	int added_resv = 0;

	(void) snprintf(errbuf, sizeof (errbuf),
	    dgettext(TEXT_DOMAIN, "cannot set property for '%s'"),
	    zhp->zfs_name);

	if ((nvl = zfs_valid_proplist(hdl, zhp->zfs_type, props,
	    zfs_prop_get_int(zhp, ZFS_PROP_ZONED), zhp, zhp->zpool_hdl,
	    errbuf)) == NULL)
		goto error;

	/*
	 * We have to check for any extra properties which need to be added
	 * before computing the length of the nvlist.
	 */
	for (nvpair_t *elem = nvlist_next_nvpair(nvl, NULL);
	    elem != NULL;
	    elem = nvlist_next_nvpair(nvl, elem)) {
		if (zfs_name_to_prop(nvpair_name(elem)) == ZFS_PROP_VOLSIZE &&
		    (added_resv = zfs_add_synthetic_resv(zhp, nvl)) == -1) {
			goto error;
		}
	}

	if (added_resv != 1 &&
	    (added_resv = zfs_fix_auto_resv(zhp, nvl)) == -1) {
		goto error;
	}

	/*
	 * Check how many properties we're setting and allocate an array to
	 * store changelist pointers for postfix().
	 */
	nvl_len = 0;
	for (nvpair_t *elem = nvlist_next_nvpair(nvl, NULL);
	    elem != NULL;
	    elem = nvlist_next_nvpair(nvl, elem))
		nvl_len++;
	if ((cls = calloc(nvl_len, sizeof (prop_changelist_t *))) == NULL)
		goto error;

	cl_idx = 0;
	for (nvpair_t *elem = nvlist_next_nvpair(nvl, NULL);
	    elem != NULL;
	    elem = nvlist_next_nvpair(nvl, elem)) {

		zfs_prop_t prop = zfs_name_to_prop(nvpair_name(elem));

		assert(cl_idx < nvl_len);
		/*
		 * We don't want to unmount & remount the dataset when changing
		 * its canmount property to 'on' or 'noauto'.  We only use
		 * the changelist logic to unmount when setting canmount=off.
		 */
		if (prop != ZFS_PROP_CANMOUNT ||
		    (fnvpair_value_uint64(elem) == ZFS_CANMOUNT_OFF &&
		    zfs_is_mounted(zhp, NULL))) {
			cls[cl_idx] = changelist_gather(zhp, prop, 0, 0);
			if (cls[cl_idx] == NULL)
				goto error;
		}

		if (prop == ZFS_PROP_MOUNTPOINT &&
		    changelist_haszonedchild(cls[cl_idx])) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "child dataset with inherited mountpoint is used "
			    "in a non-global zone"));
			ret = zfs_error(hdl, EZFS_ZONED, errbuf);
			goto error;
		}

		/* We don't support those properties on FreeBSD. */
		switch (prop) {
		case ZFS_PROP_DEVICES:
		case ZFS_PROP_ISCSIOPTIONS:
		case ZFS_PROP_XATTR:
		case ZFS_PROP_VSCAN:
		case ZFS_PROP_NBMAND:
		case ZFS_PROP_MLSLABEL:
			(void) snprintf(errbuf, sizeof (errbuf),
			    "property '%s' not supported on FreeBSD",
			    nvpair_name(elem));
			ret = zfs_error(hdl, EZFS_PERM, errbuf);
			goto error;
		}

		if (cls[cl_idx] != NULL &&
		    (ret = changelist_prefix(cls[cl_idx])) != 0)
			goto error;

		cl_idx++;
	}
	assert(cl_idx == nvl_len);

	/*
	 * Execute the corresponding ioctl() to set this list of properties.
	 */
	(void) strlcpy(zc.zc_name, zhp->zfs_name, sizeof (zc.zc_name));

	if ((ret = zcmd_write_src_nvlist(hdl, &zc, nvl)) != 0 ||
	    (ret = zcmd_alloc_dst_nvlist(hdl, &zc, 0)) != 0)
		goto error;

	ret = zfs_ioctl(hdl, ZFS_IOC_SET_PROP, &zc);

	if (ret != 0) {
		if (zc.zc_nvlist_dst_filled == B_FALSE) {
			(void) zfs_standard_error(hdl, errno, errbuf);
			goto error;
		}

		/* Get the list of unset properties back and report them. */
		nvlist_t *errorprops = NULL;
		if (zcmd_read_dst_nvlist(hdl, &zc, &errorprops) != 0)
			goto error;
		for (nvpair_t *elem = nvlist_next_nvpair(errorprops, NULL);
		    elem != NULL;
		    elem = nvlist_next_nvpair(errorprops, elem)) {
			zfs_prop_t prop = zfs_name_to_prop(nvpair_name(elem));
			zfs_setprop_error(hdl, prop, errno, errbuf);
		}
		nvlist_free(errorprops);

		if (added_resv && errno == ENOSPC) {
			/* clean up the volsize property we tried to set */
			uint64_t old_volsize = zfs_prop_get_int(zhp,
			    ZFS_PROP_VOLSIZE);
			nvlist_free(nvl);
			nvl = NULL;
			zcmd_free_nvlists(&zc);

			if (nvlist_alloc(&nvl, NV_UNIQUE_NAME, 0) != 0)
				goto error;
			if (nvlist_add_uint64(nvl,
			    zfs_prop_to_name(ZFS_PROP_VOLSIZE),
			    old_volsize) != 0)
				goto error;
			if (zcmd_write_src_nvlist(hdl, &zc, nvl) != 0)
				goto error;
			(void) zfs_ioctl(hdl, ZFS_IOC_SET_PROP, &zc);
		}
	} else {
		for (cl_idx = 0; cl_idx < nvl_len; cl_idx++) {
			if (cls[cl_idx] != NULL) {
				int clp_err = changelist_postfix(cls[cl_idx]);
				if (clp_err != 0)
					ret = clp_err;
			}
		}

		/*
		 * Refresh the statistics so the new property value
		 * is reflected.
		 */
		if (ret == 0)
			(void) get_stats(zhp);
	}

error:
	nvlist_free(nvl);
	zcmd_free_nvlists(&zc);
	if (cls != NULL) {
		for (cl_idx = 0; cl_idx < nvl_len; cl_idx++) {
			if (cls[cl_idx] != NULL)
				changelist_free(cls[cl_idx]);
		}
		free(cls);
	}
	return (ret);
}