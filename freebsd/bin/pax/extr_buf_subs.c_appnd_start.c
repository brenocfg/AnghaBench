#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE ; 
 int /*<<< orphan*/  act ; 
 scalar_t__ ar_app_ok () ; 
 int ar_read (scalar_t__,scalar_t__) ; 
 scalar_t__ ar_rev (scalar_t__) ; 
 scalar_t__ ar_set_wr () ; 
 scalar_t__ blksz ; 
 scalar_t__ buf ; 
 scalar_t__ bufend ; 
 scalar_t__ bufpt ; 
 scalar_t__ exit_val ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 scalar_t__ rdblksz ; 
 scalar_t__ rdcnt ; 
 scalar_t__ wrblksz ; 
 scalar_t__ wrcnt ; 

int
appnd_start(off_t skcnt)
{
	int res;
	off_t cnt;

	if (exit_val != 0) {
		paxwarn(0, "Cannot append to an archive that may have flaws.");
		return(-1);
	}
	/*
	 * if the user did not specify a write blocksize, inherit the size used
	 * in the last archive volume read. (If a is set we still use rdblksz
	 * until next volume, cannot shift sizes within a single volume).
	 */
	if (!wrblksz)
		wrblksz = blksz = rdblksz;
	else
		blksz = rdblksz;

	/*
	 * make sure that this volume allows appends
	 */
	if (ar_app_ok() < 0)
		return(-1);

	/*
	 * Calculate bytes to move back and move in front of record where we
	 * need to start writing from. Remember we have to add in any padding
	 * that might be in the buffer after the trailer in the last block. We
	 * travel skcnt + padding ROUNDED UP to blksize.
	 */
	skcnt += bufend - bufpt;
	if ((cnt = (skcnt/blksz) * blksz) < skcnt)
		cnt += blksz;
	if (ar_rev((off_t)cnt) < 0)
		goto out;

	/*
	 * We may have gone too far if there is valid data in the block we are
	 * now in front of, read up the block and position the pointer after
	 * the valid data.
	 */
	if ((cnt -= skcnt) > 0) {
		/*
		 * watch out for stupid tape drives. ar_rev() will set rdblksz
		 * to be real physical blocksize so we must loop until we get
		 * the old rdblksz (now in blksz). If ar_rev() fouls up the
		 * determination of the physical block size, we will fail.
		 */
		bufpt = buf;
		bufend = buf + blksz;
		while (bufpt < bufend) {
			if ((res = ar_read(bufpt, rdblksz)) <= 0)
				goto out;
			bufpt += res;
		}
		if (ar_rev((off_t)(bufpt - buf)) < 0)
			goto out;
		bufpt = buf + cnt;
		bufend = buf + blksz;
	} else {
		/*
		 * buffer is empty
		 */
		bufend = buf + blksz;
		bufpt = buf;
	}
	rdblksz = blksz;
	rdcnt -= skcnt;
	wrcnt = 0;

	/*
	 * At this point we are ready to write. If the device requires special
	 * handling to write at a point were previously recorded data resides,
	 * that is handled in ar_set_wr(). From now on we operate under normal
	 * ARCHIVE mode (write) conditions
	 */
	if (ar_set_wr() < 0)
		return(-1);
	act = ARCHIVE;
	return(0);

    out:
	paxwarn(1, "Unable to rewrite archive trailer, cannot append.");
	return(-1);
}