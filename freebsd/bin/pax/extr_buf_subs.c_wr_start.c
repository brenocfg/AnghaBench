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
struct TYPE_2__ {size_t bsz; } ;

/* Variables and functions */
 size_t BLKMULT ; 
 size_t MAXBLK ; 
 size_t MAXBLK_POSIX ; 
 scalar_t__ ar_next () ; 
 scalar_t__ ar_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arcname ; 
 size_t blksz ; 
 void* buf ; 
 void* bufend ; 
 int /*<<< orphan*/ * bufmem ; 
 void* bufpt ; 
 TYPE_1__* frmt ; 
 int /*<<< orphan*/  paxwarn (int,char*,size_t,size_t) ; 
 size_t rdblksz ; 
 size_t wrblksz ; 
 scalar_t__ wrcnt ; 

int
wr_start(void)
{
	buf = &(bufmem[BLKMULT]);
	/*
	 * Check to make sure the write block size meets pax specs. If the user
	 * does not specify a blocksize, we use the format default blocksize.
	 * We must be picky on writes, so we do not allow the user to create an
	 * archive that might be hard to read elsewhere. If all ok, we then
	 * open the first archive volume
	 */
	if (!wrblksz)
		wrblksz = frmt->bsz;
	if (wrblksz > MAXBLK) {
		paxwarn(1, "Write block size of %d too large, maximum is: %d",
			wrblksz, MAXBLK);
		return(-1);
	}
	if (wrblksz % BLKMULT) {
		paxwarn(1, "Write block size of %d is not a %d byte multiple",
		    wrblksz, BLKMULT);
		return(-1);
	}
	if (wrblksz > MAXBLK_POSIX) {
		paxwarn(0, "Write block size of %d larger than POSIX max %d, archive may not be portable",
			wrblksz, MAXBLK_POSIX);
		return(-1);
	}

	/*
	 * we only allow wrblksz to be used with all archive operations
	 */
	blksz = rdblksz = wrblksz;
	if ((ar_open(arcname) < 0) && (ar_next() < 0))
		return(-1);
	wrcnt = 0;
	bufend = buf + wrblksz;
	bufpt = buf;
	return(0);
}