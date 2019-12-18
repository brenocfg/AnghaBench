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
struct stat {size_t st_blksize; int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZE_MAX ; 
 size_t BUFSIZE_SMALL ; 
 size_t MAX (size_t,size_t) ; 
 int MAXPHYS ; 
 size_t MIN (int /*<<< orphan*/ ,int) ; 
 long PHYSPAGES_THRESHOLD ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  _SC_PHYS_PAGES ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  filename ; 
 int fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 char* malloc (size_t) ; 
 scalar_t__ read (int,char*,size_t) ; 
 int rval ; 
 int /*<<< orphan*/  stdout ; 
 long sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,char*,size_t) ; 

__attribute__((used)) static void
raw_cat(int rfd)
{
	long pagesize;
	int off, wfd;
	ssize_t nr, nw;
	static size_t bsize;
	static char *buf = NULL;
	struct stat sbuf;

	wfd = fileno(stdout);
	if (buf == NULL) {
		if (fstat(wfd, &sbuf))
			err(1, "stdout");
		if (S_ISREG(sbuf.st_mode)) {
			/* If there's plenty of RAM, use a large copy buffer */
			if (sysconf(_SC_PHYS_PAGES) > PHYSPAGES_THRESHOLD)
				bsize = MIN(BUFSIZE_MAX, MAXPHYS * 8);
			else
				bsize = BUFSIZE_SMALL;
		} else {
			bsize = sbuf.st_blksize;
			pagesize = sysconf(_SC_PAGESIZE);
			if (pagesize > 0)
				bsize = MAX(bsize, (size_t)pagesize);
		}
		if ((buf = malloc(bsize)) == NULL)
			err(1, "malloc() failure of IO buffer");
	}
	while ((nr = read(rfd, buf, bsize)) > 0)
		for (off = 0; nr; nr -= nw, off += nw)
			if ((nw = write(wfd, buf + off, (size_t)nr)) < 0)
				err(1, "stdout");
	if (nr < 0) {
		warn("%s", filename);
		rval = 1;
	}
}