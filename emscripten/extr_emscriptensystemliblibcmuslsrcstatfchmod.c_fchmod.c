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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int EBADF ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  SYS_fchmod ; 
 int /*<<< orphan*/  SYS_fchmodat ; 
 int /*<<< orphan*/  SYS_fcntl ; 
 int /*<<< orphan*/  __procfdname (char*,int) ; 
 int __syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int __syscall_ret (int) ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int fchmod(int fd, mode_t mode)
{
	int ret = __syscall(SYS_fchmod, fd, mode);
	if (ret != -EBADF || __syscall(SYS_fcntl, fd, F_GETFD) < 0)
		return __syscall_ret(ret);

	char buf[15+3*sizeof(int)];
	__procfdname(buf, fd);
#ifdef SYS_chmod
	return syscall(SYS_chmod, buf, mode);
#else
	return syscall(SYS_fchmodat, AT_FDCWD, buf, mode);
#endif
}