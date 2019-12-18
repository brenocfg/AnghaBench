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
struct stat {int st_mode; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_mtime; } ;
typedef  int /*<<< orphan*/  dblk ;
struct TYPE_2__ {int nlen; int mode; int frc_mode; int /*<<< orphan*/  atime; int /*<<< orphan*/  mtime; int /*<<< orphan*/  npos; } ;
typedef  TYPE_1__ DIRDATA ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  dircnt ; 
 scalar_t__ dirfd ; 
 int /*<<< orphan*/  lseek (scalar_t__,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paxwarn (int,char*,char*) ; 
 int write (scalar_t__,char*,int) ; 

void
add_dir(char *name, int nlen, struct stat *psb, int frc_mode)
{
	DIRDATA dblk;

	if (dirfd < 0)
		return;

	/*
	 * get current position (where file name will start) so we can store it
	 * in the trailer
	 */
	if ((dblk.npos = lseek(dirfd, 0L, SEEK_CUR)) < 0) {
		paxwarn(1,"Unable to store mode and times for directory: %s",name);
		return;
	}

	/*
	 * write the file name followed by the trailer
	 */
	dblk.nlen = nlen + 1;
	dblk.mode = psb->st_mode & 0xffff;
	dblk.mtime = psb->st_mtime;
	dblk.atime = psb->st_atime;
	dblk.frc_mode = frc_mode;
	if ((write(dirfd, name, dblk.nlen) == dblk.nlen) &&
	    (write(dirfd, (char *)&dblk, sizeof(dblk)) == sizeof(dblk))) {
		++dircnt;
		return;
	}

	paxwarn(1,"Unable to store mode and times for created directory: %s",name);
	return;
}