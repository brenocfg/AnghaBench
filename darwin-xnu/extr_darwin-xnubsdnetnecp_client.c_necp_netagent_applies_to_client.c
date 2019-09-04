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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int32_t ;
struct necp_client_parsed_parameters {TYPE_2__* required_netagent_types; int /*<<< orphan*/ * required_netagents; } ;
struct TYPE_3__ {scalar_t__ generation; int /*<<< orphan*/  netagent_uuid; } ;
struct necp_client {TYPE_1__ failed_trigger_agent; } ;
struct TYPE_4__ {int /*<<< orphan*/  netagent_type; int /*<<< orphan*/  netagent_domain; } ;

/* Variables and functions */
 int FALSE ; 
 int NECP_MAX_PARSED_PARAMETERS ; 
 int NETAGENT_DOMAINSIZE ; 
 int NETAGENT_FLAG_NEXUS_PROVIDER ; 
 int NETAGENT_FLAG_REGISTERED ; 
 int NETAGENT_FLAG_SPECIFIC_USE_ONLY ; 
 int NETAGENT_TYPESIZE ; 
 int TRUE ; 
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netagent_get_agent_domain_and_type (int /*<<< orphan*/ ,char*,char*) ; 
 int netagent_get_flags (int /*<<< orphan*/ ) ; 
 scalar_t__ netagent_get_generation (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uuid_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ uuid_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uuid_is_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
necp_netagent_applies_to_client(struct necp_client *client,
								const struct necp_client_parsed_parameters *parameters,
								uuid_t *netagent_uuid, bool allow_nexus,
								uint32_t interface_index, uint32_t interface_generation)
{
#pragma unused(interface_index, interface_generation)
	bool applies = FALSE;
	u_int32_t flags = netagent_get_flags(*netagent_uuid);
	if (!(flags & NETAGENT_FLAG_REGISTERED)) {
		// Unregistered agents never apply
		return (applies);
	}

	if (!allow_nexus &&
		(flags & NETAGENT_FLAG_NEXUS_PROVIDER)) {
		// Hide nexus providers unless allowed
		// Direct interfaces and direct policies are allowed to use a nexus
		// Delegate interfaces or re-scoped interfaces are not allowed
		return (applies);
	}

	if (uuid_compare(client->failed_trigger_agent.netagent_uuid, *netagent_uuid) == 0) {
		if (client->failed_trigger_agent.generation == netagent_get_generation(*netagent_uuid)) {
			// If this agent was triggered, and failed, and hasn't changed, keep hiding it
			return (applies);
		} else {
			// Mismatch generation, clear out old trigger
			uuid_clear(client->failed_trigger_agent.netagent_uuid);
			client->failed_trigger_agent.generation = 0;
		}
	}

	if (flags & NETAGENT_FLAG_SPECIFIC_USE_ONLY) {
		// Specific use agents only apply when required
		bool required = FALSE;
		if (parameters != NULL) {
			// Check required agent UUIDs
			for (int i = 0; i < NECP_MAX_PARSED_PARAMETERS; i++) {
				if (uuid_is_null(parameters->required_netagents[i])) {
					break;
				}
				if (uuid_compare(parameters->required_netagents[i], *netagent_uuid) == 0) {
					required = TRUE;
					break;
				}
			}

			if (!required) {
				// Check required agent types
				bool fetched_type = FALSE;
				char netagent_domain[NETAGENT_DOMAINSIZE];
				char netagent_type[NETAGENT_TYPESIZE];
				memset(&netagent_domain, 0, NETAGENT_DOMAINSIZE);
				memset(&netagent_type, 0, NETAGENT_TYPESIZE);

				for (int i = 0; i < NECP_MAX_PARSED_PARAMETERS; i++) {
					if (strlen(parameters->required_netagent_types[i].netagent_domain) == 0 ||
						strlen(parameters->required_netagent_types[i].netagent_type) == 0) {
						break;
					}

					if (!fetched_type) {
						if (netagent_get_agent_domain_and_type(*netagent_uuid, netagent_domain, netagent_type)) {
							fetched_type = TRUE;
						} else {
							break;
						}
					}

					if ((strlen(parameters->required_netagent_types[i].netagent_domain) == 0 ||
						 strncmp(netagent_domain, parameters->required_netagent_types[i].netagent_domain, NETAGENT_DOMAINSIZE) == 0) &&
						(strlen(parameters->required_netagent_types[i].netagent_type) == 0 ||
						 strncmp(netagent_type, parameters->required_netagent_types[i].netagent_type, NETAGENT_TYPESIZE) == 0)) {
						required = TRUE;
						break;
					}
				}
			}
		}

		applies = required;
	} else {
		applies = TRUE;
	}


	return (applies);
}