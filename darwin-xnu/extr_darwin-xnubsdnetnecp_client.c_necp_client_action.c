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
typedef  int u_int32_t ;
struct proc {int dummy; } ;
struct necp_fd_data {int dummy; } ;
struct necp_client_action_args {int action; int /*<<< orphan*/  necp_fd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NECPLOG (int /*<<< orphan*/ ,char*,int) ; 
#define  NECP_CLIENT_ACTION_ADD 140 
#define  NECP_CLIENT_ACTION_AGENT 139 
#define  NECP_CLIENT_ACTION_AGENT_USE 138 
#define  NECP_CLIENT_ACTION_COPY_AGENT 137 
#define  NECP_CLIENT_ACTION_COPY_CLIENT_UPDATE 136 
#define  NECP_CLIENT_ACTION_COPY_INTERFACE 135 
#define  NECP_CLIENT_ACTION_COPY_LIST 134 
#define  NECP_CLIENT_ACTION_COPY_PARAMETERS 133 
#define  NECP_CLIENT_ACTION_COPY_RESULT 132 
#define  NECP_CLIENT_ACTION_COPY_ROUTE_STATISTICS 131 
#define  NECP_CLIENT_ACTION_COPY_UPDATED_RESULT 130 
#define  NECP_CLIENT_ACTION_REMOVE 129 
#define  NECP_CLIENT_ACTION_UPDATE_CACHE 128 
 int /*<<< orphan*/  file_drop (int /*<<< orphan*/ ) ; 
 int necp_client_add (struct proc*,struct necp_fd_data*,struct necp_client_action_args*,int*) ; 
 int necp_client_agent_action (struct necp_fd_data*,struct necp_client_action_args*,int*) ; 
 int necp_client_agent_use (struct necp_fd_data*,struct necp_client_action_args*,int*) ; 
 int necp_client_copy (struct necp_fd_data*,struct necp_client_action_args*,int*) ; 
 int necp_client_copy_agent (struct necp_fd_data*,struct necp_client_action_args*,int*) ; 
 int necp_client_copy_client_update (struct necp_fd_data*,struct necp_client_action_args*,int*) ; 
 int necp_client_copy_interface (struct necp_fd_data*,struct necp_client_action_args*,int*) ; 
 int necp_client_copy_route_statistics (struct necp_fd_data*,struct necp_client_action_args*,int*) ; 
 int necp_client_list (struct necp_fd_data*,struct necp_client_action_args*,int*) ; 
 int necp_client_remove (struct necp_fd_data*,struct necp_client_action_args*,int*) ; 
 int necp_client_update_cache (struct necp_fd_data*,struct necp_client_action_args*,int*) ; 
 int necp_find_fd_data (int /*<<< orphan*/ ,struct necp_fd_data**) ; 

int
necp_client_action(struct proc *p, struct necp_client_action_args *uap, int *retval)
{
#pragma unused(p)
	int error = 0;
	int return_value = 0;
	struct necp_fd_data *fd_data = NULL;
	error = necp_find_fd_data(uap->necp_fd, &fd_data);
	if (error != 0) {
		NECPLOG(LOG_ERR, "necp_client_action find fd error (%d)", error);
		return (error);
	}

	u_int32_t action = uap->action;
	switch (action) {
		case NECP_CLIENT_ACTION_ADD: {
			return_value = necp_client_add(p, fd_data, uap, retval);
			break;
		}
		case NECP_CLIENT_ACTION_REMOVE: {
			return_value = necp_client_remove(fd_data, uap, retval);
			break;
		}
		case NECP_CLIENT_ACTION_COPY_PARAMETERS:
		case NECP_CLIENT_ACTION_COPY_RESULT:
		case NECP_CLIENT_ACTION_COPY_UPDATED_RESULT: {
			return_value = necp_client_copy(fd_data, uap, retval);
			break;
		}
		case NECP_CLIENT_ACTION_COPY_LIST: {
			return_value = necp_client_list(fd_data, uap, retval);
			break;
		}
		case NECP_CLIENT_ACTION_AGENT: {
			return_value = necp_client_agent_action(fd_data, uap, retval);
			break;
		}
		case NECP_CLIENT_ACTION_COPY_AGENT: {
			return_value = necp_client_copy_agent(fd_data, uap, retval);
			break;
		}
		case NECP_CLIENT_ACTION_AGENT_USE: {
			return_value = necp_client_agent_use(fd_data, uap, retval);
			break;
		}
		case NECP_CLIENT_ACTION_COPY_INTERFACE: {
			return_value = necp_client_copy_interface(fd_data, uap, retval);
			break;
		}
		case NECP_CLIENT_ACTION_COPY_ROUTE_STATISTICS: {
			return_value = necp_client_copy_route_statistics(fd_data, uap, retval);
			break;
		}
		case NECP_CLIENT_ACTION_UPDATE_CACHE: {
			return_value = necp_client_update_cache(fd_data, uap, retval);
			break;
		}
		case NECP_CLIENT_ACTION_COPY_CLIENT_UPDATE: {
			return_value = necp_client_copy_client_update(fd_data, uap, retval);
			break;
		}
		default: {
			NECPLOG(LOG_ERR, "necp_client_action unknown action (%u)", action);
			return_value = EINVAL;
			break;
		}
	}

	file_drop(uap->necp_fd);

	return (return_value);
}