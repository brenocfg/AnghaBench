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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int O_CLOEXEC ; 
 int /*<<< orphan*/  SYS_close ; 
 int /*<<< orphan*/  SYS_fcntl ; 
 int /*<<< orphan*/ * __fdopen (int,char const*) ; 
 int __fmodeflags (char const*) ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strchr (char*,char const) ; 
 int sys_open (char const*,int,int) ; 

FILE *fopen(const char *restrict filename, const char *restrict mode)
{
	FILE *f;
	int fd;
	int flags;

	/* Check for valid initial mode character */
	if (!strchr("rwa", *mode)) {
		errno = EINVAL;
		return 0;
	}

	/* Compute the flags to pass to open() */
	flags = __fmodeflags(mode);

	fd = sys_open(filename, flags, 0666);
	if (fd < 0) return 0;
	if (flags & O_CLOEXEC)
		__syscall(SYS_fcntl, fd, F_SETFD, FD_CLOEXEC);

	f = __fdopen(fd, mode);
	if (f) return f;

	__syscall(SYS_close, fd);
	return 0;
}