#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_5__* zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_13__ {int zc_cookie; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  zc_value; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  errbuf ;
struct TYPE_14__ {int scripted; int classify; int timestamped; int outputfd; int datafd; scalar_t__ zerr; char* errbuf; int /*<<< orphan*/  tosnap; int /*<<< orphan*/  fromsnap; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ differ_info_t ;
struct TYPE_15__ {int /*<<< orphan*/  libzfs_fd; } ;

/* Variables and functions */
 scalar_t__ EPERM ; 
 scalar_t__ EPIPE ; 
 scalar_t__ EXDEV ; 
 int /*<<< orphan*/  EZFS_DIFF ; 
 int /*<<< orphan*/  EZFS_DIFFDATA ; 
 int /*<<< orphan*/  EZFS_PIPEFAILED ; 
 int /*<<< orphan*/  EZFS_THREADCREATEFAILED ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int ZFS_DIFF_CLASSIFY ; 
 int ZFS_DIFF_PARSEABLE ; 
 int ZFS_DIFF_TIMESTAMP ; 
 int /*<<< orphan*/  ZFS_IOC_DIFF ; 
 int /*<<< orphan*/  close (int) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  differ ; 
 scalar_t__ errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  pthread_cancel (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ setup_differ_info (TYPE_1__*,char const*,char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teardown_differ_info (TYPE_3__*) ; 
 int zfs_error (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (TYPE_5__*,char*) ; 

int
zfs_show_diffs(zfs_handle_t *zhp, int outfd, const char *fromsnap,
    const char *tosnap, int flags)
{
	zfs_cmd_t zc = { 0 };
	char errbuf[1024];
	differ_info_t di = { 0 };
	pthread_t tid;
	int pipefd[2];
	int iocerr;

	(void) snprintf(errbuf, sizeof (errbuf),
	    dgettext(TEXT_DOMAIN, "zfs diff failed"));

	if (setup_differ_info(zhp, fromsnap, tosnap, &di)) {
		teardown_differ_info(&di);
		return (-1);
	}

	if (pipe(pipefd)) {
		zfs_error_aux(zhp->zfs_hdl, strerror(errno));
		teardown_differ_info(&di);
		return (zfs_error(zhp->zfs_hdl, EZFS_PIPEFAILED, errbuf));
	}

	di.scripted = (flags & ZFS_DIFF_PARSEABLE);
	di.classify = (flags & ZFS_DIFF_CLASSIFY);
	di.timestamped = (flags & ZFS_DIFF_TIMESTAMP);

	di.outputfd = outfd;
	di.datafd = pipefd[0];

	if (pthread_create(&tid, NULL, differ, &di)) {
		zfs_error_aux(zhp->zfs_hdl, strerror(errno));
		(void) close(pipefd[0]);
		(void) close(pipefd[1]);
		teardown_differ_info(&di);
		return (zfs_error(zhp->zfs_hdl,
		    EZFS_THREADCREATEFAILED, errbuf));
	}

	/* do the ioctl() */
	(void) strlcpy(zc.zc_value, di.fromsnap, strlen(di.fromsnap) + 1);
	(void) strlcpy(zc.zc_name, di.tosnap, strlen(di.tosnap) + 1);
	zc.zc_cookie = pipefd[1];

	iocerr = ioctl(zhp->zfs_hdl->libzfs_fd, ZFS_IOC_DIFF, &zc);
	if (iocerr != 0) {
		(void) snprintf(errbuf, sizeof (errbuf),
		    dgettext(TEXT_DOMAIN, "Unable to obtain diffs"));
		if (errno == EPERM) {
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "\n   The sys_mount privilege or diff delegated "
			    "permission is needed\n   to execute the "
			    "diff ioctl"));
		} else if (errno == EXDEV) {
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "\n   Not an earlier snapshot from the same fs"));
		} else if (errno != EPIPE || di.zerr == 0) {
			zfs_error_aux(zhp->zfs_hdl, strerror(errno));
		}
		(void) close(pipefd[1]);
		(void) pthread_cancel(tid);
		(void) pthread_join(tid, NULL);
		teardown_differ_info(&di);
		if (di.zerr != 0 && di.zerr != EPIPE) {
			zfs_error_aux(zhp->zfs_hdl, strerror(di.zerr));
			return (zfs_error(zhp->zfs_hdl, EZFS_DIFF, di.errbuf));
		} else {
			return (zfs_error(zhp->zfs_hdl, EZFS_DIFFDATA, errbuf));
		}
	}

	(void) close(pipefd[1]);
	(void) pthread_join(tid, NULL);

	if (di.zerr != 0) {
		zfs_error_aux(zhp->zfs_hdl, strerror(di.zerr));
		return (zfs_error(zhp->zfs_hdl, EZFS_DIFF, di.errbuf));
	}
	teardown_differ_info(&di);
	return (0);
}