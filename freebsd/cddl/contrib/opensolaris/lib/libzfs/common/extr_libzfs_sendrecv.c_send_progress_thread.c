#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* zfs_name; int /*<<< orphan*/ * zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_6__ {unsigned long long zc_cookie; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_hour; int tm_min; int tm_sec; } ;
struct TYPE_7__ {unsigned long long pa_fd; unsigned long long pa_size; scalar_t__ pa_parsable; scalar_t__ pa_astitle; TYPE_1__* pa_zhp; } ;
typedef  TYPE_3__ progress_arg_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_SEND_PROGRESS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setproctitle (char*,char*,int,unsigned long long,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_nicenum (unsigned long long,char*,int) ; 

__attribute__((used)) static void *
send_progress_thread(void *arg)
{
	progress_arg_t *pa = arg;
	zfs_cmd_t zc = { 0 };
	zfs_handle_t *zhp = pa->pa_zhp;
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	unsigned long long bytes, total;
	char buf[16];
	time_t t;
	struct tm *tm;

	(void) strlcpy(zc.zc_name, zhp->zfs_name, sizeof (zc.zc_name));

	if (!pa->pa_parsable && !pa->pa_astitle)
		(void) fprintf(stderr, "TIME        SENT   SNAPSHOT\n");

	/*
	 * Print the progress from ZFS_IOC_SEND_PROGRESS every second.
	 */
	for (;;) {
		(void) sleep(1);

		zc.zc_cookie = pa->pa_fd;
		if (zfs_ioctl(hdl, ZFS_IOC_SEND_PROGRESS, &zc) != 0)
			return ((void *)-1);

		(void) time(&t);
		tm = localtime(&t);
		bytes = zc.zc_cookie;

		if (pa->pa_astitle) {
			int pct;
			if (pa->pa_size > bytes)
				pct = 100 * bytes / pa->pa_size;
			else
				pct = 100;

			setproctitle("sending %s (%d%%: %llu/%llu)",
			    zhp->zfs_name, pct, bytes, pa->pa_size);
		} else if (pa->pa_parsable) {
			(void) fprintf(stderr, "%02d:%02d:%02d\t%llu\t%s\n",
			    tm->tm_hour, tm->tm_min, tm->tm_sec,
			    bytes, zhp->zfs_name);
		} else {
			zfs_nicenum(bytes, buf, sizeof (buf));
			(void) fprintf(stderr, "%02d:%02d:%02d   %5s   %s\n",
			    tm->tm_hour, tm->tm_min, tm->tm_sec,
			    buf, zhp->zfs_name);
		}
	}
}