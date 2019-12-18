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
struct proc {int dummy; } ;
struct necp_fd_data {int flags; int /*<<< orphan*/  clients; int /*<<< orphan*/  proc_pid; } ;
struct necp_client_action_args {int client_id_len; scalar_t__ buffer; int /*<<< orphan*/  client_id; int /*<<< orphan*/  buffer_size; } ;
struct necp_client {int platform_binary; int /*<<< orphan*/  client_id; int /*<<< orphan*/  flow_registrations; int /*<<< orphan*/  assertion_list; void* agent_handle; int /*<<< orphan*/  proc_pid; int /*<<< orphan*/  parameters_length; int /*<<< orphan*/  route_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  parameters; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FREE (struct necp_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  M_NECP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NECPLOG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  NECPLOG0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NECP_CLIENT_LOCK (struct necp_client*) ; 
 int /*<<< orphan*/  NECP_CLIENT_TREE_LOCK_EXCLUSIVE () ; 
 int /*<<< orphan*/  NECP_CLIENT_TREE_UNLOCK () ; 
 int /*<<< orphan*/  NECP_CLIENT_UNLOCK (struct necp_client*) ; 
 int /*<<< orphan*/  NECP_FD_LOCK (struct necp_fd_data*) ; 
 int /*<<< orphan*/  NECP_FD_UNLOCK (struct necp_fd_data*) ; 
 int /*<<< orphan*/  NECP_MAX_CLIENT_PARAMETERS_SIZE ; 
 int NECP_OPEN_FLAG_PUSH_OBSERVER ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct necp_client*) ; 
 struct necp_client* _MALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _necp_client_global_tree ; 
 int /*<<< orphan*/  _necp_client_tree ; 
 int copyin (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ csproc_get_platform_binary (struct proc*) ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  necp_client_count ; 
 int /*<<< orphan*/  necp_client_global_tree ; 
 int /*<<< orphan*/  necp_client_retain (struct necp_client*) ; 
 int /*<<< orphan*/  necp_client_update_observer_add (struct necp_client*) ; 
 int /*<<< orphan*/  necp_fd_mtx_attr ; 
 int /*<<< orphan*/  necp_fd_mtx_grp ; 
 int /*<<< orphan*/  necp_generate_client_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  necp_update_client_result (int /*<<< orphan*/ ,struct necp_fd_data*,struct necp_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
necp_client_add(struct proc *p, struct necp_fd_data *fd_data, struct necp_client_action_args *uap, int *retval)
{
	int error = 0;
	struct necp_client *client = NULL;

	if (fd_data->flags & NECP_OPEN_FLAG_PUSH_OBSERVER) {
		NECPLOG0(LOG_ERR, "NECP client observers with push enabled may not add their own clients");
		return (EINVAL);
	}

	if (uap->client_id == 0 || uap->client_id_len != sizeof(uuid_t) ||
		uap->buffer_size == 0 || uap->buffer_size > NECP_MAX_CLIENT_PARAMETERS_SIZE || uap->buffer == 0) {
		return (EINVAL);
	}

	if ((client = _MALLOC(sizeof(struct necp_client) + uap->buffer_size, M_NECP,
						  M_WAITOK | M_ZERO)) == NULL) {
		error = ENOMEM;
		goto done;
	}

	error = copyin(uap->buffer, client->parameters, uap->buffer_size);
	if (error) {
		NECPLOG(LOG_ERR, "necp_client_add parameters copyin error (%d)", error);
		goto done;
	}

	lck_mtx_init(&client->lock, necp_fd_mtx_grp, necp_fd_mtx_attr);
	lck_mtx_init(&client->route_lock, necp_fd_mtx_grp, necp_fd_mtx_attr);
	necp_client_retain(client); // Hold our reference until close

	client->parameters_length = uap->buffer_size;
	client->proc_pid = fd_data->proc_pid; // Save off proc pid in case the client will persist past fd
	client->agent_handle = (void *)fd_data;
	client->platform_binary = ((csproc_get_platform_binary(p) == 0) ? 0 : 1);

	necp_generate_client_id(client->client_id, false);
	LIST_INIT(&client->assertion_list);
	RB_INIT(&client->flow_registrations);

	error = copyout(client->client_id, uap->client_id, sizeof(uuid_t));
	if (error) {
		NECPLOG(LOG_ERR, "necp_client_add client_id copyout error (%d)", error);
		goto done;
	}

	necp_client_update_observer_add(client);

	NECP_FD_LOCK(fd_data);
	RB_INSERT(_necp_client_tree, &fd_data->clients, client);
	OSIncrementAtomic(&necp_client_count);
	NECP_CLIENT_TREE_LOCK_EXCLUSIVE();
	RB_INSERT(_necp_client_global_tree, &necp_client_global_tree, client);
	NECP_CLIENT_TREE_UNLOCK();

	// Prime the client result
	NECP_CLIENT_LOCK(client);
	(void)necp_update_client_result(current_proc(), fd_data, client, NULL);
	NECP_CLIENT_UNLOCK(client);
	NECP_FD_UNLOCK(fd_data);
done:
	if (error != 0) {
		if (client != NULL) {
			FREE(client, M_NECP);
			client = NULL;
		}
	}
	*retval = error;

	return (error);
}