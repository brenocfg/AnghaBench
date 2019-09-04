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
 int /*<<< orphan*/  SYS_getcpu ; 
 int __syscall (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __syscall_ret (int) ; 

int sched_getcpu(void)
{
	int r;
	unsigned cpu;

#ifdef VDSO_GETCPU_SYM
	getcpu_f f = (getcpu_f)vdso_func;
	if (f) {
		r = f(&cpu, 0, 0);
		if (!r) return cpu;
		if (r != -ENOSYS) return __syscall_ret(r);
	}
#endif

	r = __syscall(SYS_getcpu, &cpu, 0, 0);
	if (!r) return cpu;
	return __syscall_ret(r);
}