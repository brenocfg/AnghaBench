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
 int ENOSYS ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SYS_fcntl ; 
 int /*<<< orphan*/  SYS_pipe2 ; 
 int __syscall (int /*<<< orphan*/ ,...) ; 
 int __syscall_ret (int) ; 
 int pipe (int*) ; 

int pipe2(int fd[2], int flag)
{
	if (!flag) return pipe(fd);
	int ret = __syscall(SYS_pipe2, fd, flag);
	if (ret != -ENOSYS) return __syscall_ret(ret);
	ret = pipe(fd);
	if (ret) return ret;
	if (flag & O_CLOEXEC) {
		__syscall(SYS_fcntl, fd[0], F_SETFD, FD_CLOEXEC);
		__syscall(SYS_fcntl, fd[1], F_SETFD, FD_CLOEXEC);
	}
	if (flag & O_NONBLOCK) {
		__syscall(SYS_fcntl, fd[0], F_SETFL, O_NONBLOCK);
		__syscall(SYS_fcntl, fd[1], F_SETFL, O_NONBLOCK);
	}
	return 0;
}