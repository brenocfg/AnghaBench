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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int u_int32_t ;
struct proc {int dummy; } ;
struct necp_session_action_args {int action; int /*<<< orphan*/  necp_fd; } ;
struct necp_session {int /*<<< orphan*/  proc_pid; int /*<<< orphan*/  proc_uuid; scalar_t__ proc_locked; } ;
typedef  int /*<<< orphan*/  proc_uuid ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NECPLOG (int /*<<< orphan*/ ,char*,int) ; 
#define  NECP_SESSION_ACTION_LOCK_SESSION_TO_PROC 138 
#define  NECP_SESSION_ACTION_POLICY_ADD 137 
#define  NECP_SESSION_ACTION_POLICY_APPLY_ALL 136 
#define  NECP_SESSION_ACTION_POLICY_DELETE 135 
#define  NECP_SESSION_ACTION_POLICY_DELETE_ALL 134 
#define  NECP_SESSION_ACTION_POLICY_DUMP_ALL 133 
#define  NECP_SESSION_ACTION_POLICY_GET 132 
#define  NECP_SESSION_ACTION_POLICY_LIST_ALL 131 
#define  NECP_SESSION_ACTION_REGISTER_SERVICE 130 
#define  NECP_SESSION_ACTION_SET_SESSION_PRIORITY 129 
#define  NECP_SESSION_ACTION_UNREGISTER_SERVICE 128 
 int /*<<< orphan*/  NECP_SESSION_LOCK (struct necp_session*) ; 
 int /*<<< orphan*/  NECP_SESSION_UNLOCK (struct necp_session*) ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  file_drop (int /*<<< orphan*/ ) ; 
 int necp_session_add_policy (struct necp_session*,struct necp_session_action_args*,int*) ; 
 int necp_session_apply_all (struct necp_session*,struct necp_session_action_args*,int*) ; 
 int necp_session_delete_all (struct necp_session*,struct necp_session_action_args*,int*) ; 
 int necp_session_delete_policy (struct necp_session*,struct necp_session_action_args*,int*) ; 
 int necp_session_dump_all (struct necp_session*,struct necp_session_action_args*,int*) ; 
 int necp_session_find_from_fd (int /*<<< orphan*/ ,struct necp_session**) ; 
 int necp_session_get_policy (struct necp_session*,struct necp_session_action_args*,int*) ; 
 int necp_session_list_all (struct necp_session*,struct necp_session_action_args*,int*) ; 
 int necp_session_lock_to_process (struct necp_session*,struct necp_session_action_args*,int*) ; 
 int necp_session_register_service (struct necp_session*,struct necp_session_action_args*,int*) ; 
 int necp_session_set_session_priority (struct necp_session*,struct necp_session_action_args*,int*) ; 
 int necp_session_unregister_service (struct necp_session*,struct necp_session_action_args*,int*) ; 
 int /*<<< orphan*/  proc_getexecutableuuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_pid (int /*<<< orphan*/ ) ; 
 scalar_t__ uuid_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
necp_session_action(struct proc *p, struct necp_session_action_args *uap, int *retval)
{
#pragma unused(p)
	int error = 0;
	int return_value = 0;
	struct necp_session *session = NULL;
	error = necp_session_find_from_fd(uap->necp_fd, &session);
	if (error != 0) {
		NECPLOG(LOG_ERR, "necp_session_action find fd error (%d)", error);
		return (error);
	}

	NECP_SESSION_LOCK(session);

	if (session->proc_locked) {
		// Verify that the calling process is allowed to do actions
		uuid_t proc_uuid;
		proc_getexecutableuuid(current_proc(), proc_uuid, sizeof(proc_uuid));
		if (uuid_compare(proc_uuid, session->proc_uuid) != 0) {
			error = EPERM;
			goto done;
		}
	} else {
		// If not locked, update the proc_uuid and proc_pid of the session
		proc_getexecutableuuid(current_proc(), session->proc_uuid, sizeof(session->proc_uuid));
		session->proc_pid = proc_pid(current_proc());
	}

	u_int32_t action = uap->action;
	switch (action) {
		case NECP_SESSION_ACTION_POLICY_ADD: {
			return_value = necp_session_add_policy(session, uap, retval);
			break;
		}
		case NECP_SESSION_ACTION_POLICY_GET: {
			return_value = necp_session_get_policy(session, uap, retval);
			break;
		}
		case NECP_SESSION_ACTION_POLICY_DELETE:  {
			return_value = necp_session_delete_policy(session, uap, retval);
			break;
		}
		case NECP_SESSION_ACTION_POLICY_APPLY_ALL: {
			return_value = necp_session_apply_all(session, uap, retval);
			break;
		}
		case NECP_SESSION_ACTION_POLICY_LIST_ALL: {
			return_value = necp_session_list_all(session, uap, retval);
			break;
		}
		case NECP_SESSION_ACTION_POLICY_DELETE_ALL: {
			return_value = necp_session_delete_all(session, uap, retval);
			break;
		}
		case NECP_SESSION_ACTION_SET_SESSION_PRIORITY: {
			return_value = necp_session_set_session_priority(session, uap, retval);
			break;
		}
		case NECP_SESSION_ACTION_LOCK_SESSION_TO_PROC: {
			return_value = necp_session_lock_to_process(session, uap, retval);
			break;
		}
		case NECP_SESSION_ACTION_REGISTER_SERVICE: {
			return_value = necp_session_register_service(session, uap, retval);
			break;
		}
		case NECP_SESSION_ACTION_UNREGISTER_SERVICE: {
			return_value = necp_session_unregister_service(session, uap, retval);
			break;
		}
		case NECP_SESSION_ACTION_POLICY_DUMP_ALL: {
			return_value = necp_session_dump_all(session, uap, retval);
			break;
		}
		default: {
			NECPLOG(LOG_ERR, "necp_session_action unknown action (%u)", action);
			return_value = EINVAL;
			break;
		}
	}

done:
	NECP_SESSION_UNLOCK(session);
	file_drop(uap->necp_fd);

	return (return_value);
}