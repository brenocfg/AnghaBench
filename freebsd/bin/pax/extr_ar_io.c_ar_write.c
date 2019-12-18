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
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int blkalgn; } ;

/* Variables and functions */
 int BLKMULT ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EDQUOT ; 
 int /*<<< orphan*/  EFBIG ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  ENXIO ; 
#define  ISBLK 132 
#define  ISCHR 131 
#define  ISPIPE 130 
#define  ISREG 129 
#define  ISTAPE 128 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  arfd ; 
 int artyp ; 
 int /*<<< orphan*/  arvol ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__* frmt ; 
 int /*<<< orphan*/  ftruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int io_ok ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lstrval ; 
 int /*<<< orphan*/  paxwarn (int,char*,...) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int wr_trail ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

int
ar_write(char *buf, int bsz)
{
	int res;
	off_t cpos;

	/*
	 * do not allow pax to create a "bad" archive. Once a write fails on
	 * an archive volume prevent further writes to it.
	 */
	if (lstrval <= 0)
		return(lstrval);

	if ((res = write(arfd, buf, bsz)) == bsz) {
		wr_trail = 1;
		io_ok = 1;
		return(bsz);
	}
	/*
	 * write broke, see what we can do with it. We try to send any partial
	 * writes that may violate pax spec to the next archive volume.
	 */
	if (res < 0)
		lstrval = res;
	else
		lstrval = 0;

	switch (artyp) {
	case ISREG:
		if ((res > 0) && (res % BLKMULT)) {
			/*
		 	 * try to fix up partial writes which are not BLKMULT
			 * in size by forcing the runt record to next archive
			 * volume
		 	 */
			if ((cpos = lseek(arfd, (off_t)0L, SEEK_CUR)) < 0)
				break;
			cpos -= (off_t)res;
			if (ftruncate(arfd, cpos) < 0)
				break;
			res = lstrval = 0;
			break;
		}
		if (res >= 0)
			break;
		/*
		 * if file is out of space, handle it like a return of 0
		 */
		if ((errno == ENOSPC) || (errno == EFBIG) || (errno == EDQUOT))
			res = lstrval = 0;
		break;
	case ISTAPE:
	case ISCHR:
	case ISBLK:
		if (res >= 0)
			break;
		if (errno == EACCES) {
			paxwarn(0, "Write failed, archive is write protected.");
			res = lstrval = 0;
			return(0);
		}
		/*
		 * see if we reached the end of media, if so force a change to
		 * the next volume
		 */
		if ((errno == ENOSPC) || (errno == EIO) || (errno == ENXIO))
			res = lstrval = 0;
		break;
	case ISPIPE:
	default:
		/*
		 * we cannot fix errors to these devices
		 */
		break;
	}

	/*
	 * Better tell the user the bad news...
	 * if this is a block aligned archive format, we may have a bad archive
	 * if the format wants the header to start at a BLKMULT boundary. While
	 * we can deal with the mis-aligned data, it violates spec and other
	 * archive readers will likely fail. If the format is not block
	 * aligned, the user may be lucky (and the archive is ok).
	 */
	if (res >= 0) {
		if (res > 0)
			wr_trail = 1;
		io_ok = 1;
	}

	/*
	 * If we were trying to rewrite the trailer and it didn't work, we
	 * must quit right away.
	 */
	if (!wr_trail && (res <= 0)) {
		paxwarn(1,"Unable to append, trailer re-write failed. Quitting.");
		return(res);
	}

	if (res == 0)
		paxwarn(0, "End of archive volume %d reached", arvol);
	else if (res < 0)
		syswarn(1, errno, "Failed write to archive volume: %d", arvol);
	else if (!frmt->blkalgn || ((res % frmt->blkalgn) == 0))
		paxwarn(0,"WARNING: partial archive write. Archive MAY BE FLAWED");
	else
		paxwarn(1,"WARNING: partial archive write. Archive IS FLAWED");
	return(res);
}