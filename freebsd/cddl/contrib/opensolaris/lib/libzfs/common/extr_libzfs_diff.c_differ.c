#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dr ;
struct TYPE_7__ {int ddr_type; } ;
typedef  TYPE_1__ dmu_diff_record_t ;
struct TYPE_8__ {scalar_t__ zerr; int /*<<< orphan*/  errbuf; int /*<<< orphan*/  datafd; int /*<<< orphan*/  outputfd; } ;
typedef  TYPE_2__ differ_info_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  DDR_FREE 129 
#define  DDR_INUSE 128 
 scalar_t__ EPIPE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int /*<<< orphan*/ ,char*) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  strerror_r (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int write_free_diffs (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 int write_inuse_diffs (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void *
differ(void *arg)
{
	differ_info_t *di = arg;
	dmu_diff_record_t dr;
	FILE *ofp;
	int err = 0;

	if ((ofp = fdopen(di->outputfd, "w")) == NULL) {
		di->zerr = errno;
		(void) strerror_r(errno, di->errbuf, sizeof (di->errbuf));
		(void) close(di->datafd);
		return ((void *)-1);
	}

	for (;;) {
		char *cp = (char *)&dr;
		int len = sizeof (dr);
		int rv;

		do {
			rv = read(di->datafd, cp, len);
			cp += rv;
			len -= rv;
		} while (len > 0 && rv > 0);

		if (rv < 0 || (rv == 0 && len != sizeof (dr))) {
			di->zerr = EPIPE;
			break;
		} else if (rv == 0) {
			/* end of file at a natural breaking point */
			break;
		}

		switch (dr.ddr_type) {
		case DDR_FREE:
			err = write_free_diffs(ofp, di, &dr);
			break;
		case DDR_INUSE:
			err = write_inuse_diffs(ofp, di, &dr);
			break;
		default:
			di->zerr = EPIPE;
			break;
		}

		if (err || di->zerr)
			break;
	}

	(void) fclose(ofp);
	(void) close(di->datafd);
	if (err)
		return ((void *)-1);
	if (di->zerr) {
		ASSERT(di->zerr == EPIPE);
		(void) snprintf(di->errbuf, sizeof (di->errbuf),
		    dgettext(TEXT_DOMAIN,
		    "Internal error: bad data from diff IOCTL"));
		return ((void *)-1);
	}
	return ((void *)0);
}