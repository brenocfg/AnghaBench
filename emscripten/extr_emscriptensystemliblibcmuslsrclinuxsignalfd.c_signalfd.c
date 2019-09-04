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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_signalfd4 ; 
 int _NSIG ; 
 int __syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int,int) ; 
 int __syscall_ret (int) ; 

int signalfd(int fd, const sigset_t *sigs, int flags)
{
	int ret = __syscall(SYS_signalfd4, fd, sigs, _NSIG/8, flags);
#ifdef SYS_signalfd
	if (ret != -ENOSYS) return __syscall_ret(ret);
	ret = __syscall(SYS_signalfd, fd, sigs, _NSIG/8);
	if (ret >= 0) {
		if (flags & SFD_CLOEXEC)
			__syscall(SYS_fcntl, ret, F_SETFD, FD_CLOEXEC);
		if (flags & SFD_NONBLOCK)
			__syscall(SYS_fcntl, ret, F_SETFL, O_NONBLOCK);
	}
#endif
	return __syscall_ret(ret);
}