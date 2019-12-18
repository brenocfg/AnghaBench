#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct exit_args {scalar_t__ rval; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_4__ {int p_xhighbits; } ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  W_EXITCODE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_exception_return () ; 

__attribute__((noreturn))
void
exit(proc_t p, struct exit_args *uap, int *retval)
{
	p->p_xhighbits = ((uint32_t)(uap->rval) & 0xFF000000) >> 24;
	exit1(p, W_EXITCODE(uap->rval, 0), retval);

	thread_exception_return();
	/* NOTREACHED */
	while (TRUE)
		thread_block(THREAD_CONTINUE_NULL);
	/* NOTREACHED */
}