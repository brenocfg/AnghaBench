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
struct necp_fd_data {int /*<<< orphan*/  flows; } ;
struct necp_client_flow_registration {int flow_result_read; struct necp_client* client; int /*<<< orphan*/  flow_list; int /*<<< orphan*/  registration_id; int /*<<< orphan*/  last_interface_details; } ;
struct necp_client {int /*<<< orphan*/  flow_registrations; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFSCOPE_NONE ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MCR_SLEEP ; 
 int /*<<< orphan*/  NECP_CLIENT_ASSERT_LOCKED (struct necp_client*) ; 
 int /*<<< orphan*/  NECP_FD_ASSERT_LOCKED (struct necp_fd_data*) ; 
 int /*<<< orphan*/  NECP_FLOW_TREE_LOCK_EXCLUSIVE () ; 
 int /*<<< orphan*/  NECP_FLOW_TREE_UNLOCK () ; 
 int /*<<< orphan*/  NSTAT_IFNET_IS_UNKNOWN_TYPE ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct necp_client_flow_registration*) ; 
 int /*<<< orphan*/  _necp_client_flow_global_tree ; 
 int /*<<< orphan*/  _necp_client_flow_tree ; 
 int /*<<< orphan*/  _necp_fd_flow_tree ; 
 int /*<<< orphan*/  combine_interface_details (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct necp_client_flow_registration* mcache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct necp_client_flow_registration*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  necp_client_flow_global_tree ; 
 int /*<<< orphan*/  necp_flow_registration_cache ; 
 int /*<<< orphan*/  necp_generate_client_id (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct necp_client_flow_registration *
necp_client_create_flow_registration(struct necp_fd_data *fd_data, struct necp_client *client)
{
	NECP_FD_ASSERT_LOCKED(fd_data);
	NECP_CLIENT_ASSERT_LOCKED(client);

	struct necp_client_flow_registration *new_registration = mcache_alloc(necp_flow_registration_cache, MCR_SLEEP);
	if (new_registration == NULL) {
		return NULL;
	}

	memset(new_registration, 0, sizeof(*new_registration));

	new_registration->last_interface_details = combine_interface_details(IFSCOPE_NONE, NSTAT_IFNET_IS_UNKNOWN_TYPE);

	necp_generate_client_id(new_registration->registration_id, true);
	LIST_INIT(&new_registration->flow_list);

	// Add registration to client list
	RB_INSERT(_necp_client_flow_tree, &client->flow_registrations, new_registration);

	// Add registration to fd list
	RB_INSERT(_necp_fd_flow_tree, &fd_data->flows, new_registration);

	// Add registration to global tree for lookup
	NECP_FLOW_TREE_LOCK_EXCLUSIVE();
	RB_INSERT(_necp_client_flow_global_tree, &necp_client_flow_global_tree, new_registration);
	NECP_FLOW_TREE_UNLOCK();

	new_registration->client = client;

	// Start out assuming there is nothing to read from the flow
	new_registration->flow_result_read = true;

	return new_registration;
}