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

/* Variables and functions */
 int BLKMULT ; 
#define  ISBLK 132 
#define  ISCHR 131 
#define  ISPIPE 130 
#define  ISREG 129 
#define  ISTAPE 128 
 int /*<<< orphan*/  arfd ; 
 int artyp ; 
 int /*<<< orphan*/  arvol ; 
 int /*<<< orphan*/  errno ; 
 int invld_rec ; 
 int io_ok ; 
 int lstrval ; 
 int /*<<< orphan*/  paxwarn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int rdblksz ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
ar_read(char *buf, int cnt)
{
	int res = 0;

	/*
	 * if last i/o was in error, no more reads until reset or new volume
	 */
	if (lstrval <= 0)
		return(lstrval);

	/*
	 * how we read must be based on device type
	 */
	switch (artyp) {
	case ISTAPE:
		if ((res = read(arfd, buf, cnt)) > 0) {
			/*
			 * CAUTION: tape systems may not always return the same
			 * sized records so we leave blksz == MAXBLK. The
			 * physical record size that a tape drive supports is
			 * very hard to determine in a uniform and portable
			 * manner.
			 */
			io_ok = 1;
			if (res != rdblksz) {
				/*
				 * Record size changed. If this is happens on
				 * any record after the first, we probably have
				 * a tape drive which has a fixed record size
				 * we are getting multiple records in a single
				 * read). Watch out for record blocking that
				 * violates pax spec (must be a multiple of
				 * BLKMULT).
				 */
				rdblksz = res;
				if (rdblksz % BLKMULT)
					invld_rec = 1;
			}
			return(res);
		}
		break;
	case ISREG:
	case ISBLK:
	case ISCHR:
	case ISPIPE:
	default:
		/*
		 * Files are so easy to deal with. These other things cannot
		 * be trusted at all. So when we are dealing with character
		 * devices and pipes we just take what they have ready for us
		 * and return. Trying to do anything else with them runs the
		 * risk of failure.
		 */
		if ((res = read(arfd, buf, cnt)) > 0) {
			io_ok = 1;
			return(res);
		}
		break;
	}

	/*
	 * We are in trouble at this point, something is broken...
	 */
	lstrval = res;
	if (res < 0)
		syswarn(1, errno, "Failed read on archive volume %d", arvol);
	else
		paxwarn(0, "End of archive volume %d reached", arvol);
	return(res);
}