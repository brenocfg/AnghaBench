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
 int /*<<< orphan*/  SYS_inotify_init1 ; 
 int __syscall (int /*<<< orphan*/ ,int) ; 
 int __syscall_ret (int) ; 

int inotify_init1(int flags)
{
	int r = __syscall(SYS_inotify_init1, flags);
#ifdef SYS_inotify_init
	if (r==-ENOSYS && !flags) r = __syscall(SYS_inotify_init);
#endif
	return __syscall_ret(r);
}