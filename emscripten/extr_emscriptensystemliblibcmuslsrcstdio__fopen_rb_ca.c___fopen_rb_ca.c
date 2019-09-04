#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ fd; int flags; unsigned char* buf; int buf_size; int lock; int /*<<< orphan*/  close; int /*<<< orphan*/  seek; int /*<<< orphan*/  read; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int F_NOWR ; 
 int F_PERM ; 
 int /*<<< orphan*/  F_SETFD ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SYS_fcntl ; 
 int UNGET ; 
 int /*<<< orphan*/  __stdio_close ; 
 int /*<<< orphan*/  __stdio_read ; 
 int /*<<< orphan*/  __stdio_seek ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sys_open (char const*,int) ; 

FILE *__fopen_rb_ca(const char *filename, FILE *f, unsigned char *buf, size_t len)
{
	memset(f, 0, sizeof *f);

	f->fd = sys_open(filename, O_RDONLY|O_CLOEXEC);
	if (f->fd < 0) return 0;
	__syscall(SYS_fcntl, f->fd, F_SETFD, FD_CLOEXEC);

	f->flags = F_NOWR | F_PERM;
	f->buf = buf + UNGET;
	f->buf_size = len - UNGET;
	f->read = __stdio_read;
	f->seek = __stdio_seek;
	f->close = __stdio_close;
	f->lock = -1;

	return f;
}