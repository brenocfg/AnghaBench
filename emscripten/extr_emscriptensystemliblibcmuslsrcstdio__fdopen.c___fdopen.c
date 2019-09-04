#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct winsize {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  threaded; } ;
struct TYPE_8__ {int flags; int fd; unsigned char* buf; int buf_size; char lbf; int lock; int /*<<< orphan*/  close; int /*<<< orphan*/  seek; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  EINVAL ; 
 char EOF ; 
 struct winsize* FD_CLOEXEC ; 
 int F_APP ; 
 int /*<<< orphan*/  F_GETFL ; 
 int F_NORD ; 
 int F_NOWR ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_APPEND ; 
 int /*<<< orphan*/  SYS_fcntl ; 
 int /*<<< orphan*/  SYS_ioctl ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int UNGET ; 
 TYPE_1__* __ofl_add (TYPE_1__*) ; 
 int /*<<< orphan*/  __stdio_close ; 
 int /*<<< orphan*/  __stdio_read ; 
 int /*<<< orphan*/  __stdio_seek ; 
 int /*<<< orphan*/  __stdio_write ; 
 int __syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_4__ libc ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strchr (char const*,char const) ; 

FILE *__fdopen(int fd, const char *mode)
{
	FILE *f;
	struct winsize wsz;

	/* Check for valid initial mode character */
	if (!strchr("rwa", *mode)) {
		errno = EINVAL;
		return 0;
	}

	/* Allocate FILE+buffer or fail */
	if (!(f=malloc(sizeof *f + UNGET + BUFSIZ))) return 0;

	/* Zero-fill only the struct, not the buffer */
	memset(f, 0, sizeof *f);

	/* Impose mode restrictions */
	if (!strchr(mode, '+')) f->flags = (*mode == 'r') ? F_NOWR : F_NORD;

	/* Apply close-on-exec flag */
	if (strchr(mode, 'e')) __syscall(SYS_fcntl, fd, F_SETFD, FD_CLOEXEC);

	/* Set append mode on fd if opened for append */
	if (*mode == 'a') {
		int flags = __syscall(SYS_fcntl, fd, F_GETFL);
		if (!(flags & O_APPEND))
			__syscall(SYS_fcntl, fd, F_SETFL, flags | O_APPEND);
		f->flags |= F_APP;
	}

	f->fd = fd;
	f->buf = (unsigned char *)f + sizeof *f + UNGET;
	f->buf_size = BUFSIZ;

	/* Activate line buffered mode for terminals */
	f->lbf = EOF;
	if (!(f->flags & F_NOWR) && !__syscall(SYS_ioctl, fd, TIOCGWINSZ, &wsz))
		f->lbf = '\n';

	/* Initialize op ptrs. No problem if some are unneeded. */
	f->read = __stdio_read;
	f->write = __stdio_write;
	f->seek = __stdio_seek;
	f->close = __stdio_close;

	if (!libc.threaded) f->lock = -1;

	/* Add new FILE to open file list */
	return __ofl_add(f);
}