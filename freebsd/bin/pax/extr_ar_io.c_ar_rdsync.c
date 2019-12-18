#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtop {int mt_count; int /*<<< orphan*/  mt_op; } ;
typedef  int off_t ;
struct TYPE_2__ {long st_blksize; } ;

/* Variables and functions */
 scalar_t__ APPND ; 
 scalar_t__ ARCHIVE ; 
 long BLKMULT ; 
#define  ISBLK 132 
#define  ISCHR 131 
#define  ISPIPE 130 
#define  ISREG 129 
#define  ISTAPE 128 
 int /*<<< orphan*/  MTFSR ; 
 int /*<<< orphan*/  MTIOCTOP ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ act ; 
 int /*<<< orphan*/  arfd ; 
 TYPE_1__ arsb ; 
 int artyp ; 
 int did_io ; 
 scalar_t__ done ; 
 scalar_t__ io_ok ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtop*) ; 
 int lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lstrval ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 

int
ar_rdsync(void)
{
	long fsbz;
	off_t cpos;
	off_t mpos;
	struct mtop mb;

	/*
	 * Fail resync attempts at user request (done) or this is going to be
	 * an update/append to an existing archive. If last i/o hit media end,
	 * we need to go to the next volume not try a resync.
	 */
	if ((done > 0) || (lstrval == 0))
		return(-1);

	if ((act == APPND) || (act == ARCHIVE)) {
		paxwarn(1, "Cannot allow updates to an archive with flaws.");
		return(-1);
	}
	if (io_ok)
		did_io = 1;

	switch(artyp) {
	case ISTAPE:
		/*
		 * if the last i/o was a successful data transfer, we assume
		 * the fault is just a bad record on the tape that we are now
		 * past. If we did not get any data since the last resync try
		 * to move the tape forward one PHYSICAL record past any
		 * damaged tape section. Some tape drives are stubborn and need
		 * to be pushed.
		 */
		if (io_ok) {
			io_ok = 0;
			lstrval = 1;
			break;
		}
		mb.mt_op = MTFSR;
		mb.mt_count = 1;
		if (ioctl(arfd, MTIOCTOP, &mb) < 0)
			break;
		lstrval = 1;
		break;
	case ISREG:
	case ISCHR:
	case ISBLK:
		/*
		 * try to step over the bad part of the device.
		 */
		io_ok = 0;
		if (((fsbz = arsb.st_blksize) <= 0) || (artyp != ISREG))
			fsbz = BLKMULT;
		if ((cpos = lseek(arfd, (off_t)0L, SEEK_CUR)) < 0)
			break;
		mpos = fsbz - (cpos % (off_t)fsbz);
		if (lseek(arfd, mpos, SEEK_CUR) < 0)
			break;
		lstrval = 1;
		break;
	case ISPIPE:
	default:
		/*
		 * cannot recover on these archive device types
		 */
		io_ok = 0;
		break;
	}
	if (lstrval <= 0) {
		paxwarn(1, "Unable to recover from an archive read failure.");
		return(-1);
	}
	paxwarn(0, "Attempting to recover from an archive read failure.");
	return(0);
}