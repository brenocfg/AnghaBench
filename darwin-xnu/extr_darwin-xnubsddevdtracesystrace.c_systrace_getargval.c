#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uthread_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;
struct TYPE_2__ {int /*<<< orphan*/ * t_dtrace_syscall_args; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_NOFAULT ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 int SYSTRACE_NARGS ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
systrace_getargval(void *arg, dtrace_id_t id, void *parg, int argno, int aframes)
{
#pragma unused(arg,id,parg,aframes)     /* __APPLE__ */
	uint64_t val = 0;
	uint64_t *uargs = NULL;

	uthread_t uthread = (uthread_t)get_bsdthread_info(current_thread());	

	if (uthread)
		uargs = uthread->t_dtrace_syscall_args;
	if (!uargs)
		return(0);
	if (argno < 0 || argno >= SYSTRACE_NARGS)
		return(0);

	DTRACE_CPUFLAG_SET(CPU_DTRACE_NOFAULT);
	val = uargs[argno];
	DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_NOFAULT);
	return (val);
}