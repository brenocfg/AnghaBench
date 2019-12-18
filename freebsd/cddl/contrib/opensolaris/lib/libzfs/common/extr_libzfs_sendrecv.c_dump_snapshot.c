#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  dds_guid; } ;
struct TYPE_15__ {char* zfs_name; TYPE_1__ zfs_dmustats; } ;
typedef  TYPE_2__ zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_16__ {char* prevsnap; scalar_t__ (* filter_cb ) (TYPE_2__*,int /*<<< orphan*/ ) ;void* prevsnap_obj; scalar_t__ progress; int /*<<< orphan*/  debugnv; int /*<<< orphan*/  outfd; int /*<<< orphan*/  progressastitle; int /*<<< orphan*/  size; int /*<<< orphan*/  parsable; int /*<<< orphan*/  dryrun; scalar_t__ verbose; scalar_t__ replicate; scalar_t__ fromorigin; int /*<<< orphan*/  filter_cb_arg; int /*<<< orphan*/  fsavl; int /*<<< orphan*/  doall; scalar_t__ compress; scalar_t__ embed_data; scalar_t__ large_block; void* seento; int /*<<< orphan*/ * tosnap; void* seenfrom; int /*<<< orphan*/ * fromsnap; scalar_t__ std_out; } ;
typedef  TYPE_3__ send_dump_data_t ;
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_17__ {int /*<<< orphan*/  pa_astitle; int /*<<< orphan*/  pa_size; int /*<<< orphan*/  pa_parsable; int /*<<< orphan*/  pa_fd; TYPE_2__* pa_zhp; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ progress_arg_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  fromds ;
typedef  enum lzc_send_flags { ____Placeholder_lzc_send_flags } lzc_send_flags ;
typedef  int boolean_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 void* B_TRUE ; 
 int LZC_SEND_FLAG_COMPRESS ; 
 int LZC_SEND_FLAG_EMBED_DATA ; 
 int LZC_SEND_FLAG_LARGE_BLOCK ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_OBJSETID ; 
 int dump_ioctl (TYPE_2__*,char*,void*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fsavl_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  gather_holds (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pthread_cancel (int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_print_verbose (int /*<<< orphan*/ *,char*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_progress_thread ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (TYPE_2__*) ; 
 void* zfs_prop_get_int (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_send_space (TYPE_2__*,char*,char*,int,scalar_t__*) ; 

__attribute__((used)) static int
dump_snapshot(zfs_handle_t *zhp, void *arg)
{
	send_dump_data_t *sdd = arg;
	progress_arg_t pa = { 0 };
	pthread_t tid;
	char *thissnap;
	enum lzc_send_flags flags = 0;
	int err;
	boolean_t isfromsnap, istosnap, fromorigin;
	boolean_t exclude = B_FALSE;
	FILE *fout = sdd->std_out ? stdout : stderr;

	err = 0;
	thissnap = strchr(zhp->zfs_name, '@') + 1;
	isfromsnap = (sdd->fromsnap != NULL &&
	    strcmp(sdd->fromsnap, thissnap) == 0);

	if (!sdd->seenfrom && isfromsnap) {
		gather_holds(zhp, sdd);
		sdd->seenfrom = B_TRUE;
		(void) strcpy(sdd->prevsnap, thissnap);
		sdd->prevsnap_obj = zfs_prop_get_int(zhp, ZFS_PROP_OBJSETID);
		zfs_close(zhp);
		return (0);
	}

	if (sdd->seento || !sdd->seenfrom) {
		zfs_close(zhp);
		return (0);
	}

	istosnap = (strcmp(sdd->tosnap, thissnap) == 0);
	if (istosnap)
		sdd->seento = B_TRUE;

	if (sdd->large_block)
		flags |= LZC_SEND_FLAG_LARGE_BLOCK;
	if (sdd->embed_data)
		flags |= LZC_SEND_FLAG_EMBED_DATA;
	if (sdd->compress)
		flags |= LZC_SEND_FLAG_COMPRESS;

	if (!sdd->doall && !isfromsnap && !istosnap) {
		if (sdd->replicate) {
			char *snapname;
			nvlist_t *snapprops;
			/*
			 * Filter out all intermediate snapshots except origin
			 * snapshots needed to replicate clones.
			 */
			nvlist_t *nvfs = fsavl_find(sdd->fsavl,
			    zhp->zfs_dmustats.dds_guid, &snapname);

			VERIFY(0 == nvlist_lookup_nvlist(nvfs,
			    "snapprops", &snapprops));
			VERIFY(0 == nvlist_lookup_nvlist(snapprops,
			    thissnap, &snapprops));
			exclude = !nvlist_exists(snapprops, "is_clone_origin");
		} else {
			exclude = B_TRUE;
		}
	}

	/*
	 * If a filter function exists, call it to determine whether
	 * this snapshot will be sent.
	 */
	if (exclude || (sdd->filter_cb != NULL &&
	    sdd->filter_cb(zhp, sdd->filter_cb_arg) == B_FALSE)) {
		/*
		 * This snapshot is filtered out.  Don't send it, and don't
		 * set prevsnap_obj, so it will be as if this snapshot didn't
		 * exist, and the next accepted snapshot will be sent as
		 * an incremental from the last accepted one, or as the
		 * first (and full) snapshot in the case of a replication,
		 * non-incremental send.
		 */
		zfs_close(zhp);
		return (0);
	}

	gather_holds(zhp, sdd);
	fromorigin = sdd->prevsnap[0] == '\0' &&
	    (sdd->fromorigin || sdd->replicate);

	if (sdd->verbose || sdd->progress) {
		uint64_t size = 0;
		char fromds[ZFS_MAX_DATASET_NAME_LEN];

		if (sdd->prevsnap[0] != '\0') {
			(void) strlcpy(fromds, zhp->zfs_name, sizeof (fromds));
			*(strchr(fromds, '@') + 1) = '\0';
			(void) strlcat(fromds, sdd->prevsnap, sizeof (fromds));
		}
		if (zfs_send_space(zhp, zhp->zfs_name,
		    sdd->prevsnap[0] ? fromds : NULL, flags, &size) != 0) {
			size = 0; /* cannot estimate send space */
		} else {
			send_print_verbose(fout, zhp->zfs_name,
			    sdd->prevsnap[0] ? sdd->prevsnap : NULL,
			    size, sdd->parsable);
		}
		sdd->size += size;
	}

	if (!sdd->dryrun) {
		/*
		 * If progress reporting is requested, spawn a new thread to
		 * poll ZFS_IOC_SEND_PROGRESS at a regular interval.
		 */
		if (sdd->progress) {
			pa.pa_zhp = zhp;
			pa.pa_fd = sdd->outfd;
			pa.pa_parsable = sdd->parsable;
			pa.pa_size = sdd->size;
			pa.pa_astitle = sdd->progressastitle;

			if ((err = pthread_create(&tid, NULL,
			    send_progress_thread, &pa)) != 0) {
				zfs_close(zhp);
				return (err);
			}
		}

		err = dump_ioctl(zhp, sdd->prevsnap, sdd->prevsnap_obj,
		    fromorigin, sdd->outfd, flags, sdd->debugnv);

		if (sdd->progress) {
			(void) pthread_cancel(tid);
			(void) pthread_join(tid, NULL);
		}
	}

	(void) strcpy(sdd->prevsnap, thissnap);
	sdd->prevsnap_obj = zfs_prop_get_int(zhp, ZFS_PROP_OBJSETID);
	zfs_close(zhp);
	return (err);
}