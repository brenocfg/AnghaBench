#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct label {int dummy; } ;
typedef  scalar_t__ ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_kobject_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_8__ {scalar_t__ port; scalar_t__ privileged; } ;
struct TYPE_7__ {scalar_t__ ith_self; scalar_t__ inspection; scalar_t__ ith_sself; scalar_t__ ith_special_reply_port; TYPE_4__* exc_actions; } ;

/* Variables and functions */
 int EXC_TYPES_COUNT ; 
 scalar_t__ FALSE ; 
 int FIRST_EXCEPTION ; 
 int /*<<< orphan*/  IKOT_NONE ; 
 int /*<<< orphan*/  IKOT_THREAD ; 
 int /*<<< orphan*/  IKO_NULL ; 
 scalar_t__ IP_NULL ; 
 scalar_t__ IP_VALID (scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ipc_kobject_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_port_alloc_kernel () ; 
 int /*<<< orphan*/  ipc_port_dealloc_kernel (scalar_t__) ; 
 scalar_t__ ipc_port_make_send (scalar_t__) ; 
 int /*<<< orphan*/  ipc_port_release_send (scalar_t__) ; 
 int /*<<< orphan*/  ipc_port_unbind_special_reply_port (TYPE_1__*,scalar_t__) ; 
 struct label* mac_exc_create_label () ; 
 int /*<<< orphan*/  mac_exc_free_label (struct label*) ; 
 int /*<<< orphan*/  mac_exc_update_action_label (TYPE_4__*,struct label*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_1__*) ; 

void
ipc_thread_reset(
	thread_t	thread)
{
	ipc_port_t old_kport, new_kport;
	ipc_port_t old_sself;
	ipc_port_t old_exc_actions[EXC_TYPES_COUNT];
	boolean_t  has_old_exc_actions = FALSE;	
	int		   i;

#if CONFIG_MACF
	struct label *new_label = mac_exc_create_label();
#endif
	
	new_kport = ipc_port_alloc_kernel();
	if (new_kport == IP_NULL)
		panic("ipc_task_reset");

	thread_mtx_lock(thread);

	old_kport = thread->ith_self;

	if (old_kport == IP_NULL && thread->inspection == FALSE) {
		/* the  is already terminated (can this happen?) */
		thread_mtx_unlock(thread);
		ipc_port_dealloc_kernel(new_kport);
#if CONFIG_MACF
		mac_exc_free_label(new_label);
#endif
		return;
	}

	thread->ith_self = new_kport;
	old_sself = thread->ith_sself;
	thread->ith_sself = ipc_port_make_send(new_kport);
	if (old_kport != IP_NULL) {
		ipc_kobject_set(old_kport, IKO_NULL, IKOT_NONE);
	}
	ipc_kobject_set(new_kport, (ipc_kobject_t) thread, IKOT_THREAD);

	/*
	 * Only ports that were set by root-owned processes
	 * (privileged ports) should survive 
	 */
	if (thread->exc_actions != NULL) {
		has_old_exc_actions = TRUE;
		for (i = FIRST_EXCEPTION; i < EXC_TYPES_COUNT; i++) {
			if (thread->exc_actions[i].privileged) {
				old_exc_actions[i] = IP_NULL;
			} else {
#if CONFIG_MACF
				mac_exc_update_action_label(thread->exc_actions + i, new_label);
#endif
				old_exc_actions[i] = thread->exc_actions[i].port;
				thread->exc_actions[i].port = IP_NULL;		
			}
		}
	}

	thread_mtx_unlock(thread);

#if CONFIG_MACF
	mac_exc_free_label(new_label);
#endif
	
	/* release the naked send rights */

	if (IP_VALID(old_sself))
		ipc_port_release_send(old_sself);

	if (has_old_exc_actions) {
		for (i = FIRST_EXCEPTION; i < EXC_TYPES_COUNT; i++) {
			ipc_port_release_send(old_exc_actions[i]);
		}
	}

	/* destroy the kernel port */
	if (old_kport != IP_NULL) {
		ipc_port_dealloc_kernel(old_kport);
	}

	/* unbind the thread special reply port */
	if (IP_VALID(thread->ith_special_reply_port)) {
		ipc_port_unbind_special_reply_port(thread, TRUE);
	}
}