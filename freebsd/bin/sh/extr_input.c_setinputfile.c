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

/* Variables and functions */
 int ENOENT ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  F_DUPFD_CLOEXEC ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  errorwithstatus (int,char*,char const*,int /*<<< orphan*/ ) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  setinputfd (int,int) ; 
 int /*<<< orphan*/  strerror (int) ; 

void
setinputfile(const char *fname, int push)
{
	int e;
	int fd;
	int fd2;

	INTOFF;
	if ((fd = open(fname, O_RDONLY | O_CLOEXEC)) < 0) {
		e = errno;
		errorwithstatus(e == ENOENT || e == ENOTDIR ? 127 : 126,
		    "cannot open %s: %s", fname, strerror(e));
	}
	if (fd < 10) {
		fd2 = fcntl(fd, F_DUPFD_CLOEXEC, 10);
		close(fd);
		if (fd2 < 0)
			error("Out of file descriptors");
		fd = fd2;
	}
	setinputfd(fd, push);
	INTON;
}