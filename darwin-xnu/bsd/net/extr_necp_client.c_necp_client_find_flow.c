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
struct necp_client_flow_registration {int /*<<< orphan*/  registration_id; } ;
struct necp_client {int /*<<< orphan*/  flow_registrations; } ;

/* Variables and functions */
 int /*<<< orphan*/  NECP_CLIENT_ASSERT_LOCKED (struct necp_client*) ; 
 struct necp_client_flow_registration* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct necp_client_flow_registration*) ; 
 struct necp_client_flow_registration* RB_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _necp_client_flow_tree ; 
 scalar_t__ necp_client_id_is_flow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct necp_client_flow_registration *
necp_client_find_flow(struct necp_client *client, uuid_t flow_id)
{
	NECP_CLIENT_ASSERT_LOCKED(client);
	struct necp_client_flow_registration *flow = NULL;

	if (necp_client_id_is_flow(flow_id)) {
		struct necp_client_flow_registration find;
		uuid_copy(find.registration_id, flow_id);
		flow = RB_FIND(_necp_client_flow_tree, &client->flow_registrations, &find);
	} else {
		flow = RB_ROOT(&client->flow_registrations);
	}

	return (flow);
}