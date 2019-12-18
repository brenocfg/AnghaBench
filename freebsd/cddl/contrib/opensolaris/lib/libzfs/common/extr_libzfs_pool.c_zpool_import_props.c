#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int zlp_rewind; } ;
typedef  TYPE_1__ zpool_load_policy_t ;
typedef  int /*<<< orphan*/  zpool_handle_t ;
struct TYPE_14__ {int zc_nvlist_conf_size; int zc_cookie; int /*<<< orphan*/  zc_guid; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_15__ {int import; int /*<<< orphan*/  create; } ;
typedef  TYPE_3__ prop_flags_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  desc ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int B_TRUE ; 
#define  EEXIST 133 
#define  EINVAL 132 
#define  ENAMETOOLONG 131 
 int ENOMEM ; 
#define  ENOTSUP 130 
#define  ENXIO 129 
#define  EROFS 128 
 int /*<<< orphan*/  EZFS_BADDEV ; 
 int /*<<< orphan*/  EZFS_BADVERSION ; 
 int /*<<< orphan*/  EZFS_INVALCONFIG ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  EZFS_NAMETOOLONG ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_IMPORT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CAN_RDONLY ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_LOAD_INFO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_MISSING_DEVICES ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_NAME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_UNSUP_FEAT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VERSION ; 
 int ZPOOL_DO_REWIND ; 
 int ZPOOL_TRY_REWIND ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_vdev_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  verify (int) ; 
 scalar_t__ zcmd_alloc_dst_nvlist (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ zcmd_expand_dst_nvlist (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_2__*) ; 
 int /*<<< orphan*/  zcmd_read_dst_nvlist (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **) ; 
 scalar_t__ zcmd_write_conf_nvlist (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zcmd_write_src_nvlist (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 int zfs_error_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_explain_recover (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_get_load_policy (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zpool_name_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ zpool_open_silent (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zpool_print_unsup_feat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_rewind_exclaim (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_standard_error (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * zpool_valid_proplist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__,char*) ; 

int
zpool_import_props(libzfs_handle_t *hdl, nvlist_t *config, const char *newname,
    nvlist_t *props, int flags)
{
	zfs_cmd_t zc = { 0 };
	zpool_load_policy_t policy;
	nvlist_t *nv = NULL;
	nvlist_t *nvinfo = NULL;
	nvlist_t *missing = NULL;
	char *thename;
	char *origname;
	int ret;
	int error = 0;
	char errbuf[1024];

	verify(nvlist_lookup_string(config, ZPOOL_CONFIG_POOL_NAME,
	    &origname) == 0);

	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "cannot import pool '%s'"), origname);

	if (newname != NULL) {
		if (!zpool_name_valid(hdl, B_FALSE, newname))
			return (zfs_error_fmt(hdl, EZFS_INVALIDNAME,
			    dgettext(TEXT_DOMAIN, "cannot import '%s'"),
			    newname));
		thename = (char *)newname;
	} else {
		thename = origname;
	}

	if (props != NULL) {
		uint64_t version;
		prop_flags_t flags = { .create = B_FALSE, .import = B_TRUE };

		verify(nvlist_lookup_uint64(config, ZPOOL_CONFIG_VERSION,
		    &version) == 0);

		if ((props = zpool_valid_proplist(hdl, origname,
		    props, version, flags, errbuf)) == NULL)
			return (-1);
		if (zcmd_write_src_nvlist(hdl, &zc, props) != 0) {
			nvlist_free(props);
			return (-1);
		}
		nvlist_free(props);
	}

	(void) strlcpy(zc.zc_name, thename, sizeof (zc.zc_name));

	verify(nvlist_lookup_uint64(config, ZPOOL_CONFIG_POOL_GUID,
	    &zc.zc_guid) == 0);

	if (zcmd_write_conf_nvlist(hdl, &zc, config) != 0) {
		zcmd_free_nvlists(&zc);
		return (-1);
	}
	if (zcmd_alloc_dst_nvlist(hdl, &zc, zc.zc_nvlist_conf_size * 2) != 0) {
		zcmd_free_nvlists(&zc);
		return (-1);
	}

	zc.zc_cookie = flags;
	while ((ret = zfs_ioctl(hdl, ZFS_IOC_POOL_IMPORT, &zc)) != 0 &&
	    errno == ENOMEM) {
		if (zcmd_expand_dst_nvlist(hdl, &zc) != 0) {
			zcmd_free_nvlists(&zc);
			return (-1);
		}
	}
	if (ret != 0)
		error = errno;

	(void) zcmd_read_dst_nvlist(hdl, &zc, &nv);

	zcmd_free_nvlists(&zc);

	zpool_get_load_policy(config, &policy);

	if (error) {
		char desc[1024];

		/*
		 * Dry-run failed, but we print out what success
		 * looks like if we found a best txg
		 */
		if (policy.zlp_rewind & ZPOOL_TRY_REWIND) {
			zpool_rewind_exclaim(hdl, newname ? origname : thename,
			    B_TRUE, nv);
			nvlist_free(nv);
			return (-1);
		}

		if (newname == NULL)
			(void) snprintf(desc, sizeof (desc),
			    dgettext(TEXT_DOMAIN, "cannot import '%s'"),
			    thename);
		else
			(void) snprintf(desc, sizeof (desc),
			    dgettext(TEXT_DOMAIN, "cannot import '%s' as '%s'"),
			    origname, thename);

		switch (error) {
		case ENOTSUP:
			if (nv != NULL && nvlist_lookup_nvlist(nv,
			    ZPOOL_CONFIG_LOAD_INFO, &nvinfo) == 0 &&
			    nvlist_exists(nvinfo, ZPOOL_CONFIG_UNSUP_FEAT)) {
				(void) printf(dgettext(TEXT_DOMAIN, "This "
				    "pool uses the following feature(s) not "
				    "supported by this system:\n"));
				zpool_print_unsup_feat(nv);
				if (nvlist_exists(nvinfo,
				    ZPOOL_CONFIG_CAN_RDONLY)) {
					(void) printf(dgettext(TEXT_DOMAIN,
					    "All unsupported features are only "
					    "required for writing to the pool."
					    "\nThe pool can be imported using "
					    "'-o readonly=on'.\n"));
				}
			}
			/*
			 * Unsupported version.
			 */
			(void) zfs_error(hdl, EZFS_BADVERSION, desc);
			break;

		case EINVAL:
			(void) zfs_error(hdl, EZFS_INVALCONFIG, desc);
			break;

		case EROFS:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "one or more devices is read only"));
			(void) zfs_error(hdl, EZFS_BADDEV, desc);
			break;

		case ENXIO:
			if (nv && nvlist_lookup_nvlist(nv,
			    ZPOOL_CONFIG_LOAD_INFO, &nvinfo) == 0 &&
			    nvlist_lookup_nvlist(nvinfo,
			    ZPOOL_CONFIG_MISSING_DEVICES, &missing) == 0) {
				(void) printf(dgettext(TEXT_DOMAIN,
				    "The devices below are missing or "
				    "corrupted, use '-m' to import the pool "
				    "anyway:\n"));
				print_vdev_tree(hdl, NULL, missing, 2);
				(void) printf("\n");
			}
			(void) zpool_standard_error(hdl, error, desc);
			break;

		case EEXIST:
			(void) zpool_standard_error(hdl, error, desc);
			break;
		case ENAMETOOLONG:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "new name of at least one dataset is longer than "
			    "the maximum allowable length"));
			(void) zfs_error(hdl, EZFS_NAMETOOLONG, desc);
			break;
		default:
			(void) zpool_standard_error(hdl, error, desc);
			zpool_explain_recover(hdl,
			    newname ? origname : thename, -error, nv);
			break;
		}

		nvlist_free(nv);
		ret = -1;
	} else {
		zpool_handle_t *zhp;

		/*
		 * This should never fail, but play it safe anyway.
		 */
		if (zpool_open_silent(hdl, thename, &zhp) != 0)
			ret = -1;
		else if (zhp != NULL)
			zpool_close(zhp);
		if (policy.zlp_rewind &
		    (ZPOOL_DO_REWIND | ZPOOL_TRY_REWIND)) {
			zpool_rewind_exclaim(hdl, newname ? origname : thename,
			    ((policy.zlp_rewind & ZPOOL_TRY_REWIND) != 0), nv);
		}
		nvlist_free(nv);
		return (0);
	}

	return (ret);
}