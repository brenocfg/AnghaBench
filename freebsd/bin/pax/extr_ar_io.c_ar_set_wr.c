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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 scalar_t__ ISREG ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  arfd ; 
 scalar_t__ artyp ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ftruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wr_trail ; 

int
ar_set_wr(void)
{
	off_t cpos;

	/*
	 * we must make sure the trailer is rewritten on append, ar_next()
	 * will stop us if the archive containing the trailer was not written
	 */
	wr_trail = 0;

	/*
	 * Add any device dependent code as required here
	 */
	if (artyp != ISREG)
		return(0);
	/*
	 * Ok we have an archive in a regular file. If we were rewriting a
	 * file, we must get rid of all the stuff after the current offset
	 * (it was not written by pax).
	 */
	if (((cpos = lseek(arfd, (off_t)0L, SEEK_CUR)) < 0) ||
	    (ftruncate(arfd, cpos) < 0)) {
		syswarn(1, errno, "Unable to truncate archive file");
		return(-1);
	}
	return(0);
}