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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int kern_return_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  TYPE_2__* atm_task_descriptor_t ;
struct TYPE_10__ {int /*<<< orphan*/  trace_buffer_size; int /*<<< orphan*/  trace_buffer; } ;
struct TYPE_9__ {TYPE_2__* atm_context; } ;

/* Variables and functions */
 TYPE_2__* ATM_TASK_DESCRIPTOR_NULL ; 
 int ATM_TRACE_DISABLE ; 
 int /*<<< orphan*/  IPC_PORT_VALID (int /*<<< orphan*/ ) ; 
 int KERN_FAILURE ; 
 int KERN_INVALID_TASK ; 
 int KERN_NOT_SUPPORTED ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int MACH_SEND_TIMED_OUT ; 
 int /*<<< orphan*/  atm_descriptor_get_reference (TYPE_2__*) ; 
 int atm_get_diagnostic_config () ; 
 int atm_inspect_process_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atm_task_descriptor_dealloc (TYPE_2__*) ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ disable_atm ; 
 int host_get_atm_notification_port (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_priv_self () ; 
 int /*<<< orphan*/  ipc_port_copy_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_release_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_clear_honor_qlimit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_set_honor_qlimit (int /*<<< orphan*/ ) ; 

kern_return_t
atm_send_proc_inspect_notification(
	task_t task,
	int32_t traced_pid,
	uint64_t traced_uniqueid)
{
	mach_port_t user_port = MACH_PORT_NULL;
	mach_port_t memory_port = MACH_PORT_NULL;
	kern_return_t kr;
	atm_task_descriptor_t task_descriptor = ATM_TASK_DESCRIPTOR_NULL;
	uint64_t buffer_size = 0;
	int			error;
	thread_t th = current_thread();

	if (disable_atm || (atm_get_diagnostic_config() & ATM_TRACE_DISABLE))
		return KERN_NOT_SUPPORTED;

	/* look for the requested memory in target task */
	if (!task)
		return KERN_INVALID_TASK;

	task_lock(task);
	if (task->atm_context){
		task_descriptor = task->atm_context;
		atm_descriptor_get_reference(task_descriptor);
	}
	task_unlock(task);

	if (task_descriptor == ATM_TASK_DESCRIPTOR_NULL){
		return KERN_FAILURE;
	}

	memory_port = ipc_port_copy_send(task_descriptor->trace_buffer);
	buffer_size =  task_descriptor->trace_buffer_size;
	atm_task_descriptor_dealloc(task_descriptor);

	/* get the communication port */
	error = host_get_atm_notification_port(host_priv_self(), &user_port);
	if ((error != KERN_SUCCESS) || !IPC_PORT_VALID(user_port)) {
		ipc_port_release_send(memory_port);
		return KERN_FAILURE;
	}

	thread_set_honor_qlimit(th);
	kr =  atm_inspect_process_buffer(user_port, traced_pid, traced_uniqueid, buffer_size, memory_port);
	thread_clear_honor_qlimit(th);

	if (kr != KERN_SUCCESS) {
		ipc_port_release_send(user_port);

		if (kr == MACH_SEND_TIMED_OUT) {
			kr = KERN_SUCCESS;
		}
	}

	ipc_port_release_send(memory_port);
	return kr;
}