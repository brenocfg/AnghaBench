#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zprop_source_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  origin ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
struct TYPE_6__ {char* ds; void* tosnap; void* fromsnap; int /*<<< orphan*/  isclone; int /*<<< orphan*/  errbuf; TYPE_1__* zhp; } ;
typedef  TYPE_2__ differ_info_t ;
struct TYPE_5__ {int /*<<< orphan*/ * zfs_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_ORIGIN ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int make_temp_snapshot (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 void* zfs_alloc (int /*<<< orphan*/ *,int) ; 
 void* zfs_asprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* zfs_strdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  zfs_validate_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_snapshot_names(differ_info_t *di, const char *fromsnap,
    const char *tosnap)
{
	libzfs_handle_t *hdl = di->zhp->zfs_hdl;
	char *atptrf = NULL;
	char *atptrt = NULL;
	int fdslen, fsnlen;
	int tdslen, tsnlen;

	/*
	 * Can accept
	 *    dataset@snap1
	 *    dataset@snap1 dataset@snap2
	 *    dataset@snap1 @snap2
	 *    dataset@snap1 dataset
	 *    @snap1 dataset@snap2
	 */
	if (tosnap == NULL) {
		/* only a from snapshot given, must be valid */
		(void) snprintf(di->errbuf, sizeof (di->errbuf),
		    dgettext(TEXT_DOMAIN,
		    "Badly formed snapshot name %s"), fromsnap);

		if (!zfs_validate_name(hdl, fromsnap, ZFS_TYPE_SNAPSHOT,
		    B_FALSE)) {
			return (zfs_error(hdl, EZFS_INVALIDNAME,
			    di->errbuf));
		}

		atptrf = strchr(fromsnap, '@');
		ASSERT(atptrf != NULL);
		fdslen = atptrf - fromsnap;

		di->fromsnap = zfs_strdup(hdl, fromsnap);
		di->ds = zfs_strdup(hdl, fromsnap);
		di->ds[fdslen] = '\0';

		/* the to snap will be a just-in-time snap of the head */
		return (make_temp_snapshot(di));
	}

	(void) snprintf(di->errbuf, sizeof (di->errbuf),
	    dgettext(TEXT_DOMAIN,
	    "Unable to determine which snapshots to compare"));

	atptrf = strchr(fromsnap, '@');
	atptrt = strchr(tosnap, '@');
	fdslen = atptrf ? atptrf - fromsnap : strlen(fromsnap);
	tdslen = atptrt ? atptrt - tosnap : strlen(tosnap);
	fsnlen = strlen(fromsnap) - fdslen;	/* includes @ sign */
	tsnlen = strlen(tosnap) - tdslen;	/* includes @ sign */

	if (fsnlen <= 1 || tsnlen == 1 || (fdslen == 0 && tdslen == 0) ||
	    (fsnlen == 0 && tsnlen == 0)) {
		return (zfs_error(hdl, EZFS_INVALIDNAME, di->errbuf));
	} else if ((fdslen > 0 && tdslen > 0) &&
	    ((tdslen != fdslen || strncmp(fromsnap, tosnap, fdslen) != 0))) {
		/*
		 * not the same dataset name, might be okay if
		 * tosnap is a clone of a fromsnap descendant.
		 */
		char origin[ZFS_MAX_DATASET_NAME_LEN];
		zprop_source_t src;
		zfs_handle_t *zhp;

		di->ds = zfs_alloc(di->zhp->zfs_hdl, tdslen + 1);
		(void) strncpy(di->ds, tosnap, tdslen);
		di->ds[tdslen] = '\0';

		zhp = zfs_open(hdl, di->ds, ZFS_TYPE_FILESYSTEM);
		while (zhp != NULL) {
			if (zfs_prop_get(zhp, ZFS_PROP_ORIGIN, origin,
			    sizeof (origin), &src, NULL, 0, B_FALSE) != 0) {
				(void) zfs_close(zhp);
				zhp = NULL;
				break;
			}
			if (strncmp(origin, fromsnap, fsnlen) == 0)
				break;

			(void) zfs_close(zhp);
			zhp = zfs_open(hdl, origin, ZFS_TYPE_FILESYSTEM);
		}

		if (zhp == NULL) {
			(void) snprintf(di->errbuf, sizeof (di->errbuf),
			    dgettext(TEXT_DOMAIN,
			    "Not an earlier snapshot from the same fs"));
			return (zfs_error(hdl, EZFS_INVALIDNAME, di->errbuf));
		} else {
			(void) zfs_close(zhp);
		}

		di->isclone = B_TRUE;
		di->fromsnap = zfs_strdup(hdl, fromsnap);
		if (tsnlen) {
			di->tosnap = zfs_strdup(hdl, tosnap);
		} else {
			return (make_temp_snapshot(di));
		}
	} else {
		int dslen = fdslen ? fdslen : tdslen;

		di->ds = zfs_alloc(hdl, dslen + 1);
		(void) strncpy(di->ds, fdslen ? fromsnap : tosnap, dslen);
		di->ds[dslen] = '\0';

		di->fromsnap = zfs_asprintf(hdl, "%s%s", di->ds, atptrf);
		if (tsnlen) {
			di->tosnap = zfs_asprintf(hdl, "%s%s", di->ds, atptrt);
		} else {
			return (make_temp_snapshot(di));
		}
	}
	return (0);
}