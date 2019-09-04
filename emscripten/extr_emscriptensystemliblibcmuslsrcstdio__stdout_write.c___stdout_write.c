#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct winsize {int dummy; } ;
struct TYPE_4__ {size_t (* write ) (TYPE_1__*,unsigned char const*,size_t) ;int flags; int lbf; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int F_SVB ; 
 int /*<<< orphan*/  SYS_ioctl ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 size_t __stdio_write (TYPE_1__*,unsigned char const*,size_t) ; 
 scalar_t__ __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 

size_t __stdout_write(FILE *f, const unsigned char *buf, size_t len)
{
	struct winsize wsz;
	f->write = __stdio_write;
	if (!(f->flags & F_SVB) && __syscall(SYS_ioctl, f->fd, TIOCGWINSZ, &wsz))
		f->lbf = -1;
	return __stdio_write(f, buf, len);
}