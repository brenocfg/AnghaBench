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
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  SYS_dup3 ; 
 int /*<<< orphan*/  SYS_fcntl ; 
 int __syscall (int /*<<< orphan*/ ,int,int,...) ; 

__attribute__((used)) static int __sys_dup2(int old, int new)
{
#ifdef SYS_dup2
	return __syscall(SYS_dup2, old, new);
#else
	if (old==new) {
		int r = __syscall(SYS_fcntl, old, F_GETFD);
		return r<0 ? r : old;
	} else {
		return __syscall(SYS_dup3, old, new, 0);
	}
#endif
}