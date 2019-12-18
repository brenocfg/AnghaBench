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
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EZFS_VDEVNOTSUP ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  VDEV_TYPE_FILE ; 
 int /*<<< orphan*/  VDEV_TYPE_HOLE ; 
 int /*<<< orphan*/  VDEV_TYPE_MISSING ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static boolean_t
supported_dump_vdev_type(libzfs_handle_t *hdl, nvlist_t *config, char *errbuf)
{
	char *type;
	nvlist_t **child;
	uint_t children, c;

	verify(nvlist_lookup_string(config, ZPOOL_CONFIG_TYPE, &type) == 0);
	if (strcmp(type, VDEV_TYPE_FILE) == 0 ||
	    strcmp(type, VDEV_TYPE_HOLE) == 0 ||
	    strcmp(type, VDEV_TYPE_MISSING) == 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "vdev type '%s' is not supported"), type);
		(void) zfs_error(hdl, EZFS_VDEVNOTSUP, errbuf);
		return (B_FALSE);
	}
	if (nvlist_lookup_nvlist_array(config, ZPOOL_CONFIG_CHILDREN,
	    &child, &children) == 0) {
		for (c = 0; c < children; c++) {
			if (!supported_dump_vdev_type(hdl, child[c], errbuf))
				return (B_FALSE);
		}
	}
	return (B_TRUE);
}