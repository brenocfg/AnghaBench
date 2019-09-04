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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int EBADF ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  SYS_fchown ; 
 int /*<<< orphan*/  SYS_fchownat ; 
 int /*<<< orphan*/  SYS_fcntl ; 
 int /*<<< orphan*/  __procfdname (char*,int) ; 
 int __syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 
 int __syscall_ret (int) ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fchown(int fd, uid_t uid, gid_t gid)
{
	int ret = __syscall(SYS_fchown, fd, uid, gid);
	if (ret != -EBADF || __syscall(SYS_fcntl, fd, F_GETFD) < 0)
		return __syscall_ret(ret);

	char buf[15+3*sizeof(int)];
	__procfdname(buf, fd);
#ifdef SYS_chown
	return syscall(SYS_chown, buf, uid, gid);
#else
	return syscall(SYS_fchownat, AT_FDCWD, buf, uid, gid);
#endif

}