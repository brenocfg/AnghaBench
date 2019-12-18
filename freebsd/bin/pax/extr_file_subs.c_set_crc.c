#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  tbuf ;
struct stat {scalar_t__ st_mtime; } ;
typedef  scalar_t__ off_t ;
struct TYPE_4__ {scalar_t__ st_size; scalar_t__ st_mtime; scalar_t__ st_blksize; } ;
struct TYPE_5__ {long crc; int /*<<< orphan*/  org_name; TYPE_1__ sb; } ;
typedef  TYPE_2__ ARCHD ;

/* Variables and functions */
 int FILEBLK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paxwarn (int,char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
set_crc(ARCHD *arcn, int fd)
{
	int i;
	int res;
	off_t cpcnt = 0L;
	u_long size;
	unsigned long crc = 0L;
	char tbuf[FILEBLK];
	struct stat sb;

	if (fd < 0) {
		/*
		 * hmm, no fd, should never happen. well no crc then.
		 */
		arcn->crc = 0L;
		return(0);
	}

	if ((size = (u_long)arcn->sb.st_blksize) > (u_long)sizeof(tbuf))
		size = (u_long)sizeof(tbuf);

	/*
	 * read all the bytes we think that there are in the file. If the user
	 * is trying to archive an active file, forget this file.
	 */
	for(;;) {
		if ((res = read(fd, tbuf, size)) <= 0)
			break;
		cpcnt += res;
		for (i = 0; i < res; ++i)
			crc += (tbuf[i] & 0xff);
	}

	/*
	 * safety check. we want to avoid archiving files that are active as
	 * they can create inconsistent archive copies.
	 */
	if (cpcnt != arcn->sb.st_size)
		paxwarn(1, "File changed size %s", arcn->org_name);
	else if (fstat(fd, &sb) < 0)
		syswarn(1, errno, "Failed stat on %s", arcn->org_name);
	else if (arcn->sb.st_mtime != sb.st_mtime)
		paxwarn(1, "File %s was modified during read", arcn->org_name);
	else if (lseek(fd, (off_t)0L, SEEK_SET) < 0)
		syswarn(1, errno, "File rewind failed on: %s", arcn->org_name);
	else {
		arcn->crc = crc;
		return(0);
	}
	return(-1);
}