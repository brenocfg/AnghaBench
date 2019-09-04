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
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  SYS_dup3 ; 
 int /*<<< orphan*/  SYS_fcntl ; 
 int __syscall (int /*<<< orphan*/ ,int,int,...) ; 
 int __syscall_ret (int) ; 

int dup2(int old, int new)
{
	int r;
#ifdef SYS_dup2
	while ((r=__syscall(SYS_dup2, old, new))==-EBUSY);
#else
	if (old==new) {
		r = __syscall(SYS_fcntl, old, F_GETFD);
		if (r >= 0) return old;
	} else {
		while ((r=__syscall(SYS_dup3, old, new, 0))==-EBUSY);
	}
#endif
	return __syscall_ret(r);
}