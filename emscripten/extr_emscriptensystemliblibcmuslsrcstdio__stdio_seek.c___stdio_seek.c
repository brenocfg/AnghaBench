#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_lseek ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

off_t __stdio_seek(FILE *f, off_t off, int whence)
{
	off_t ret;
#ifdef SYS__llseek
	if (syscall(SYS__llseek, f->fd, off>>32, off, &ret, whence)<0)
		ret = -1;
#else
	ret = syscall(SYS_lseek, f->fd, off, whence);
#endif
	return ret;
}