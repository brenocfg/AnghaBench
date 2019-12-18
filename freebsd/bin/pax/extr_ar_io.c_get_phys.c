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
struct mtop {int mt_count; void* mt_op; } ;
typedef  int /*<<< orphan*/  scbuf ;

/* Variables and functions */
 int MAXBLK ; 
 void* MTBSF ; 
 void* MTBSR ; 
 int /*<<< orphan*/  MTIOCTOP ; 
 int /*<<< orphan*/  arfd ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtop*) ; 
 int lstrval ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
get_phys(void)
{
	int padsz = 0;
	int res;
	int phyblk;
	struct mtop mb;
	char scbuf[MAXBLK];

	/*
	 * move to the file mark, and then back up one record and read it.
	 * this should tell us the physical record size the tape is using.
	 */
	if (lstrval == 1) {
		/*
		 * we know we are at file mark when we get back a 0 from
		 * read()
		 */
		while ((res = read(arfd, scbuf, sizeof(scbuf))) > 0)
			padsz += res;
		if (res < 0) {
			syswarn(1, errno, "Unable to locate tape filemark.");
			return(-1);
		}
	}

	/*
	 * move backwards over the file mark so we are at the end of the
	 * last record.
	 */
	mb.mt_op = MTBSF;
	mb.mt_count = 1;
	if (ioctl(arfd, MTIOCTOP, &mb) < 0) {
		syswarn(1, errno, "Unable to backspace over tape filemark.");
		return(-1);
	}

	/*
	 * move backwards so we are in front of the last record and read it to
	 * get physical tape blocksize.
	 */
	mb.mt_op = MTBSR;
	mb.mt_count = 1;
	if (ioctl(arfd, MTIOCTOP, &mb) < 0) {
		syswarn(1, errno, "Unable to backspace over last tape block.");
		return(-1);
	}
	if ((phyblk = read(arfd, scbuf, sizeof(scbuf))) <= 0) {
		syswarn(1, errno, "Cannot determine archive tape blocksize.");
		return(-1);
	}

	/*
	 * read forward to the file mark, then back up in front of the filemark
	 * (this is a bit paranoid, but should be safe to do).
	 */
	while ((res = read(arfd, scbuf, sizeof(scbuf))) > 0)
		;
	if (res < 0) {
		syswarn(1, errno, "Unable to locate tape filemark.");
		return(-1);
	}
	mb.mt_op = MTBSF;
	mb.mt_count = 1;
	if (ioctl(arfd, MTIOCTOP, &mb) < 0) {
		syswarn(1, errno, "Unable to backspace over tape filemark.");
		return(-1);
	}

	/*
	 * set lstrval so we know that the filemark has not been seen
	 */
	lstrval = 1;

	/*
	 * return if there was no padding
	 */
	if (padsz == 0)
		return(phyblk);

	/*
	 * make sure we can move backwards over the padding. (this should
	 * never fail).
	 */
	if (padsz % phyblk) {
		paxwarn(1, "Tape drive unable to backspace requested amount");
		return(-1);
	}

	/*
	 * move backwards over the padding so the head is where it was when
	 * we were first called (if required).
	 */
	mb.mt_op = MTBSR;
	mb.mt_count = padsz/phyblk;
	if (ioctl(arfd, MTIOCTOP, &mb) < 0) {
		syswarn(1,errno,"Unable to backspace tape over %d pad blocks",
		    mb.mt_count);
		return(-1);
	}
	return(phyblk);
}