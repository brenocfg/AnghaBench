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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  mach_atm_subaid_t ;
typedef  int kern_return_t ;
typedef  int /*<<< orphan*/  aid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_PORT_VALID (int /*<<< orphan*/ ) ; 
 int KERN_FAILURE ; 
 int KERN_SUCCESS ; 
 int MACH_SEND_TIMED_OUT ; 
 int atm_collect_trace_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 int host_get_atm_notification_port (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_priv_self () ; 
 int /*<<< orphan*/  ipc_port_release_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_clear_honor_qlimit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_set_honor_qlimit (int /*<<< orphan*/ ) ; 

kern_return_t
atm_send_user_notification(
	aid_t aid,
	mach_atm_subaid_t sub_aid,
	mach_port_t *buffers_array,
	uint64_t *sizes_array,
	mach_msg_type_number_t count,
	uint32_t flags)
{
	mach_port_t user_port;
	int			error;
	thread_t th = current_thread();
	kern_return_t kr;

	error = host_get_atm_notification_port(host_priv_self(), &user_port);
	if ((error != KERN_SUCCESS) || !IPC_PORT_VALID(user_port)) {
		return KERN_FAILURE;
	}

	thread_set_honor_qlimit(th);
	kr = atm_collect_trace_info(user_port, aid, sub_aid, flags, buffers_array, count, sizes_array, count);
	thread_clear_honor_qlimit(th);

	if (kr != KERN_SUCCESS) {
		ipc_port_release_send(user_port);

		if (kr == MACH_SEND_TIMED_OUT) {
			kr = KERN_SUCCESS;
		}
	}

	return kr;
}