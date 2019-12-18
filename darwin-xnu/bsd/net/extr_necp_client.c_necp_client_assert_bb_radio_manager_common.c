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
typedef  int /*<<< orphan*/  uint8_t ;
struct necp_client {int /*<<< orphan*/  agent_handle; int /*<<< orphan*/  proc_pid; int /*<<< orphan*/  client_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int FALSE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NECPLOG0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETAGENT_MESSAGE_TYPE_CLIENT_ASSERT ; 
 int /*<<< orphan*/  NETAGENT_MESSAGE_TYPE_CLIENT_UNASSERT ; 
 int TRUE ; 
 int /*<<< orphan*/  necp_client_add_assertion (struct necp_client*,int /*<<< orphan*/ ) ; 
 int necp_client_lookup_bb_radio_manager (struct necp_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  necp_client_remove_assertion (struct necp_client*,int /*<<< orphan*/ ) ; 
 int netagent_client_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
necp_client_assert_bb_radio_manager_common(struct necp_client *client, bool assert)
{
	uuid_t netagent_uuid;
	uint8_t assert_type;
	int error;

	error = necp_client_lookup_bb_radio_manager(client, netagent_uuid);
	if (error) {
		NECPLOG0(LOG_ERR, "BB radio manager agent not found");
		return error;
	}

	// Before unasserting, verify that the assertion was already taken
	if (assert == FALSE) {
		assert_type = NETAGENT_MESSAGE_TYPE_CLIENT_UNASSERT;

		if (!necp_client_remove_assertion(client, netagent_uuid)) {
			return EINVAL;
		}
	} else {
		assert_type = NETAGENT_MESSAGE_TYPE_CLIENT_ASSERT;
	}

	error = netagent_client_message(netagent_uuid, client->client_id, client->proc_pid, client->agent_handle, assert_type);
	if (error) {
		NECPLOG0(LOG_ERR, "netagent_client_message failed");
		return error;
	}

	// Only save the assertion if the action succeeded
	if (assert == TRUE) {
		necp_client_add_assertion(client, netagent_uuid);
	}

	return 0;
}