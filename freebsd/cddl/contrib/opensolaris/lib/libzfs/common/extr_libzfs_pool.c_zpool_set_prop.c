#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  zpool_hdl; int /*<<< orphan*/  zpool_name; } ;
typedef  TYPE_1__ zpool_handle_t ;
struct TYPE_12__ {int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_13__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ prop_flags_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_SET_PROPS ; 
 int /*<<< orphan*/  ZPOOL_PROP_VERSION ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 int no_memory (int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_2__*) ; 
 scalar_t__ zcmd_write_src_nvlist (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int zfs_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zpool_get_prop_int (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_props_refresh (TYPE_1__*) ; 
 int /*<<< orphan*/  zpool_standard_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * zpool_valid_proplist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__,char*) ; 

int
zpool_set_prop(zpool_handle_t *zhp, const char *propname, const char *propval)
{
	zfs_cmd_t zc = { 0 };
	int ret = -1;
	char errbuf[1024];
	nvlist_t *nvl = NULL;
	nvlist_t *realprops;
	uint64_t version;
	prop_flags_t flags = { 0 };

	(void) snprintf(errbuf, sizeof (errbuf),
	    dgettext(TEXT_DOMAIN, "cannot set property for '%s'"),
	    zhp->zpool_name);

	if (nvlist_alloc(&nvl, NV_UNIQUE_NAME, 0) != 0)
		return (no_memory(zhp->zpool_hdl));

	if (nvlist_add_string(nvl, propname, propval) != 0) {
		nvlist_free(nvl);
		return (no_memory(zhp->zpool_hdl));
	}

	version = zpool_get_prop_int(zhp, ZPOOL_PROP_VERSION, NULL);
	if ((realprops = zpool_valid_proplist(zhp->zpool_hdl,
	    zhp->zpool_name, nvl, version, flags, errbuf)) == NULL) {
		nvlist_free(nvl);
		return (-1);
	}

	nvlist_free(nvl);
	nvl = realprops;

	/*
	 * Execute the corresponding ioctl() to set this property.
	 */
	(void) strlcpy(zc.zc_name, zhp->zpool_name, sizeof (zc.zc_name));

	if (zcmd_write_src_nvlist(zhp->zpool_hdl, &zc, nvl) != 0) {
		nvlist_free(nvl);
		return (-1);
	}

	ret = zfs_ioctl(zhp->zpool_hdl, ZFS_IOC_POOL_SET_PROPS, &zc);

	zcmd_free_nvlists(&zc);
	nvlist_free(nvl);

	if (ret)
		(void) zpool_standard_error(zhp->zpool_hdl, errno, errbuf);
	else
		(void) zpool_props_refresh(zhp);

	return (ret);
}