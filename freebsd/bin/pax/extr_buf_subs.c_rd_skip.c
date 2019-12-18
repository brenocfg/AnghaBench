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
typedef  long off_t ;

/* Variables and functions */
 long MIN (long,long) ; 
 scalar_t__ ar_fow (long,long*) ; 
 long buf_fill () ; 
 long bufend ; 
 long bufpt ; 
 long rdblksz ; 
 long rdcnt ; 

int
rd_skip(off_t skcnt)
{
	off_t res;
	off_t cnt;
	off_t skipped = 0;

	/*
	 * consume what data we have in the buffer. If we have to move forward
	 * whole records, we call the low level skip function to see if we can
	 * move within the archive without doing the expensive reads on data we
	 * do not want.
	 */
	if (skcnt == 0)
		return(0);
	res = MIN((bufend - bufpt), skcnt);
	bufpt += res;
	skcnt -= res;

	/*
	 * if skcnt is now 0, then no additional i/o is needed
	 */
	if (skcnt == 0)
		return(0);

	/*
	 * We have to read more, calculate complete and partial record reads
	 * based on rdblksz. we skip over "cnt" complete records
	 */
	res = skcnt%rdblksz;
	cnt = (skcnt/rdblksz) * rdblksz;

	/*
	 * if the skip fails, we will have to resync. ar_fow will tell us
	 * how much it can skip over. We will have to read the rest.
	 */
	if (ar_fow(cnt, &skipped) < 0)
		return(-1);
	res += cnt - skipped;
	rdcnt += skipped;

	/*
	 * what is left we have to read (which may be the whole thing if
	 * ar_fow() told us the device can only read to skip records);
	 */
	while (res > 0L) {
		cnt = bufend - bufpt;
		/*
		 * if the read fails, we will have to resync
		 */
		if ((cnt <= 0) && ((cnt = buf_fill()) < 0))
			return(-1);
		if (cnt == 0)
			return(1);
		cnt = MIN(cnt, res);
		bufpt += cnt;
		res -= cnt;
	}
	return(0);
}