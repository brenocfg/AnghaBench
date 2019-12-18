#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_t ;
struct image_params {int /*<<< orphan*/  ip_new_thread; int /*<<< orphan*/  ip_vfs_context; TYPE_2__* ip_px_spa; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/ * ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
typedef  scalar_t__ errno_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int port_type; int /*<<< orphan*/  new_port; int /*<<< orphan*/  flavor; int /*<<< orphan*/  behavior; int /*<<< orphan*/  mask; int /*<<< orphan*/  which; } ;
typedef  TYPE_1__ _ps_port_action_t ;
typedef  TYPE_2__* _posix_spawn_port_actions_t ;
struct TYPE_4__ {int pspa_count; TYPE_1__* pspa_actions; } ;

/* Variables and functions */
 int /*<<< orphan*/ * CAST_MACH_NAME_TO_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTRACE_PROC1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IPC_PORT_VALID (int /*<<< orphan*/ *) ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_COPY_SEND ; 
 scalar_t__ MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
#define  PSPA_AU_SESSION 131 
#define  PSPA_EXCEPTION 130 
#define  PSPA_IMP_WATCHPORTS 129 
#define  PSPA_SPECIAL 128 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ audit_session_spawnjoin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  get_task_ipcspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_threadtask (int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_object_copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_port_release_send (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_port_name_t ; 
 int /*<<< orphan*/  spawn__port__failure ; 
 scalar_t__ task_set_exception_ports (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ task_set_special_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
exec_handle_port_actions(struct image_params *imgp, boolean_t * portwatch_present,
                         ipc_port_t * portwatch_ports)
{
	_posix_spawn_port_actions_t pacts = imgp->ip_px_spa;
#if CONFIG_AUDIT
	proc_t p = vfs_context_proc(imgp->ip_vfs_context);
#endif
	_ps_port_action_t *act = NULL;
	task_t task = get_threadtask(imgp->ip_new_thread);
	ipc_port_t port = NULL;
	errno_t ret = 0;
	int i;
	kern_return_t kr;

	*portwatch_present = FALSE;

	for (i = 0; i < pacts->pspa_count; i++) {
		act = &pacts->pspa_actions[i];

		if (MACH_PORT_VALID(act->new_port)) {
			kr = ipc_object_copyin(get_task_ipcspace(current_task()),
			                       act->new_port, MACH_MSG_TYPE_COPY_SEND,
			                       (ipc_object_t *) &port);

			if (kr != KERN_SUCCESS) {
				ret = EINVAL;
				goto done;
			}
		} else {
			/* it's NULL or DEAD */
			port = CAST_MACH_NAME_TO_PORT(act->new_port);
		}

		switch (act->port_type) {
		case PSPA_SPECIAL:
			kr = task_set_special_port(task, act->which, port);

			if (kr != KERN_SUCCESS)
				ret = EINVAL;
			break;

		case PSPA_EXCEPTION:
			kr = task_set_exception_ports(task, act->mask, port,
			                              act->behavior, act->flavor);
			if (kr != KERN_SUCCESS)
				ret = EINVAL;
			break;
#if CONFIG_AUDIT
		case PSPA_AU_SESSION:
			ret = audit_session_spawnjoin(p, task, port);
			if (ret) {
				/* audit_session_spawnjoin() has already dropped the reference in case of error. */
				goto done;
			}

			break;
#endif
		case PSPA_IMP_WATCHPORTS:
			if (portwatch_ports != NULL && IPC_PORT_VALID(port)) {
				*portwatch_present = TRUE;
				/* hold on to this till end of spawn */
				portwatch_ports[i] = port;
			} else {
				ipc_port_release_send(port);
			}

			break;
		default:
			ret = EINVAL;
			break;
		}

		if (ret) {
			/* action failed, so release port resources */
			ipc_port_release_send(port);
			break;
		}
	}

done:
	if (0 != ret)
		DTRACE_PROC1(spawn__port__failure, mach_port_name_t, act->new_port);
	return (ret);
}