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
typedef  scalar_t__ uint32_t ;
typedef  size_t u_int32_t ;
struct necp_client_interface_option {scalar_t__ interface_index; int /*<<< orphan*/  nexus_agent; scalar_t__ interface_generation; } ;
struct necp_client {size_t interface_option_count; struct necp_client_interface_option* extra_interface_options; struct necp_client_interface_option* interface_options; int /*<<< orphan*/  allow_multiple_flows; } ;

/* Variables and functions */
 scalar_t__ IFSCOPE_NONE ; 
 int /*<<< orphan*/  M_NECP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NECP_CLIENT_INTERFACE_OPTION_EXTRA_COUNT ; 
 size_t NECP_CLIENT_INTERFACE_OPTION_STATIC_COUNT ; 
 size_t NECP_CLIENT_MAX_INTERFACE_OPTIONS ; 
 struct necp_client_interface_option* _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uuid_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uuid_is_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
necp_client_add_interface_option_if_needed(struct necp_client *client,
										   uint32_t interface_index,
										   uint32_t interface_generation,
										   uuid_t *nexus_agent)
{
	if (interface_index == IFSCOPE_NONE ||
		(client->interface_option_count != 0 && !client->allow_multiple_flows)) {
		// Interface not set, or client not allowed to use this mode
		return;
	}

	if (client->interface_option_count >= NECP_CLIENT_MAX_INTERFACE_OPTIONS) {
		// Cannot take any more interface options
		return;
	}

	// Check if already present
	for (u_int32_t option_i = 0; option_i < client->interface_option_count; option_i++) {
		if (option_i < NECP_CLIENT_INTERFACE_OPTION_STATIC_COUNT) {
			struct necp_client_interface_option *option = &client->interface_options[option_i];
			if (option->interface_index == interface_index) {
				if (nexus_agent == NULL) {
					return;
				}
				if (uuid_compare(option->nexus_agent, *nexus_agent) == 0) {
					return;
				}
				if (uuid_is_null(option->nexus_agent)) {
					uuid_copy(option->nexus_agent, *nexus_agent);
					return;
				}
				// If we get to this point, this is a new nexus flow
			}
		} else {
			struct necp_client_interface_option *option = &client->extra_interface_options[option_i - NECP_CLIENT_INTERFACE_OPTION_STATIC_COUNT];
			if (option->interface_index == interface_index) {
				if (nexus_agent == NULL) {
					return;
				}
				if (uuid_compare(option->nexus_agent, *nexus_agent) == 0) {
					return;
				}
				if (uuid_is_null(option->nexus_agent)) {
					uuid_copy(option->nexus_agent, *nexus_agent);
					return;
				}
				// If we get to this point, this is a new nexus flow
			}
		}
	}

	// Add a new entry
	if (client->interface_option_count < NECP_CLIENT_INTERFACE_OPTION_STATIC_COUNT) {
		// Add to static
		struct necp_client_interface_option *option = &client->interface_options[client->interface_option_count];
		option->interface_index = interface_index;
		option->interface_generation = interface_generation;
		if (nexus_agent != NULL) {
			uuid_copy(option->nexus_agent, *nexus_agent);
		}
		client->interface_option_count++;
	} else {
		// Add to extra
		if (client->extra_interface_options == NULL) {
			client->extra_interface_options = _MALLOC(sizeof(struct necp_client_interface_option) * NECP_CLIENT_INTERFACE_OPTION_EXTRA_COUNT, M_NECP, M_WAITOK | M_ZERO);
		}
		if (client->extra_interface_options != NULL) {
			struct necp_client_interface_option *option = &client->extra_interface_options[client->interface_option_count - NECP_CLIENT_INTERFACE_OPTION_STATIC_COUNT];
			option->interface_index = interface_index;
			option->interface_generation = interface_generation;
			if (nexus_agent != NULL) {
				uuid_copy(option->nexus_agent, *nexus_agent);
			}
			client->interface_option_count++;
		}
	}
}