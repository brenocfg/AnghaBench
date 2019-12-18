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
struct mtop {int mt_count; int /*<<< orphan*/  mt_op; } ;
typedef  int off_t ;

/* Variables and functions */
#define  ISBLK 132 
#define  ISCHR 131 
#define  ISPIPE 130 
#define  ISREG 129 
#define  ISTAPE 128 
 int /*<<< orphan*/  MTBSR ; 
 int /*<<< orphan*/  MTIOCTOP ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  arfd ; 
 int artyp ; 
 int arvol ; 
 int /*<<< orphan*/  errno ; 
 int get_phys () ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtop*) ; 
 int lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int lstrval ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 int rdblksz ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,...) ; 

int
ar_rev(off_t sksz)
{
	off_t cpos;
	struct mtop mb;
	int phyblk;

	/*
	 * make sure we do not have try to reverse on a flawed archive
	 */
	if (lstrval < 0)
		return(lstrval);

	switch(artyp) {
	case ISPIPE:
		if (sksz <= 0)
			break;
		/*
		 * cannot go backwards on these critters
		 */
		paxwarn(1, "Reverse positioning on pipes is not supported.");
		lstrval = -1;
		return(-1);
	case ISREG:
	case ISBLK:
	case ISCHR:
	default:
		if (sksz <= 0)
			break;

		/*
		 * For things other than files, backwards movement has a very
		 * high probability of failure as we really do not know the
		 * true attributes of the device we are talking to (the device
		 * may not even have the ability to lseek() in any direction).
		 * First we figure out where we are in the archive.
		 */
		if ((cpos = lseek(arfd, (off_t)0L, SEEK_CUR)) < 0) {
			syswarn(1, errno,
			   "Unable to obtain current archive byte offset");
			lstrval = -1;
			return(-1);
		}

		/*
		 * we may try to go backwards past the start when the archive
		 * is only a single record. If this happens and we are on a
		 * multi volume archive, we need to go to the end of the
		 * previous volume and continue our movement backwards from
		 * there.
		 */
		if ((cpos -= sksz) < (off_t)0L) {
			if (arvol > 1) {
				/*
				 * this should never happen
				 */
				paxwarn(1,"Reverse position on previous volume.");
				lstrval = -1;
				return(-1);
			}
			cpos = (off_t)0L;
		}
		if (lseek(arfd, cpos, SEEK_SET) < 0) {
			syswarn(1, errno, "Unable to seek archive backwards");
			lstrval = -1;
			return(-1);
		}
		break;
	case ISTAPE:
		/*
	 	 * Calculate and move the proper number of PHYSICAL tape
		 * blocks. If the sksz is not an even multiple of the physical
		 * tape size, we cannot do the move (this should never happen).
		 * (We also cannot handler trailers spread over two vols).
		 * get_phys() also makes sure we are in front of the filemark.
	 	 */
		if ((phyblk = get_phys()) <= 0) {
			lstrval = -1;
			return(-1);
		}

		/*
		 * make sure future tape reads only go by physical tape block
		 * size (set rdblksz to the real size).
		 */
		rdblksz = phyblk;

		/*
		 * if no movement is required, just return (we must be after
		 * get_phys() so the physical blocksize is properly set)
		 */
		if (sksz <= 0)
			break;

		/*
		 * ok we have to move. Make sure the tape drive can do it.
		 */
		if (sksz % phyblk) {
			paxwarn(1,
			    "Tape drive unable to backspace requested amount");
			lstrval = -1;
			return(-1);
		}

		/*
		 * move backwards the requested number of bytes
		 */
		mb.mt_op = MTBSR;
		mb.mt_count = sksz/phyblk;
		if (ioctl(arfd, MTIOCTOP, &mb) < 0) {
			syswarn(1,errno, "Unable to backspace tape %d blocks.",
			    mb.mt_count);
			lstrval = -1;
			return(-1);
		}
		break;
	}
	lstrval = 1;
	return(0);
}