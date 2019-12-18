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
typedef  scalar_t__ u_int32_t ;
struct necp_session_policy {int /*<<< orphan*/  result_size; int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ necp_policy_result_get_parameter_length_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * necp_policy_result_get_parameter_pointer_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
necp_policy_get_result_parameter(struct necp_session_policy *policy, u_int8_t *parameter_buffer, u_int32_t parameter_buffer_length)
{
	if (policy) {
		u_int32_t parameter_length = necp_policy_result_get_parameter_length_from_buffer(policy->result, policy->result_size);
		if (parameter_buffer_length >= parameter_length) {
			u_int8_t *parameter = necp_policy_result_get_parameter_pointer_from_buffer(policy->result, policy->result_size);
			if (parameter && parameter_buffer) {
				memcpy(parameter_buffer, parameter, parameter_length);
				return (TRUE);
			}
		}
	}

	return (FALSE);
}