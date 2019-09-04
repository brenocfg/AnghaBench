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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int SOCK_CLOEXEC ; 
 int SOCK_NONBLOCK ; 
 int /*<<< orphan*/  SYS_fcntl ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int accept (int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int socketcall_cp (int (*) (int,struct sockaddr*,int /*<<< orphan*/ *,int),int,struct sockaddr*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int accept4(int fd, struct sockaddr *restrict addr, socklen_t *restrict len, int flg)
{
	if (!flg) return accept(fd, addr, len);
	int ret = socketcall_cp(accept4, fd, addr, len, flg, 0, 0);
	if (ret>=0 || (errno != ENOSYS && errno != EINVAL)) return ret;
	ret = accept(fd, addr, len);
	if (ret<0) return ret;
	if (flg & SOCK_CLOEXEC)
		__syscall(SYS_fcntl, ret, F_SETFD, FD_CLOEXEC);
	if (flg & SOCK_NONBLOCK)
		__syscall(SYS_fcntl, ret, F_SETFL, O_NONBLOCK);
	return ret;
}