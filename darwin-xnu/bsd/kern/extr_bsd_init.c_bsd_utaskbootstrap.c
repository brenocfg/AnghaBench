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
typedef  int /*<<< orphan*/  thread_t ;
struct uthread {scalar_t__ uu_sigmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  COALITION_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PROC_NULL ; 
 int /*<<< orphan*/  TASK_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  act_set_astbsd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cloneproc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_threadtask (int /*<<< orphan*/ ) ; 
 scalar_t__ initproc ; 
 int /*<<< orphan*/  kernproc ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ proc_find (int) ; 
 int /*<<< orphan*/  proc_signalend (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_transend (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_clear_return_wait (int /*<<< orphan*/ ) ; 

void
bsd_utaskbootstrap(void)
{
	thread_t thread;
	struct uthread *ut;

	/*
	 * Clone the bootstrap process from the kernel process, without
	 * inheriting either task characteristics or memory from the kernel;
	 */
	thread = cloneproc(TASK_NULL, COALITION_NULL, kernproc, FALSE, TRUE);

	/* Hold the reference as it will be dropped during shutdown */
	initproc = proc_find(1);				
#if __PROC_INTERNAL_DEBUG
	if (initproc == PROC_NULL)
		panic("bsd_utaskbootstrap: initproc not set\n");
#endif
	/*
	 * Since we aren't going back out the normal way to our parent,
	 * we have to drop the transition locks explicitly.
	 */
	proc_signalend(initproc, 0);
	proc_transend(initproc, 0);

	ut = (struct uthread *)get_bsdthread_info(thread);
	ut->uu_sigmask = 0;
	act_set_astbsd(thread);
	task_clear_return_wait(get_threadtask(thread));
}