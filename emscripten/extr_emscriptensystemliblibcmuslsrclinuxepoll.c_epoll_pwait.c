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
struct epoll_event {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_epoll_pwait ; 
 int _NSIG ; 
 int __syscall (int /*<<< orphan*/ ,int,struct epoll_event*,int,int,int /*<<< orphan*/  const*,int) ; 
 int __syscall_ret (int) ; 

int epoll_pwait(int fd, struct epoll_event *ev, int cnt, int to, const sigset_t *sigs)
{
	int r = __syscall(SYS_epoll_pwait, fd, ev, cnt, to, sigs, _NSIG/8);
#ifdef SYS_epoll_wait
	if (r==-ENOSYS && !sigs) r = __syscall(SYS_epoll_wait, fd, ev, cnt, to);
#endif
	return __syscall_ret(r);
}