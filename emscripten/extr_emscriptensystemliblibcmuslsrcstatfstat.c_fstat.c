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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int EBADF ; 
 struct stat* F_GETFD ; 
 int /*<<< orphan*/  SYS_fcntl ; 
 int /*<<< orphan*/  SYS_fstat ; 
 int /*<<< orphan*/  SYS_fstatat ; 
 int /*<<< orphan*/  __procfdname (char*,int) ; 
 int __syscall (int /*<<< orphan*/ ,int,struct stat*) ; 
 int __syscall_ret (int) ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct stat*,int /*<<< orphan*/ ) ; 

int fstat(int fd, struct stat *st)
{
	int ret = __syscall(SYS_fstat, fd, st);
	if (ret != -EBADF || __syscall(SYS_fcntl, fd, F_GETFD) < 0)
		return __syscall_ret(ret);

	char buf[15+3*sizeof(int)];
	__procfdname(buf, fd);
#ifdef SYS_stat
	return syscall(SYS_stat, buf, st);
#else
	return syscall(SYS_fstatat, AT_FDCWD, buf, st, 0);
#endif
}