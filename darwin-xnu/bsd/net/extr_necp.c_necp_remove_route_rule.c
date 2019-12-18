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
typedef  int /*<<< orphan*/  u_int32_t ;
struct necp_route_rule_list {int dummy; } ;
struct necp_route_rule {scalar_t__ refcount; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FREE (struct necp_route_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT_EXCLUSIVE ; 
 int /*<<< orphan*/  LIST_REMOVE (struct necp_route_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NECP ; 
 int TRUE ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  necp_kernel_policy_lock ; 
 struct necp_route_rule* necp_lookup_route_rule_locked (struct necp_route_rule_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  necp_remove_aggregate_route_rule_for_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
necp_remove_route_rule(struct necp_route_rule_list *list, u_int32_t route_rule_id)
{
	struct necp_route_rule *existing_rule = NULL;

	LCK_RW_ASSERT(&necp_kernel_policy_lock, LCK_RW_ASSERT_EXCLUSIVE);

	existing_rule = necp_lookup_route_rule_locked(list, route_rule_id);
	if (existing_rule != NULL) {
		if (--existing_rule->refcount == 0) {
			necp_remove_aggregate_route_rule_for_id(existing_rule->id);
			LIST_REMOVE(existing_rule, chain);
			FREE(existing_rule, M_NECP);
		}
		return (TRUE);
	}

	return (FALSE);
}