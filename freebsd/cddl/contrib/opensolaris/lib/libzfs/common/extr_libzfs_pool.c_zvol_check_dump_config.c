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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EZFS_INVALCONFIG ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  EZFS_NAMETOOLONG ; 
 int /*<<< orphan*/  EZFS_OPENFAILED ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int /*<<< orphan*/  ZVOL_FULL_DEV_DIR ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  libzfs_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libzfs_init () ; 
 int /*<<< orphan*/  libzfs_print_on_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  supported_dump_vdev_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open (int /*<<< orphan*/ *,char*) ; 

int
zvol_check_dump_config(char *arg)
{
	zpool_handle_t *zhp = NULL;
	nvlist_t *config, *nvroot;
	char *p, *volname;
	nvlist_t **top;
	uint_t toplevels;
	libzfs_handle_t *hdl;
	char errbuf[1024];
	char poolname[ZFS_MAX_DATASET_NAME_LEN];
	int pathlen = strlen(ZVOL_FULL_DEV_DIR);
	int ret = 1;

	if (strncmp(arg, ZVOL_FULL_DEV_DIR, pathlen)) {
		return (-1);
	}

	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "dump is not supported on device '%s'"), arg);

	if ((hdl = libzfs_init()) == NULL)
		return (1);
	libzfs_print_on_error(hdl, B_TRUE);

	volname = arg + pathlen;

	/* check the configuration of the pool */
	if ((p = strchr(volname, '/')) == NULL) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "malformed dataset name"));
		(void) zfs_error(hdl, EZFS_INVALIDNAME, errbuf);
		return (1);
	} else if (p - volname >= ZFS_MAX_DATASET_NAME_LEN) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "dataset name is too long"));
		(void) zfs_error(hdl, EZFS_NAMETOOLONG, errbuf);
		return (1);
	} else {
		(void) strncpy(poolname, volname, p - volname);
		poolname[p - volname] = '\0';
	}

	if ((zhp = zpool_open(hdl, poolname)) == NULL) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "could not open pool '%s'"), poolname);
		(void) zfs_error(hdl, EZFS_OPENFAILED, errbuf);
		goto out;
	}
	config = zpool_get_config(zhp, NULL);
	if (nvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE,
	    &nvroot) != 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "could not obtain vdev configuration for  '%s'"), poolname);
		(void) zfs_error(hdl, EZFS_INVALCONFIG, errbuf);
		goto out;
	}

	verify(nvlist_lookup_nvlist_array(nvroot, ZPOOL_CONFIG_CHILDREN,
	    &top, &toplevels) == 0);

	if (!supported_dump_vdev_type(hdl, top[0], errbuf)) {
		goto out;
	}
	ret = 0;

out:
	if (zhp)
		zpool_close(zhp);
	libzfs_fini(hdl);
	return (ret);
}