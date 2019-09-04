#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t tunnel_interface_index; } ;
typedef  TYPE_1__ necp_kernel_policy_result_parameter ;
typedef  int /*<<< orphan*/ * ifnet_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** ifindex2ifnet ; 

ifnet_t
necp_get_ifnet_from_result_parameter(necp_kernel_policy_result_parameter *result_parameter)
{
	if (result_parameter == NULL) {
		return (NULL);
	}

	return (ifindex2ifnet[result_parameter->tunnel_interface_index]);
}