#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* task_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  mach_exception_data_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  scalar_t__ kern_return_t ;
typedef  TYPE_3__* host_priv_t ;
typedef  scalar_t__ exception_type_t ;
struct TYPE_9__ {int /*<<< orphan*/  exc_actions; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {int /*<<< orphan*/  exc_actions; int /*<<< orphan*/  itk_lock_data; } ;
struct TYPE_7__ {TYPE_2__* task; int /*<<< orphan*/  exc_actions; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 scalar_t__ EXC_CORPSE_NOTIFY ; 
 scalar_t__ EXC_CRASH ; 
 scalar_t__ EXC_GUARD ; 
 scalar_t__ EXC_RESOURCE ; 
 scalar_t__ EXC_RPC_ALERT ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ MACH_RCV_PORT_DIED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ check_exc_receiver_dependency (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ exception_deliver (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* host_priv_self () ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ panic_on_exception_triage ; 
 int /*<<< orphan*/  thread_exception_return () ; 

kern_return_t
exception_triage_thread(
	exception_type_t	exception,
	mach_exception_data_t	code,
	mach_msg_type_number_t  codeCnt,
	thread_t 		thread)
{
	task_t			task;
	host_priv_t		host_priv;
	lck_mtx_t		*mutex;
	kern_return_t	kr = KERN_FAILURE;

	assert(exception != EXC_RPC_ALERT);

	/*
	 * If this behavior has been requested by the the kernel
	 * (due to the boot environment), we should panic if we
	 * enter this function.  This is intended as a debugging
	 * aid; it should allow us to debug why we caught an
	 * exception in environments where debugging is especially
	 * difficult.
	 */
	if (panic_on_exception_triage) {
		panic("called exception_triage when it was forbidden by the boot environment");
	}

	/*
	 * Try to raise the exception at the activation level.
	 */
	mutex = &thread->mutex;
	if (KERN_SUCCESS == check_exc_receiver_dependency(exception, thread->exc_actions, mutex))
	{
		kr = exception_deliver(thread, exception, code, codeCnt, thread->exc_actions, mutex);
		if (kr == KERN_SUCCESS || kr == MACH_RCV_PORT_DIED)
			goto out;
	}

	/*
	 * Maybe the task level will handle it.
	 */
	task = thread->task;
	mutex = &task->itk_lock_data;
	if (KERN_SUCCESS == check_exc_receiver_dependency(exception, task->exc_actions, mutex))
	{
		kr = exception_deliver(thread, exception, code, codeCnt, task->exc_actions, mutex);
		if (kr == KERN_SUCCESS || kr == MACH_RCV_PORT_DIED)
			goto out;
	}

	/*
	 * How about at the host level?
	 */
	host_priv = host_priv_self();
	mutex = &host_priv->lock;

	if (KERN_SUCCESS == check_exc_receiver_dependency(exception, host_priv->exc_actions, mutex))
	{
		kr = exception_deliver(thread, exception, code, codeCnt, host_priv->exc_actions, mutex);
		if (kr == KERN_SUCCESS || kr == MACH_RCV_PORT_DIED)
			goto out;
	}

out:
	if ((exception != EXC_CRASH) && (exception != EXC_RESOURCE) &&
	    (exception != EXC_GUARD) && (exception != EXC_CORPSE_NOTIFY))
		thread_exception_return();
	return kr;
}