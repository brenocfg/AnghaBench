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
typedef  int /*<<< orphan*/  u_int8_t ;
struct necp_session_policy {int /*<<< orphan*/  result_size; int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int /*<<< orphan*/  necp_policy_result_get_type_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u_int8_t
necp_policy_get_result_type(struct necp_session_policy *policy)
{
	return (policy ? necp_policy_result_get_type_from_buffer(policy->result, policy->result_size) : 0);
}