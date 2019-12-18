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

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LCK_RW_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT_EXCLUSIVE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NECPLOG0 (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ NECP_FIRST_VALID_AGGREGATE_ROUTE_RULE_ID ; 
 scalar_t__ NECP_FIRST_VALID_ROUTE_RULE_ID ; 
 int TRUE ; 
 int /*<<< orphan*/  necp_kernel_policy_lock ; 
 int /*<<< orphan*/ * necp_lookup_route_rule_locked (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  necp_route_rule_lock ; 
 int /*<<< orphan*/  necp_route_rules ; 

__attribute__((used)) static u_int32_t
necp_get_new_route_rule_id(bool aggregate)
{
	static u_int32_t necp_last_route_rule_id = 0;
	static u_int32_t necp_last_aggregate_route_rule_id = 0;

	u_int32_t newid = 0;

	if (!aggregate) {
		// Main necp_kernel_policy_lock protects non-aggregate rule IDs
		LCK_RW_ASSERT(&necp_kernel_policy_lock, LCK_RW_ASSERT_EXCLUSIVE);

		bool wrapped = FALSE;
		do {
			necp_last_route_rule_id++;
			if (necp_last_route_rule_id < NECP_FIRST_VALID_ROUTE_RULE_ID ||
				necp_last_route_rule_id >= NECP_FIRST_VALID_AGGREGATE_ROUTE_RULE_ID) {
				if (wrapped) {
					// Already wrapped, give up
					NECPLOG0(LOG_ERR, "Failed to find a free route rule id.\n");
					return (0);
				}
				necp_last_route_rule_id = NECP_FIRST_VALID_ROUTE_RULE_ID;
				wrapped = TRUE;
			}
			newid = necp_last_route_rule_id;
		} while (necp_lookup_route_rule_locked(&necp_route_rules, newid) != NULL); // If already used, keep trying
	} else {
		// necp_route_rule_lock protects aggregate rule IDs
		LCK_RW_ASSERT(&necp_route_rule_lock, LCK_RW_ASSERT_EXCLUSIVE);

		bool wrapped = FALSE;
		do {
			necp_last_aggregate_route_rule_id++;
			if (necp_last_aggregate_route_rule_id < NECP_FIRST_VALID_AGGREGATE_ROUTE_RULE_ID) {
				if (wrapped) {
					// Already wrapped, give up
					NECPLOG0(LOG_ERR, "Failed to find a free aggregate route rule id.\n");
					return (0);
				}
				necp_last_aggregate_route_rule_id = NECP_FIRST_VALID_AGGREGATE_ROUTE_RULE_ID;
				wrapped = TRUE;
			}
			newid = necp_last_aggregate_route_rule_id;
		} while (necp_lookup_route_rule_locked(&necp_route_rules, newid) != NULL); // If already used, keep trying
	}

	if (newid == 0) {
		NECPLOG0(LOG_ERR, "Allocate route rule ID failed.\n");
		return (0);
	}

	return (newid);
}