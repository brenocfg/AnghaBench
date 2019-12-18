#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  mach_exception_data_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  exception_type_t ;
struct TYPE_3__ {int /*<<< orphan*/  exc_actions; int /*<<< orphan*/  itk_lock_data; } ;

/* Variables and functions */
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ MACH_RCV_PORT_DIED ; 
 TYPE_1__* current_task () ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ exception_deliver (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
bsd_exception(
	exception_type_t	exception,
	mach_exception_data_t	code,
	mach_msg_type_number_t  codeCnt)
{
	task_t			task;
	lck_mtx_t		*mutex;
	thread_t		self = current_thread();
	kern_return_t		kr;

	/*
	 * Maybe the task level will handle it.
	 */
	task = current_task();
	mutex = &task->itk_lock_data;

	kr = exception_deliver(self, exception, code, codeCnt, task->exc_actions, mutex);

	if (kr == KERN_SUCCESS || kr == MACH_RCV_PORT_DIED)
		return(KERN_SUCCESS);
	return(KERN_FAILURE);
}