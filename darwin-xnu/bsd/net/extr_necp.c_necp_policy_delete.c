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
struct necp_session_policy {int /*<<< orphan*/ * route_rules; int /*<<< orphan*/ * conditions; int /*<<< orphan*/ * result; } ;
struct necp_session {int dummy; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE_ZONE (struct necp_session_policy*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct necp_session_policy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  M_NECP ; 
 int /*<<< orphan*/  M_NECP_SESSION_POLICY ; 
 int /*<<< orphan*/  NECPLOG0 (int /*<<< orphan*/ ,char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  chain ; 
 scalar_t__ necp_debug ; 

__attribute__((used)) static bool
necp_policy_delete(struct necp_session *session, struct necp_session_policy *policy)
{
	if (session == NULL || policy == NULL) {
		return (FALSE);
	}

	LIST_REMOVE(policy, chain);

	if (policy->result) {
		FREE(policy->result, M_NECP);
		policy->result = NULL;
	}

	if (policy->conditions) {
		FREE(policy->conditions, M_NECP);
		policy->conditions = NULL;
	}

	if (policy->route_rules) {
		FREE(policy->route_rules, M_NECP);
		policy->route_rules = NULL;
	}

	FREE_ZONE(policy, sizeof(*policy), M_NECP_SESSION_POLICY);

	if (necp_debug) {
		NECPLOG0(LOG_DEBUG, "Removed NECP policy");
	}
	return (TRUE);
}