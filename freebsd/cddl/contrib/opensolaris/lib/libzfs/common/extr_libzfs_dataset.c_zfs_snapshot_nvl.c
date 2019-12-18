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
typedef  int /*<<< orphan*/  pool ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
#define  EXDEV 128 
 int /*<<< orphan*/  EZFS_EXISTS ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int fnvpair_value_int32 (int /*<<< orphan*/ *) ; 
 int lzc_snapshot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char const* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zfs_standard_error (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * zfs_valid_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zfs_validate_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_open (int /*<<< orphan*/ *,char*) ; 

int
zfs_snapshot_nvl(libzfs_handle_t *hdl, nvlist_t *snaps, nvlist_t *props)
{
	int ret;
	char errbuf[1024];
	nvpair_t *elem;
	nvlist_t *errors;

	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "cannot create snapshots "));

	elem = NULL;
	while ((elem = nvlist_next_nvpair(snaps, elem)) != NULL) {
		const char *snapname = nvpair_name(elem);

		/* validate the target name */
		if (!zfs_validate_name(hdl, snapname, ZFS_TYPE_SNAPSHOT,
		    B_TRUE)) {
			(void) snprintf(errbuf, sizeof (errbuf),
			    dgettext(TEXT_DOMAIN,
			    "cannot create snapshot '%s'"), snapname);
			return (zfs_error(hdl, EZFS_INVALIDNAME, errbuf));
		}
	}

	/*
	 * get pool handle for prop validation. assumes all snaps are in the
	 * same pool, as does lzc_snapshot (below).
	 */
	char pool[ZFS_MAX_DATASET_NAME_LEN];
	elem = nvlist_next_nvpair(snaps, NULL);
	(void) strlcpy(pool, nvpair_name(elem), sizeof (pool));
	pool[strcspn(pool, "/@")] = '\0';
	zpool_handle_t *zpool_hdl = zpool_open(hdl, pool);

	if (props != NULL &&
	    (props = zfs_valid_proplist(hdl, ZFS_TYPE_SNAPSHOT,
	    props, B_FALSE, NULL, zpool_hdl, errbuf)) == NULL) {
		zpool_close(zpool_hdl);
		return (-1);
	}
	zpool_close(zpool_hdl);

	ret = lzc_snapshot(snaps, props, &errors);

	if (ret != 0) {
		boolean_t printed = B_FALSE;
		for (elem = nvlist_next_nvpair(errors, NULL);
		    elem != NULL;
		    elem = nvlist_next_nvpair(errors, elem)) {
			(void) snprintf(errbuf, sizeof (errbuf),
			    dgettext(TEXT_DOMAIN,
			    "cannot create snapshot '%s'"), nvpair_name(elem));
			(void) zfs_standard_error(hdl,
			    fnvpair_value_int32(elem), errbuf);
			printed = B_TRUE;
		}
		if (!printed) {
			switch (ret) {
			case EXDEV:
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "multiple snapshots of same "
				    "fs not allowed"));
				(void) zfs_error(hdl, EZFS_EXISTS, errbuf);

				break;
			default:
				(void) zfs_standard_error(hdl, ret, errbuf);
			}
		}
	}

	nvlist_free(props);
	nvlist_free(errors);
	return (ret);
}