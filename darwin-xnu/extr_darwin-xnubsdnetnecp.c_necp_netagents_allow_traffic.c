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
typedef  scalar_t__ u_int32_t ;
struct necp_uuid_id_mapping {int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ NETAGENT_FLAG_ACTIVE ; 
 scalar_t__ NETAGENT_FLAG_REGISTERED ; 
 scalar_t__ NETAGENT_FLAG_VOLUNTARY ; 
 int TRUE ; 
 struct necp_uuid_id_mapping* necp_uuid_lookup_uuid_with_service_id_locked (scalar_t__) ; 
 scalar_t__ netagent_get_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
necp_netagents_allow_traffic(u_int32_t *netagent_ids, size_t netagent_id_count)
{
	size_t netagent_cursor;
	for (netagent_cursor = 0; netagent_cursor < netagent_id_count; netagent_cursor++) {
		struct necp_uuid_id_mapping *mapping = NULL;
		u_int32_t netagent_id = netagent_ids[netagent_cursor];
		if (netagent_id == 0) {
			break;
		}
		mapping = necp_uuid_lookup_uuid_with_service_id_locked(netagent_id);
		if (mapping != NULL) {
			u_int32_t agent_flags = 0;
			agent_flags = netagent_get_flags(mapping->uuid);
			if (agent_flags & NETAGENT_FLAG_REGISTERED) {
				if (agent_flags & NETAGENT_FLAG_ACTIVE) {
					continue;
				} else if ((agent_flags & NETAGENT_FLAG_VOLUNTARY) == 0) {
					return (FALSE);
				}
			}
		}
	}
	return (TRUE);
}