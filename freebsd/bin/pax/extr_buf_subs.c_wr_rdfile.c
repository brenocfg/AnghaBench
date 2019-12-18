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
struct stat {scalar_t__ st_mtime; } ;
typedef  long off_t ;
struct TYPE_4__ {long st_size; scalar_t__ st_mtime; } ;
struct TYPE_5__ {int /*<<< orphan*/  org_name; TYPE_1__ sb; } ;
typedef  TYPE_2__ ARCHD ;

/* Variables and functions */
 int MIN (int,long) ; 
 int /*<<< orphan*/  blksz ; 
 int buf_flush (int /*<<< orphan*/ ) ; 
 int bufend ; 
 int bufpt ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  paxwarn (int,char*,int /*<<< orphan*/ ) ; 
 int read (int,int,int) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
wr_rdfile(ARCHD *arcn, int ifd, off_t *left)
{
	int cnt;
	int res = 0;
	off_t size = arcn->sb.st_size;
	struct stat sb;

	/*
	 * while there are more bytes to write
	 */
	while (size > 0L) {
		cnt = bufend - bufpt;
		if ((cnt <= 0) && ((cnt = buf_flush(blksz)) < 0)) {
			*left = size;
			return(-1);
		}
		cnt = MIN(cnt, size);
		if ((res = read(ifd, bufpt, cnt)) <= 0)
			break;
		size -= res;
		bufpt += res;
	}

	/*
	 * better check the file did not change during this operation
	 * or the file read failed.
	 */
	if (res < 0)
		syswarn(1, errno, "Read fault on %s", arcn->org_name);
	else if (size != 0L)
		paxwarn(1, "File changed size during read %s", arcn->org_name);
	else if (fstat(ifd, &sb) < 0)
		syswarn(1, errno, "Failed stat on %s", arcn->org_name);
	else if (arcn->sb.st_mtime != sb.st_mtime)
		paxwarn(1, "File %s was modified during copy to archive",
			arcn->org_name);
	*left = size;
	return(0);
}