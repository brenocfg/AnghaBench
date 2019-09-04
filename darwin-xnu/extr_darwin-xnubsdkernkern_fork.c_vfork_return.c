#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uthread_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  task_t ;
typedef  TYPE_2__* proc_t ;
typedef  int int32_t ;
struct TYPE_10__ {scalar_t__ p_vforkact; int /*<<< orphan*/  p_lflag; } ;
struct TYPE_9__ {int uu_flag; int /*<<< orphan*/  uu_vforkmask; int /*<<< orphan*/  uu_sigmask; scalar_t__ uu_proc; scalar_t__ uu_userstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_LINVFORK ; 
 int UT_SETUID ; 
 int UT_VFORK ; 
 int UT_WASSETUID ; 
 int /*<<< orphan*/  act_thread_catt (scalar_t__) ; 
 int /*<<< orphan*/  current_thread () ; 
 TYPE_2__* get_bsdtask_info (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_threadtask (scalar_t__) ; 
 int /*<<< orphan*/  proc_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  proc_vfork_end (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_set_parent (int /*<<< orphan*/ ,int) ; 

void
vfork_return(proc_t child_proc, int32_t *retval, int rval)
{
	task_t parent_task = get_threadtask(child_proc->p_vforkact);
	proc_t parent_proc = get_bsdtask_info(parent_task);
	thread_t th = current_thread();
	uthread_t uth = get_bsdthread_info(th);
	
	act_thread_catt(uth->uu_userstate);

	/* clear vfork state in parent proc structure */
	proc_vfork_end(parent_proc);

	/* REPATRIATE PARENT TASK, THREAD, UTHREAD */
	uth->uu_userstate = 0;
	uth->uu_flag &= ~UT_VFORK;
	/* restore thread-set-id state */
	if (uth->uu_flag & UT_WASSETUID) {
		uth->uu_flag |= UT_SETUID;
		uth->uu_flag &= UT_WASSETUID;
	}
	uth->uu_proc = 0;
	uth->uu_sigmask = uth->uu_vforkmask;

	proc_lock(child_proc);
	child_proc->p_lflag &= ~P_LINVFORK;
	child_proc->p_vforkact = 0;
	proc_unlock(child_proc);

	thread_set_parent(th, rval);

	if (retval) {
		retval[0] = rval;
		retval[1] = 0;			/* mark parent */
	}
}