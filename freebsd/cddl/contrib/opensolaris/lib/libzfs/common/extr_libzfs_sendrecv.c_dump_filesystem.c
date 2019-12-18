#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* zfs_name; TYPE_6__* zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_10__ {char* tosnap; char* fromsnap; void* err; void* seento; void* seenfrom; scalar_t__ replicate; scalar_t__ prevsnap_obj; void** prevsnap; } ;
typedef  TYPE_3__ send_dump_data_t ;
typedef  void* boolean_t ;
struct TYPE_11__ {int /*<<< orphan*/  libzfs_fd; } ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_OBJSET_STATS ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dump_snapshot ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 int /*<<< orphan*/  get_snap_txg (TYPE_6__*,char*,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int zfs_iter_snapshots_sorted (TYPE_1__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_filesystem(zfs_handle_t *zhp, void *arg)
{
	int rv = 0;
	uint64_t min_txg = 0, max_txg = 0;
	send_dump_data_t *sdd = arg;
	boolean_t missingfrom = B_FALSE;
	zfs_cmd_t zc = { 0 };

	(void) snprintf(zc.zc_name, sizeof (zc.zc_name), "%s@%s",
	    zhp->zfs_name, sdd->tosnap);
	if (ioctl(zhp->zfs_hdl->libzfs_fd, ZFS_IOC_OBJSET_STATS, &zc) != 0) {
		(void) fprintf(stderr, dgettext(TEXT_DOMAIN,
		    "WARNING: could not send %s@%s: does not exist\n"),
		    zhp->zfs_name, sdd->tosnap);
		sdd->err = B_TRUE;
		return (0);
	}

	if (sdd->replicate && sdd->fromsnap) {
		/*
		 * If this fs does not have fromsnap, and we're doing
		 * recursive, we need to send a full stream from the
		 * beginning (or an incremental from the origin if this
		 * is a clone).  If we're doing non-recursive, then let
		 * them get the error.
		 */
		(void) snprintf(zc.zc_name, sizeof (zc.zc_name), "%s@%s",
		    zhp->zfs_name, sdd->fromsnap);
		if (ioctl(zhp->zfs_hdl->libzfs_fd,
		    ZFS_IOC_OBJSET_STATS, &zc) != 0) {
			missingfrom = B_TRUE;
		}
	}

	sdd->seenfrom = sdd->seento = sdd->prevsnap[0] = 0;
	sdd->prevsnap_obj = 0;
	if (sdd->fromsnap == NULL || missingfrom)
		sdd->seenfrom = B_TRUE;

	if (!sdd->replicate && sdd->fromsnap != NULL)
		min_txg = get_snap_txg(zhp->zfs_hdl, zhp->zfs_name,
		    sdd->fromsnap);
	if (!sdd->replicate && sdd->tosnap != NULL)
		max_txg = get_snap_txg(zhp->zfs_hdl, zhp->zfs_name,
		    sdd->tosnap);

	rv = zfs_iter_snapshots_sorted(zhp, dump_snapshot, arg,
	    min_txg, max_txg);
	if (!sdd->seenfrom) {
		(void) fprintf(stderr, dgettext(TEXT_DOMAIN,
		    "WARNING: could not send %s@%s:\n"
		    "incremental source (%s@%s) does not exist\n"),
		    zhp->zfs_name, sdd->tosnap,
		    zhp->zfs_name, sdd->fromsnap);
		sdd->err = B_TRUE;
	} else if (!sdd->seento) {
		if (sdd->fromsnap) {
			(void) fprintf(stderr, dgettext(TEXT_DOMAIN,
			    "WARNING: could not send %s@%s:\n"
			    "incremental source (%s@%s) "
			    "is not earlier than it\n"),
			    zhp->zfs_name, sdd->tosnap,
			    zhp->zfs_name, sdd->fromsnap);
		} else {
			(void) fprintf(stderr, dgettext(TEXT_DOMAIN,
			    "WARNING: "
			    "could not send %s@%s: does not exist\n"),
			    zhp->zfs_name, sdd->tosnap);
		}
		sdd->err = B_TRUE;
	}

	return (rv);
}