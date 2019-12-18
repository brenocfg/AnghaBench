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
typedef  scalar_t__ off_t ;
struct TYPE_2__ {scalar_t__ st_size; } ;

/* Variables and functions */
 scalar_t__ ISREG ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  arfd ; 
 TYPE_1__ arsb ; 
 scalar_t__ artyp ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int lstrval ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*) ; 

int
ar_fow(off_t sksz, off_t *skipped)
{
	off_t cpos;
	off_t mpos;

	*skipped = 0;
	if (sksz <= 0)
		return(0);

	/*
	 * we cannot move forward at EOF or error
	 */
	if (lstrval <= 0)
		return(lstrval);

	/*
	 * Safer to read forward on devices where it is hard to find the end of
	 * the media without reading to it. With tapes we cannot be sure of the
	 * number of physical blocks to skip (we do not know physical block
	 * size at this point), so we must only read forward on tapes!
	 */
	if (artyp != ISREG)
		return(0);

	/*
	 * figure out where we are in the archive
	 */
	if ((cpos = lseek(arfd, (off_t)0L, SEEK_CUR)) >= 0) {
		/*
	 	 * we can be asked to move farther than there are bytes in this
		 * volume, if so, just go to file end and let normal buf_fill()
		 * deal with the end of file (it will go to next volume by
		 * itself)
	 	 */
		if ((mpos = cpos + sksz) > arsb.st_size) {
			*skipped = arsb.st_size - cpos;
			mpos = arsb.st_size;
		} else
			*skipped = sksz;
		if (lseek(arfd, mpos, SEEK_SET) >= 0)
			return(0);
	}
	syswarn(1, errno, "Forward positioning operation on archive failed");
	lstrval = -1;
	return(-1);
}