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
struct inpcb {int dummy; } ;
typedef  int /*<<< orphan*/  necp_kernel_policy_id ;

/* Variables and functions */
 int necp_socket_is_allowed_to_send_recv_internal (struct inpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
necp_socket_is_allowed_to_send_recv(struct inpcb *inp, necp_kernel_policy_id *return_policy_id, u_int32_t *return_route_rule_id,
									necp_kernel_policy_id *return_skip_policy_id)
{
	return (necp_socket_is_allowed_to_send_recv_internal(inp, NULL, NULL, NULL, return_policy_id, return_route_rule_id, return_skip_policy_id));
}