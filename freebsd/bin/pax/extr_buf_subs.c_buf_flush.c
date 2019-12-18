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
struct TYPE_2__ {int blkalgn; } ;

/* Variables and functions */
 scalar_t__ ar_next () ; 
 int ar_write (scalar_t__,int) ; 
 int blksz ; 
 scalar_t__ buf ; 
 scalar_t__ bufend ; 
 scalar_t__ bufpt ; 
 int exit_val ; 
 TYPE_1__* frmt ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  paxwarn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wrcnt ; 
 scalar_t__ wrlimit ; 

int
buf_flush(int bufcnt)
{
	int cnt;
	int push = 0;
	int totcnt = 0;

	/*
	 * if we have reached the user specified byte count for each archive
	 * volume, prompt for the next volume. (The non-standard -R flag).
	 * NOTE: If the wrlimit is smaller than wrcnt, we will always write
	 * at least one record. We always round limit UP to next blocksize.
	 */
	if ((wrlimit > 0) && (wrcnt > wrlimit)) {
		paxwarn(0, "User specified archive volume byte limit reached.");
		if (ar_next() < 0) {
			wrcnt = 0;
			exit_val = 1;
			return(-1);
		}
		wrcnt = 0;

		/*
		 * The new archive volume might have changed the size of the
		 * write blocksize. if so we figure out if we need to write
		 * (one or more times), or if there is now free space left in
		 * the buffer (it is no longer full). bufcnt has the number of
		 * bytes in the buffer, (the blocksize, at the point we were
		 * CALLED). Push has the amount of "extra" data in the buffer
		 * if the block size has shrunk from a volume change.
		 */
		bufend = buf + blksz;
		if (blksz > bufcnt)
			return(0);
		if (blksz < bufcnt)
			push = bufcnt - blksz;
	}

	/*
	 * We have enough data to write at least one archive block
	 */
	for (;;) {
		/*
		 * write a block and check if it all went out ok
		 */
		cnt = ar_write(buf, blksz);
		if (cnt == blksz) {
			/*
			 * the write went ok
			 */
			wrcnt += cnt;
			totcnt += cnt;
			if (push > 0) {
				/* we have extra data to push to the front.
				 * check for more than 1 block of push, and if
				 * so we loop back to write again
				 */
				memcpy(buf, bufend, push);
				bufpt = buf + push;
				if (push >= blksz) {
					push -= blksz;
					continue;
				}
			} else
				bufpt = buf;
			return(totcnt);
		} else if (cnt > 0) {
			/*
			 * Oh drat we got a partial write!
			 * if format doesn't care about alignment let it go,
			 * we warned the user in ar_write().... but this means
			 * the last record on this volume violates pax spec....
			 */
			totcnt += cnt;
			wrcnt += cnt;
			bufpt = buf + cnt;
			cnt = bufcnt - cnt;
			memcpy(buf, bufpt, cnt);
			bufpt = buf + cnt;
			if (!frmt->blkalgn || ((cnt % frmt->blkalgn) == 0))
				return(totcnt);
			break;
		}

		/*
		 * All done, go to next archive
		 */
		wrcnt = 0;
		if (ar_next() < 0)
			break;

		/*
		 * The new archive volume might also have changed the block
		 * size. if so, figure out if we have too much or too little
		 * data for using the new block size
		 */
		bufend = buf + blksz;
		if (blksz > bufcnt)
			return(0);
		if (blksz < bufcnt)
			push = bufcnt - blksz;
	}

	/*
	 * write failed, stop pax. we must not create a bad archive!
	 */
	exit_val = 1;
	return(-1);
}