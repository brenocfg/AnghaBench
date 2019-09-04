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
typedef  int u_int32_t ;

/* Variables and functions */

__attribute__((used)) static inline u_int32_t
necp_policy_result_get_parameter_length_from_buffer(u_int8_t *buffer, u_int32_t length)
{
	return ((buffer && length > sizeof(u_int8_t)) ? (length - sizeof(u_int8_t)) : 0);
}