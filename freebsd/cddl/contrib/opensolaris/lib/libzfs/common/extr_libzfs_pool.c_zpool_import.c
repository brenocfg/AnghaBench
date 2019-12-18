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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EZFS_NOMEM ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IMPORT_NORMAL ; 
 int /*<<< orphan*/  ZPOOL_PROP_ALTROOT ; 
 int /*<<< orphan*/  ZPOOL_PROP_CACHEFILE ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int zfs_error_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int zpool_import_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_prop_to_name (int /*<<< orphan*/ ) ; 

int
zpool_import(libzfs_handle_t *hdl, nvlist_t *config, const char *newname,
    char *altroot)
{
	nvlist_t *props = NULL;
	int ret;

	if (altroot != NULL) {
		if (nvlist_alloc(&props, NV_UNIQUE_NAME, 0) != 0) {
			return (zfs_error_fmt(hdl, EZFS_NOMEM,
			    dgettext(TEXT_DOMAIN, "cannot import '%s'"),
			    newname));
		}

		if (nvlist_add_string(props,
		    zpool_prop_to_name(ZPOOL_PROP_ALTROOT), altroot) != 0 ||
		    nvlist_add_string(props,
		    zpool_prop_to_name(ZPOOL_PROP_CACHEFILE), "none") != 0) {
			nvlist_free(props);
			return (zfs_error_fmt(hdl, EZFS_NOMEM,
			    dgettext(TEXT_DOMAIN, "cannot import '%s'"),
			    newname));
		}
	}

	ret = zpool_import_props(hdl, config, newname, props,
	    ZFS_IMPORT_NORMAL);
	nvlist_free(props);
	return (ret);
}