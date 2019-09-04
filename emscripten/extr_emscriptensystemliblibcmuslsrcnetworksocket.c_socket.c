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
 scalar_t__ EINVAL ; 
 scalar_t__ EPROTONOSUPPORT ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int SOCK_CLOEXEC ; 
 int SOCK_NONBLOCK ; 
 int /*<<< orphan*/  SYS_fcntl ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int socketcall (int (*) (int,int,int),int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int socket(int domain, int type, int protocol)
{
	int s = socketcall(socket, domain, type, protocol, 0, 0, 0);
	if (s<0 && (errno==EINVAL || errno==EPROTONOSUPPORT)
	    && (type&(SOCK_CLOEXEC|SOCK_NONBLOCK))) {
		s = socketcall(socket, domain,
			type & ~(SOCK_CLOEXEC|SOCK_NONBLOCK),
			protocol, 0, 0, 0);
		if (s < 0) return s;
		if (type & SOCK_CLOEXEC)
			__syscall(SYS_fcntl, s, F_SETFD, FD_CLOEXEC);
		if (type & SOCK_NONBLOCK)
			__syscall(SYS_fcntl, s, F_SETFL, O_NONBLOCK);
	}
	return s;
}