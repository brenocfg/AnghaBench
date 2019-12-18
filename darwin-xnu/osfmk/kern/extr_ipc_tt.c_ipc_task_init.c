#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
typedef  scalar_t__ kern_return_t ;
typedef  TYPE_2__* ipc_space_t ;
typedef  scalar_t__ ipc_port_t ;
struct TYPE_16__ {int /*<<< orphan*/  privileged; int /*<<< orphan*/  behavior; int /*<<< orphan*/  flavor; void* port; } ;
struct TYPE_15__ {TYPE_1__* is_task; } ;
struct TYPE_14__ {scalar_t__ itk_self; void* itk_task_access; void* itk_gssd; void* itk_seatbelt; void* itk_bootstrap; void* itk_host; TYPE_4__* exc_actions; void** itk_registered; TYPE_2__* itk_space; scalar_t__ itk_debug_control; scalar_t__ itk_sself; scalar_t__ itk_resume; scalar_t__ itk_nself; } ;

/* Variables and functions */
 int EXC_TYPES_COUNT ; 
 int FIRST_EXCEPTION ; 
 scalar_t__ IP_NULL ; 
 scalar_t__ KERN_SUCCESS ; 
 TYPE_1__* TASK_NULL ; 
 int TASK_PORT_REGISTER_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ host_get_host_port (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  host_priv_self () ; 
 scalar_t__ ipc_port_alloc_kernel () ; 
 void* ipc_port_copy_send (void*) ; 
 scalar_t__ ipc_port_make_send (scalar_t__) ; 
 scalar_t__ ipc_space_create (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/ * ipc_table_entries ; 
 int /*<<< orphan*/  itk_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  itk_lock_init (TYPE_1__*) ; 
 int /*<<< orphan*/  itk_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  mac_exc_associate_action_label (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_exc_create_label () ; 
 int /*<<< orphan*/  mac_exc_inherit_action_label (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ task_is_a_corpse_fork (TYPE_1__*) ; 

void
ipc_task_init(
	task_t		task,
	task_t		parent)
{
	ipc_space_t space;
	ipc_port_t kport;
	ipc_port_t nport;
	kern_return_t kr;
	int i;


	kr = ipc_space_create(&ipc_table_entries[0], &space);
	if (kr != KERN_SUCCESS)
		panic("ipc_task_init");

	space->is_task = task;

	kport = ipc_port_alloc_kernel();
	if (kport == IP_NULL)
		panic("ipc_task_init");

	nport = ipc_port_alloc_kernel();
	if (nport == IP_NULL)
		panic("ipc_task_init");

	itk_lock_init(task);
	task->itk_self = kport;
	task->itk_nself = nport;
	task->itk_resume = IP_NULL; /* Lazily allocated on-demand */
	if (task_is_a_corpse_fork(task)) {
		/*
		 * No sender's notification for corpse would not
		 * work with a naked send right in kernel.
		 */
		task->itk_sself = IP_NULL;
	} else {
		task->itk_sself = ipc_port_make_send(kport);
	}
	task->itk_debug_control = IP_NULL;
	task->itk_space = space;

#if CONFIG_MACF
	for (i = FIRST_EXCEPTION; i < EXC_TYPES_COUNT; i++) {
		mac_exc_associate_action_label(&task->exc_actions[i], mac_exc_create_label());
	}
#endif
	
	if (parent == TASK_NULL) {
		ipc_port_t port;

		for (i = FIRST_EXCEPTION; i < EXC_TYPES_COUNT; i++) {
			task->exc_actions[i].port = IP_NULL;
		}/* for */
		
		kr = host_get_host_port(host_priv_self(), &port);
		assert(kr == KERN_SUCCESS);
		task->itk_host = port;

		task->itk_bootstrap = IP_NULL;
		task->itk_seatbelt = IP_NULL;
		task->itk_gssd = IP_NULL;
		task->itk_task_access = IP_NULL;

		for (i = 0; i < TASK_PORT_REGISTER_MAX; i++)
			task->itk_registered[i] = IP_NULL;
	} else {
		itk_lock(parent);
		assert(parent->itk_self != IP_NULL);

		/* inherit registered ports */

		for (i = 0; i < TASK_PORT_REGISTER_MAX; i++)
			task->itk_registered[i] =
				ipc_port_copy_send(parent->itk_registered[i]);

		/* inherit exception and bootstrap ports */

		for (i = FIRST_EXCEPTION; i < EXC_TYPES_COUNT; i++) {
		    task->exc_actions[i].port =
		  		ipc_port_copy_send(parent->exc_actions[i].port);
		    task->exc_actions[i].flavor =
				parent->exc_actions[i].flavor;
		    task->exc_actions[i].behavior = 
				parent->exc_actions[i].behavior;
		    task->exc_actions[i].privileged =
				parent->exc_actions[i].privileged;
#if CONFIG_MACF
		    mac_exc_inherit_action_label(parent->exc_actions + i, task->exc_actions + i);
#endif
		}/* for */
		task->itk_host =
			ipc_port_copy_send(parent->itk_host);

		task->itk_bootstrap =
			ipc_port_copy_send(parent->itk_bootstrap);

		task->itk_seatbelt =
			ipc_port_copy_send(parent->itk_seatbelt);

		task->itk_gssd =
			ipc_port_copy_send(parent->itk_gssd);

		task->itk_task_access =
			ipc_port_copy_send(parent->itk_task_access);

		itk_unlock(parent);
	}
}