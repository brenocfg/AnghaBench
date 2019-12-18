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
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ write (int,char*,int) ; 

void
file_flush(int fd, char *fname, int isempt)
{
	static char blnk[] = "\0";

	/*
	 * silly test, but make sure we are only called when the last block is
	 * filled with all zeros.
	 */
	if (!isempt)
		return;

	/*
	 * move back one byte and write a zero
	 */
	if (lseek(fd, (off_t)-1, SEEK_CUR) < 0) {
		syswarn(1, errno, "Failed seek on file %s", fname);
		return;
	}

	if (write(fd, blnk, 1) < 0)
		syswarn(1, errno, "Failed write to file %s", fname);
	return;
}