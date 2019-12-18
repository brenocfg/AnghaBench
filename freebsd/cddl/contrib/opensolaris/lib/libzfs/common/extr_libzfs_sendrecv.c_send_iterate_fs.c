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
struct TYPE_13__ {scalar_t__ dds_creation_txg; scalar_t__ dds_guid; scalar_t__* dds_origin; } ;
struct TYPE_14__ {TYPE_1__ zfs_dmustats; int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_name; } ;
typedef  TYPE_2__ zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_15__ {scalar_t__ parent_fromsnap_guid; scalar_t__ fromsnap_txg; scalar_t__ tosnap_txg; scalar_t__ recursive; int /*<<< orphan*/ * fss; int /*<<< orphan*/ * snapprops; int /*<<< orphan*/ * parent_snaps; int /*<<< orphan*/  replicate; int /*<<< orphan*/ * tosnap; int /*<<< orphan*/  fsname; scalar_t__ verbose; int /*<<< orphan*/ * fromsnap; } ;
typedef  TYPE_3__ send_data_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  longlong_t ;
typedef  int /*<<< orphan*/  guidstring ;

/* Variables and functions */
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 scalar_t__ get_snap_txg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_iterate_prop (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_iterate_snap ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zfs_close (TYPE_2__*) ; 
 int zfs_iter_filesystems (TYPE_2__*,int (*) (TYPE_2__*,void*),TYPE_3__*) ; 
 int /*<<< orphan*/  zfs_iter_snapshots_sorted (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,scalar_t__) ; 
 TYPE_2__* zfs_open (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
send_iterate_fs(zfs_handle_t *zhp, void *arg)
{
	send_data_t *sd = arg;
	nvlist_t *nvfs, *nv;
	int rv = 0;
	uint64_t min_txg = 0, max_txg = 0;
	uint64_t parent_fromsnap_guid_save = sd->parent_fromsnap_guid;
	uint64_t fromsnap_txg_save = sd->fromsnap_txg;
	uint64_t tosnap_txg_save = sd->tosnap_txg;
	uint64_t txg = zhp->zfs_dmustats.dds_creation_txg;
	uint64_t guid = zhp->zfs_dmustats.dds_guid;
	uint64_t fromsnap_txg, tosnap_txg;
	char guidstring[64];

	fromsnap_txg = get_snap_txg(zhp->zfs_hdl, zhp->zfs_name, sd->fromsnap);
	if (fromsnap_txg != 0)
		sd->fromsnap_txg = fromsnap_txg;

	tosnap_txg = get_snap_txg(zhp->zfs_hdl, zhp->zfs_name, sd->tosnap);
	if (tosnap_txg != 0)
		sd->tosnap_txg = tosnap_txg;

	/*
	 * on the send side, if the current dataset does not have tosnap,
	 * perform two additional checks:
	 *
	 * - skip sending the current dataset if it was created later than
	 *   the parent tosnap
	 * - return error if the current dataset was created earlier than
	 *   the parent tosnap
	 */
	if (sd->tosnap != NULL && tosnap_txg == 0) {
		if (sd->tosnap_txg != 0 && txg > sd->tosnap_txg) {
			if (sd->verbose) {
				(void) fprintf(stderr, dgettext(TEXT_DOMAIN,
				    "skipping dataset %s: snapshot %s does "
				    "not exist\n"), zhp->zfs_name, sd->tosnap);
			}
		} else {
			(void) fprintf(stderr, dgettext(TEXT_DOMAIN,
			    "cannot send %s@%s%s: snapshot %s@%s does not "
			    "exist\n"), sd->fsname, sd->tosnap, sd->recursive ?
			    dgettext(TEXT_DOMAIN, " recursively") : "",
			    zhp->zfs_name, sd->tosnap);
			rv = -1;
		}
		goto out;
	}

	nvfs = fnvlist_alloc();
	fnvlist_add_string(nvfs, "name", zhp->zfs_name);
	fnvlist_add_uint64(nvfs, "parentfromsnap",
	    sd->parent_fromsnap_guid);

	if (zhp->zfs_dmustats.dds_origin[0]) {
		zfs_handle_t *origin = zfs_open(zhp->zfs_hdl,
		    zhp->zfs_dmustats.dds_origin, ZFS_TYPE_SNAPSHOT);
		if (origin == NULL) {
			rv = -1;
			goto out;
		}
		VERIFY(0 == nvlist_add_uint64(nvfs, "origin",
		    origin->zfs_dmustats.dds_guid));
	}

	/* iterate over props */
	VERIFY(0 == nvlist_alloc(&nv, NV_UNIQUE_NAME, 0));
	send_iterate_prop(zhp, nv);
	VERIFY(0 == nvlist_add_nvlist(nvfs, "props", nv));
	nvlist_free(nv);

	/* iterate over snaps, and set sd->parent_fromsnap_guid */
	if (!sd->replicate && fromsnap_txg != 0)
		min_txg = fromsnap_txg;
	if (!sd->replicate && tosnap_txg != 0)
		max_txg = tosnap_txg;
	sd->parent_fromsnap_guid = 0;
	VERIFY(0 == nvlist_alloc(&sd->parent_snaps, NV_UNIQUE_NAME, 0));
	VERIFY(0 == nvlist_alloc(&sd->snapprops, NV_UNIQUE_NAME, 0));
	(void) zfs_iter_snapshots_sorted(zhp, send_iterate_snap, sd,
	    min_txg, max_txg);
	VERIFY(0 == nvlist_add_nvlist(nvfs, "snaps", sd->parent_snaps));
	VERIFY(0 == nvlist_add_nvlist(nvfs, "snapprops", sd->snapprops));
	fnvlist_free(sd->parent_snaps);
	fnvlist_free(sd->snapprops);

	/* add this fs to nvlist */
	(void) snprintf(guidstring, sizeof (guidstring),
	    "0x%llx", (longlong_t)guid);
	VERIFY(0 == nvlist_add_nvlist(sd->fss, guidstring, nvfs));
	nvlist_free(nvfs);

	/* iterate over children */
	if (sd->recursive)
		rv = zfs_iter_filesystems(zhp, send_iterate_fs, sd);

out:
	sd->parent_fromsnap_guid = parent_fromsnap_guid_save;
	sd->fromsnap_txg = fromsnap_txg_save;
	sd->tosnap_txg = tosnap_txg_save;

	zfs_close(zhp);
	return (rv);
}