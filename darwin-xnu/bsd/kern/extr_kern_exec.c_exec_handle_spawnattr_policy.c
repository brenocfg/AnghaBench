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
typedef  int uint64_t ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_3__ {int /*<<< orphan*/  task; } ;

/* Variables and functions */
#define  POSIX_SPAWN_PROC_CLAMP_BACKGROUND 136 
#define  POSIX_SPAWN_PROC_CLAMP_MAINTENANCE 135 
 int POSIX_SPAWN_PROC_CLAMP_NONE ; 
#define  POSIX_SPAWN_PROC_CLAMP_UTILITY 134 
#define  POSIX_SPAWN_PROC_TYPE_APP_DEFAULT 133 
#define  POSIX_SPAWN_PROC_TYPE_APP_TAL 132 
#define  POSIX_SPAWN_PROC_TYPE_DAEMON_ADAPTIVE 131 
#define  POSIX_SPAWN_PROC_TYPE_DAEMON_BACKGROUND 130 
#define  POSIX_SPAWN_PROC_TYPE_DAEMON_INTERACTIVE 129 
#define  POSIX_SPAWN_PROC_TYPE_DAEMON_STANDARD 128 
 int POSIX_SPAWN_PROC_TYPE_MASK ; 
 int PRIO_DARWIN_ROLE_DEFAULT ; 
 int TASK_APPTYPE_APP_DEFAULT ; 
 int TASK_APPTYPE_APP_TAL ; 
 int TASK_APPTYPE_DAEMON_ADAPTIVE ; 
 int TASK_APPTYPE_DAEMON_BACKGROUND ; 
 int TASK_APPTYPE_DAEMON_INTERACTIVE ; 
 int TASK_APPTYPE_DAEMON_STANDARD ; 
 int TASK_APPTYPE_NONE ; 
 int TASK_UNSPECIFIED ; 
 int THREAD_QOS_BACKGROUND ; 
 int THREAD_QOS_MAINTENANCE ; 
 int THREAD_QOS_UNSPECIFIED ; 
 int THREAD_QOS_UTILITY ; 
 int /*<<< orphan*/  proc_darwin_role_to_task_role (int,int*) ; 
 int /*<<< orphan*/  proc_set_task_spawnpolicy (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static errno_t
exec_handle_spawnattr_policy(proc_t p, int psa_apptype, uint64_t psa_qos_clamp, uint64_t psa_darwin_role,
                             ipc_port_t * portwatch_ports, int portwatch_count)
{
	int apptype     = TASK_APPTYPE_NONE;
	int qos_clamp   = THREAD_QOS_UNSPECIFIED;
	int role        = TASK_UNSPECIFIED;

	if ((psa_apptype & POSIX_SPAWN_PROC_TYPE_MASK) != 0) {
		int proctype = psa_apptype & POSIX_SPAWN_PROC_TYPE_MASK;

		switch(proctype) {
			case POSIX_SPAWN_PROC_TYPE_DAEMON_INTERACTIVE:
				apptype = TASK_APPTYPE_DAEMON_INTERACTIVE;
				break;
			case POSIX_SPAWN_PROC_TYPE_DAEMON_STANDARD:
				apptype = TASK_APPTYPE_DAEMON_STANDARD;
				break;
			case POSIX_SPAWN_PROC_TYPE_DAEMON_ADAPTIVE:
				apptype = TASK_APPTYPE_DAEMON_ADAPTIVE;
				break;
			case POSIX_SPAWN_PROC_TYPE_DAEMON_BACKGROUND:
				apptype = TASK_APPTYPE_DAEMON_BACKGROUND;
				break;
			case POSIX_SPAWN_PROC_TYPE_APP_DEFAULT:
				apptype = TASK_APPTYPE_APP_DEFAULT;
				break;
#if !CONFIG_EMBEDDED
			case POSIX_SPAWN_PROC_TYPE_APP_TAL:
				apptype = TASK_APPTYPE_APP_TAL;
				break;
#endif /* !CONFIG_EMBEDDED */
			default:
				apptype = TASK_APPTYPE_NONE;
				/* TODO: Should an invalid value here fail the spawn? */
				break;
		}
	}

	if (psa_qos_clamp != POSIX_SPAWN_PROC_CLAMP_NONE) {
		switch (psa_qos_clamp) {
			case POSIX_SPAWN_PROC_CLAMP_UTILITY:
				qos_clamp = THREAD_QOS_UTILITY;
				break;
			case POSIX_SPAWN_PROC_CLAMP_BACKGROUND:
				qos_clamp = THREAD_QOS_BACKGROUND;
				break;
			case POSIX_SPAWN_PROC_CLAMP_MAINTENANCE:
				qos_clamp = THREAD_QOS_MAINTENANCE;
				break;
			default:
				qos_clamp = THREAD_QOS_UNSPECIFIED;
				/* TODO: Should an invalid value here fail the spawn? */
				break;
		}
	}

	if (psa_darwin_role != PRIO_DARWIN_ROLE_DEFAULT) {
		proc_darwin_role_to_task_role(psa_darwin_role, &role);
	}

	if (apptype   != TASK_APPTYPE_NONE      ||
	    qos_clamp != THREAD_QOS_UNSPECIFIED ||
	    role      != TASK_UNSPECIFIED) {
		proc_set_task_spawnpolicy(p->task, apptype, qos_clamp, role,
		                          portwatch_ports, portwatch_count);
	}

	return (0);
}