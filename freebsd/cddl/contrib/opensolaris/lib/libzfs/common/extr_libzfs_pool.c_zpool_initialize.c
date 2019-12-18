#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  zpool_name; int /*<<< orphan*/ * zpool_hdl; } ;
typedef  TYPE_1__ zpool_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  pool_initialize_func_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int EZFS_ISL2CACHE ; 
 int EZFS_ISSPARE ; 
 int EZFS_NODEVICE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_INITIALIZE_VDEVS ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* fnvlist_lookup_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fnvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvpair_value_int64 (int /*<<< orphan*/ *) ; 
 int lzc_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  xlate_init_err (int /*<<< orphan*/ ) ; 
 int zfs_error (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  zfs_error_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * zpool_find_vdev (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zpool_standard_error (int /*<<< orphan*/ *,int,char*) ; 

int
zpool_initialize(zpool_handle_t *zhp, pool_initialize_func_t cmd_type,
    nvlist_t *vds)
{
	char msg[1024];
	libzfs_handle_t *hdl = zhp->zpool_hdl;

	nvlist_t *errlist;

	/* translate vdev names to guids */
	nvlist_t *vdev_guids = fnvlist_alloc();
	nvlist_t *guids_to_paths = fnvlist_alloc();
	boolean_t spare, cache;
	nvlist_t *tgt;
	nvpair_t *elem;

	for (elem = nvlist_next_nvpair(vds, NULL); elem != NULL;
	    elem = nvlist_next_nvpair(vds, elem)) {
		char *vd_path = nvpair_name(elem);
		tgt = zpool_find_vdev(zhp, vd_path, &spare, &cache, NULL);

		if ((tgt == NULL) || cache || spare) {
			(void) snprintf(msg, sizeof (msg),
			    dgettext(TEXT_DOMAIN, "cannot initialize '%s'"),
			    vd_path);
			int err = (tgt == NULL) ? EZFS_NODEVICE :
			    (spare ? EZFS_ISSPARE : EZFS_ISL2CACHE);
			fnvlist_free(vdev_guids);
			fnvlist_free(guids_to_paths);
			return (zfs_error(hdl, err, msg));
		}

		uint64_t guid = fnvlist_lookup_uint64(tgt, ZPOOL_CONFIG_GUID);
		fnvlist_add_uint64(vdev_guids, vd_path, guid);

		(void) snprintf(msg, sizeof (msg), "%llu", guid);
		fnvlist_add_string(guids_to_paths, msg, vd_path);
	}

	int err = lzc_initialize(zhp->zpool_name, cmd_type, vdev_guids,
	    &errlist);
	fnvlist_free(vdev_guids);

	if (err == 0) {
		fnvlist_free(guids_to_paths);
		return (0);
	}

	nvlist_t *vd_errlist = NULL;
	if (errlist != NULL) {
		vd_errlist = fnvlist_lookup_nvlist(errlist,
		    ZPOOL_INITIALIZE_VDEVS);
	}

	(void) snprintf(msg, sizeof (msg),
	    dgettext(TEXT_DOMAIN, "operation failed"));

	for (elem = nvlist_next_nvpair(vd_errlist, NULL); elem != NULL;
	    elem = nvlist_next_nvpair(vd_errlist, elem)) {
		int64_t vd_error = xlate_init_err(fnvpair_value_int64(elem));
		char *path = fnvlist_lookup_string(guids_to_paths,
		    nvpair_name(elem));
		(void) zfs_error_fmt(hdl, vd_error, "cannot initialize '%s'",
		    path);
	}

	fnvlist_free(guids_to_paths);
	if (vd_errlist != NULL)
		return (-1);

	return (zpool_standard_error(hdl, err, msg));
}