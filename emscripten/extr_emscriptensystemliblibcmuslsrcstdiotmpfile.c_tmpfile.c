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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int MAXTRIES ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SYS_close ; 
 int /*<<< orphan*/  SYS_unlinkat ; 
 int /*<<< orphan*/ * __fdopen (int,char*) ; 
 int /*<<< orphan*/  __randname (char*) ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int,...) ; 
 int sys_open (char*,int,int) ; 

FILE *tmpfile(void)
{
	char s[] = "/tmp/tmpfile_XXXXXX";
	int fd;
	FILE *f;
	int try;
	for (try=0; try<MAXTRIES; try++) {
		__randname(s+13);
		fd = sys_open(s, O_RDWR|O_CREAT|O_EXCL, 0600);
		if (fd >= 0) {
#ifdef SYS_unlink
			__syscall(SYS_unlink, s);
#else
			__syscall(SYS_unlinkat, AT_FDCWD, s, 0);
#endif
			f = __fdopen(fd, "w+");
			if (!f) __syscall(SYS_close, fd);
			return f;
		}
	}
	return 0;
}