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
struct necp_client_flow_registration {int /*<<< orphan*/  client_id; struct necp_client_flow_registration* client; int /*<<< orphan*/  registration_id; } ;
struct necp_client {int /*<<< orphan*/  client_id; struct necp_client* client; int /*<<< orphan*/  registration_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NECP_CLIENT_LOCK (struct necp_client_flow_registration*) ; 
 int /*<<< orphan*/  NECP_CLIENT_TREE_ASSERT_LOCKED () ; 
 int /*<<< orphan*/  NECP_FLOW_TREE_LOCK_SHARED () ; 
 int /*<<< orphan*/  NECP_FLOW_TREE_UNLOCK () ; 
 struct necp_client_flow_registration* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct necp_client_flow_registration*) ; 
 int /*<<< orphan*/  _necp_client_flow_global_tree ; 
 int /*<<< orphan*/  _necp_client_global_tree ; 
 int /*<<< orphan*/  necp_client_flow_global_tree ; 
 int /*<<< orphan*/  necp_client_global_tree ; 
 scalar_t__ necp_client_id_is_flow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct necp_client *
necp_find_client_and_lock(uuid_t client_id)
{
	NECP_CLIENT_TREE_ASSERT_LOCKED();

	struct necp_client *client = NULL;

	if (necp_client_id_is_flow(client_id)) {
		NECP_FLOW_TREE_LOCK_SHARED();
		struct necp_client_flow_registration find;
		uuid_copy(find.registration_id, client_id);
		struct necp_client_flow_registration *flow = RB_FIND(_necp_client_flow_global_tree, &necp_client_flow_global_tree, &find);
		if (flow != NULL) {
			client = flow->client;
		}
		NECP_FLOW_TREE_UNLOCK();
	} else {
		struct necp_client find;
		uuid_copy(find.client_id, client_id);
		client = RB_FIND(_necp_client_global_tree, &necp_client_global_tree, &find);
	}

	if (client != NULL) {
		NECP_CLIENT_LOCK(client);
	}

	return (client);
}