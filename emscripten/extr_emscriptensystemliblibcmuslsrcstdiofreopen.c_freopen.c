#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int fd; int flags; int /*<<< orphan*/  close; int /*<<< orphan*/  seek; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  FLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCK (TYPE_1__*) ; 
 int F_PERM ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  SYS_fcntl ; 
 scalar_t__ __dup3 (int,int,int) ; 
 int __fmodeflags (char const*) ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (TYPE_1__*) ; 
 int /*<<< orphan*/  fflush (TYPE_1__*) ; 
 TYPE_1__* fopen (char const*,char const*) ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

FILE *freopen(const char *restrict filename, const char *restrict mode, FILE *restrict f)
{
	int fl = __fmodeflags(mode);
	FILE *f2;

	FLOCK(f);

	fflush(f);

	if (!filename) {
		if (fl&O_CLOEXEC)
			__syscall(SYS_fcntl, f->fd, F_SETFD, FD_CLOEXEC);
		fl &= ~(O_CREAT|O_EXCL|O_CLOEXEC);
		if (syscall(SYS_fcntl, f->fd, F_SETFL, fl) < 0)
			goto fail;
	} else {
		f2 = fopen(filename, mode);
		if (!f2) goto fail;
		if (f2->fd == f->fd) f2->fd = -1; /* avoid closing in fclose */
		else if (__dup3(f2->fd, f->fd, fl&O_CLOEXEC)<0) goto fail2;

		f->flags = (f->flags & F_PERM) | f2->flags;
		f->read = f2->read;
		f->write = f2->write;
		f->seek = f2->seek;
		f->close = f2->close;

		fclose(f2);
	}

	FUNLOCK(f);
	return f;

fail2:
	fclose(f2);
fail:
	fclose(f);
	return NULL;
}