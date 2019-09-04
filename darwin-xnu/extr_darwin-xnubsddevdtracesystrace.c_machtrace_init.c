#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ stsy_underlying; } ;
typedef  TYPE_1__ machtrace_sysent_t ;
struct TYPE_9__ {scalar_t__ mach_trap_function; } ;
typedef  TYPE_2__ mach_trap_t ;
typedef  scalar_t__ mach_call_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 scalar_t__ LOADABLE_SYSCALL (TYPE_2__ const*) ; 
 int /*<<< orphan*/  LOADED_SYSCALL (TYPE_2__ const*) ; 
 int NSYSCALL ; 
 scalar_t__ dtrace_machtrace_syscall ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
machtrace_init(const mach_trap_t *actual, machtrace_sysent_t **interposed)
{
	machtrace_sysent_t *msysent = *interposed;
	int i;

	if (msysent == NULL) {
		*interposed = msysent = kmem_zalloc(sizeof (machtrace_sysent_t) *
				NSYSCALL, KM_SLEEP);
	}

	for (i = 0; i < NSYSCALL; i++) {
		const mach_trap_t *a = &actual[i];
		machtrace_sysent_t *s = &msysent[i];

		if (LOADABLE_SYSCALL(a) && !LOADED_SYSCALL(a))
			continue;

		if (a->mach_trap_function == (mach_call_t)(dtrace_machtrace_syscall))
			continue;

		s->stsy_underlying = a->mach_trap_function;
	}
}