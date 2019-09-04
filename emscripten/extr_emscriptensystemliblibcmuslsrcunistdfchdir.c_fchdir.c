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
 int EBADF ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  SYS_chdir ; 
 int /*<<< orphan*/  SYS_fchdir ; 
 int /*<<< orphan*/  SYS_fcntl ; 
 int /*<<< orphan*/  __procfdname (char*,int) ; 
 int __syscall (int /*<<< orphan*/ ,int,...) ; 
 int __syscall_ret (int) ; 
 int syscall (int /*<<< orphan*/ ,char*) ; 

int fchdir(int fd)
{
	int ret = __syscall(SYS_fchdir, fd);
	if (ret != -EBADF || __syscall(SYS_fcntl, fd, F_GETFD) < 0)
		return __syscall_ret(ret);

	char buf[15+3*sizeof(int)];
	__procfdname(buf, fd);
	return syscall(SYS_chdir, buf);
}