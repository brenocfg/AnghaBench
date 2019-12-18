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
typedef  void* u_int16_t ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct inpcb {int dummy; } ;
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  necp_kernel_policy_id ;
typedef  int /*<<< orphan*/  ifnet_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct in_addr*,int) ; 
 int necp_socket_is_allowed_to_send_recv_internal (struct inpcb*,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
necp_socket_is_allowed_to_send_recv_v4(struct inpcb *inp, u_int16_t local_port, u_int16_t remote_port, struct in_addr *local_addr, struct in_addr *remote_addr, ifnet_t interface, necp_kernel_policy_id *return_policy_id, u_int32_t *return_route_rule_id, necp_kernel_policy_id *return_skip_policy_id)
{
	struct sockaddr_in local = {};
	struct sockaddr_in remote = {};
	local.sin_family = remote.sin_family = AF_INET;
	local.sin_len = remote.sin_len = sizeof(struct sockaddr_in);
	local.sin_port = local_port;
	remote.sin_port = remote_port;
	memcpy(&local.sin_addr, local_addr, sizeof(local.sin_addr));
	memcpy(&remote.sin_addr, remote_addr, sizeof(remote.sin_addr));

	return (necp_socket_is_allowed_to_send_recv_internal(inp, (struct sockaddr *)&local, (struct sockaddr *)&remote, interface,
														 return_policy_id, return_route_rule_id, return_skip_policy_id));
}