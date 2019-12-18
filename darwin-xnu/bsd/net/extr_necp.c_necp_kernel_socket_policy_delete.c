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
struct necp_kernel_socket_policy {int /*<<< orphan*/ * cond_custom_entitlement; int /*<<< orphan*/ * cond_domain; int /*<<< orphan*/ * cond_bound_interface; } ;
typedef  int /*<<< orphan*/  necp_kernel_policy_id ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE_ZONE (struct necp_kernel_socket_policy*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT_EXCLUSIVE ; 
 int /*<<< orphan*/  LIST_REMOVE (struct necp_kernel_socket_policy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NECP ; 
 int /*<<< orphan*/  M_NECP_SOCKET_POLICY ; 
 int TRUE ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  ifnet_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  necp_kernel_policy_lock ; 
 struct necp_kernel_socket_policy* necp_kernel_socket_policy_find (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
necp_kernel_socket_policy_delete(necp_kernel_policy_id policy_id)
{
	struct necp_kernel_socket_policy *policy = NULL;

	LCK_RW_ASSERT(&necp_kernel_policy_lock, LCK_RW_ASSERT_EXCLUSIVE);

	policy = necp_kernel_socket_policy_find(policy_id);
	if (policy) {
		LIST_REMOVE(policy, chain);

		if (policy->cond_bound_interface) {
			ifnet_release(policy->cond_bound_interface);
			policy->cond_bound_interface = NULL;
		}

		if (policy->cond_domain) {
			FREE(policy->cond_domain, M_NECP);
			policy->cond_domain = NULL;
		}

		if (policy->cond_custom_entitlement) {
			FREE(policy->cond_custom_entitlement, M_NECP);
			policy->cond_custom_entitlement = NULL;
		}

		FREE_ZONE(policy, sizeof(*policy), M_NECP_SOCKET_POLICY);
		return (TRUE);
	}

	return (FALSE);
}