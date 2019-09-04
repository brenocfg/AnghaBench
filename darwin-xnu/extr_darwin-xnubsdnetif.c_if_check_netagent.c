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
typedef  size_t uint32_t ;
struct ifnet {size_t if_agentcount; int /*<<< orphan*/ * if_agentids; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (struct ifnet*) ; 
 scalar_t__ uuid_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uuid_is_null (int /*<<< orphan*/ ) ; 

boolean_t
if_check_netagent(struct ifnet *ifp, uuid_t find_agent_uuid)
{
	boolean_t found = FALSE;

	if (!ifp || uuid_is_null(find_agent_uuid))
		return FALSE;

	ifnet_lock_shared(ifp);

	if (ifp->if_agentids != NULL) {
		for (uint32_t index = 0; index < ifp->if_agentcount; index++) {
			if (uuid_compare(ifp->if_agentids[index], find_agent_uuid) == 0) {
				found = TRUE;
				break;
			}
		}
	}

	ifnet_lock_done(ifp);

	return found;
}