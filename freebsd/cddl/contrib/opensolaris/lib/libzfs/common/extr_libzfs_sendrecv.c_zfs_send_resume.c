#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zfs_name; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_9__ {scalar_t__ progress; int /*<<< orphan*/  progressastitle; int /*<<< orphan*/  parsable; scalar_t__ dryrun; scalar_t__ verbose; scalar_t__ compress; scalar_t__ embed_data; scalar_t__ largeblock; } ;
typedef  TYPE_2__ sendflags_t ;
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_10__ {int pa_fd; int /*<<< orphan*/  pa_astitle; scalar_t__ pa_size; int /*<<< orphan*/  pa_parsable; TYPE_1__* pa_zhp; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ progress_arg_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  longlong_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  enum lzc_send_flags { ____Placeholder_lzc_send_flags } lzc_send_flags ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
#define  EDQUOT 140 
#define  EFAULT 139 
#define  EFBIG 138 
#define  EIO 137 
#define  ENOENT 136 
#define  ENOLINK 135 
#define  ENOSPC 134 
#define  ENOSTR 133 
#define  ENXIO 132 
#define  EPIPE 131 
#define  ERANGE 130 
#define  EROFS 129 
#define  EXDEV 128 
 int /*<<< orphan*/  EZFS_BADBACKUP ; 
 int /*<<< orphan*/  EZFS_BADPATH ; 
 int /*<<< orphan*/  EZFS_FAULT ; 
 int LZC_SEND_FLAG_COMPRESS ; 
 int LZC_SEND_FLAG_EMBED_DATA ; 
 int LZC_SEND_FLAG_LARGE_BLOCK ; 
 scalar_t__ MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ guid_to_name (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int lzc_send_resume (int /*<<< orphan*/ ,char*,int,int,scalar_t__,scalar_t__) ; 
 int lzc_send_space (int /*<<< orphan*/ ,char*,int,scalar_t__*) ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  nvlist_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cancel (int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_print_verbose (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_progress_thread ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 scalar_t__ zfs_dataset_exists (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__* zfs_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_send_resume_token_to_nvlist (int /*<<< orphan*/ *,char const*) ; 
 int zfs_standard_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

int
zfs_send_resume(libzfs_handle_t *hdl, sendflags_t *flags, int outfd,
    const char *resume_token)
{
	char errbuf[1024];
	char *toname;
	char *fromname = NULL;
	uint64_t resumeobj, resumeoff, toguid, fromguid, bytes;
	zfs_handle_t *zhp;
	int error = 0;
	char name[ZFS_MAX_DATASET_NAME_LEN];
	enum lzc_send_flags lzc_flags = 0;
	uint64_t size = 0;
	FILE *fout = (flags->verbose && flags->dryrun) ? stdout : stderr;

	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "cannot resume send"));

	nvlist_t *resume_nvl =
	    zfs_send_resume_token_to_nvlist(hdl, resume_token);
	if (resume_nvl == NULL) {
		/*
		 * zfs_error_aux has already been set by
		 * zfs_send_resume_token_to_nvlist
		 */
		return (zfs_error(hdl, EZFS_FAULT, errbuf));
	}
	if (flags->verbose) {
		(void) fprintf(fout, dgettext(TEXT_DOMAIN,
		    "resume token contents:\n"));
		nvlist_print(fout, resume_nvl);
	}

	if (nvlist_lookup_string(resume_nvl, "toname", &toname) != 0 ||
	    nvlist_lookup_uint64(resume_nvl, "object", &resumeobj) != 0 ||
	    nvlist_lookup_uint64(resume_nvl, "offset", &resumeoff) != 0 ||
	    nvlist_lookup_uint64(resume_nvl, "bytes", &bytes) != 0 ||
	    nvlist_lookup_uint64(resume_nvl, "toguid", &toguid) != 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "resume token is corrupt"));
		return (zfs_error(hdl, EZFS_FAULT, errbuf));
	}
	fromguid = 0;
	(void) nvlist_lookup_uint64(resume_nvl, "fromguid", &fromguid);

	if (flags->largeblock || nvlist_exists(resume_nvl, "largeblockok"))
		lzc_flags |= LZC_SEND_FLAG_LARGE_BLOCK;
	if (flags->embed_data || nvlist_exists(resume_nvl, "embedok"))
		lzc_flags |= LZC_SEND_FLAG_EMBED_DATA;
	if (flags->compress || nvlist_exists(resume_nvl, "compressok"))
		lzc_flags |= LZC_SEND_FLAG_COMPRESS;

	if (guid_to_name(hdl, toname, toguid, B_FALSE, name) != 0) {
		if (zfs_dataset_exists(hdl, toname, ZFS_TYPE_DATASET)) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "'%s' is no longer the same snapshot used in "
			    "the initial send"), toname);
		} else {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "'%s' used in the initial send no longer exists"),
			    toname);
		}
		return (zfs_error(hdl, EZFS_BADPATH, errbuf));
	}
	zhp = zfs_open(hdl, name, ZFS_TYPE_DATASET);
	if (zhp == NULL) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "unable to access '%s'"), name);
		return (zfs_error(hdl, EZFS_BADPATH, errbuf));
	}

	if (fromguid != 0) {
		if (guid_to_name(hdl, toname, fromguid, B_TRUE, name) != 0) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "incremental source %#llx no longer exists"),
			    (longlong_t)fromguid);
			return (zfs_error(hdl, EZFS_BADPATH, errbuf));
		}
		fromname = name;
	}

	if (flags->progress || flags->verbose) {
		error = lzc_send_space(zhp->zfs_name, fromname,
		    lzc_flags, &size);
		if (error == 0)
			size = MAX(0, (int64_t)(size - bytes));
	}
	if (flags->verbose) {
		send_print_verbose(fout, zhp->zfs_name, fromname,
		    size, flags->parsable);
	}

	if (!flags->dryrun) {
		progress_arg_t pa = { 0 };
		pthread_t tid;
		/*
		 * If progress reporting is requested, spawn a new thread to
		 * poll ZFS_IOC_SEND_PROGRESS at a regular interval.
		 */
		if (flags->progress) {
			pa.pa_zhp = zhp;
			pa.pa_fd = outfd;
			pa.pa_parsable = flags->parsable;
			pa.pa_size = size;
			pa.pa_astitle = flags->progressastitle;

			error = pthread_create(&tid, NULL,
			    send_progress_thread, &pa);
			if (error != 0) {
				zfs_close(zhp);
				return (error);
			}
		}

		error = lzc_send_resume(zhp->zfs_name, fromname, outfd,
		    lzc_flags, resumeobj, resumeoff);

		if (flags->progress) {
			(void) pthread_cancel(tid);
			(void) pthread_join(tid, NULL);
		}

		char errbuf[1024];
		(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
		    "warning: cannot send '%s'"), zhp->zfs_name);

		zfs_close(zhp);

		switch (error) {
		case 0:
			return (0);
		case EXDEV:
		case ENOENT:
		case EDQUOT:
		case EFBIG:
		case EIO:
		case ENOLINK:
		case ENOSPC:
#ifdef illumos
		case ENOSTR:
#endif
		case ENXIO:
		case EPIPE:
		case ERANGE:
		case EFAULT:
		case EROFS:
			zfs_error_aux(hdl, strerror(errno));
			return (zfs_error(hdl, EZFS_BADBACKUP, errbuf));

		default:
			return (zfs_standard_error(hdl, errno, errbuf));
		}
	}


	zfs_close(zhp);

	return (error);
}