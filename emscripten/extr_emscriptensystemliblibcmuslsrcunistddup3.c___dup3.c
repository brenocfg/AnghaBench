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
 int EBUSY ; 
 int /*<<< orphan*/  SYS_dup3 ; 
 int __syscall (int /*<<< orphan*/ ,int,int,int) ; 
 int __syscall_ret (int) ; 

int __dup3(int old, int new, int flags)
{
	int r;
#ifdef SYS_dup2
	if (old==new) return __syscall_ret(-EINVAL);
	if (flags & O_CLOEXEC) {
		while ((r=__syscall(SYS_dup3, old, new, flags))==-EBUSY);
		if (r!=-ENOSYS) return __syscall_ret(r);
	}
	while ((r=__syscall(SYS_dup2, old, new))==-EBUSY);
	if (flags & O_CLOEXEC) __syscall(SYS_fcntl, new, F_SETFD, FD_CLOEXEC);
#else
	while ((r=__syscall(SYS_dup3, old, new, flags))==-EBUSY);
#endif
	return __syscall_ret(r);
}