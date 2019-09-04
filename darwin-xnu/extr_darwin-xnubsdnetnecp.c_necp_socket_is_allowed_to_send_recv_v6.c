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
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_addr; void* sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
struct inpcb {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  necp_kernel_policy_id ;
typedef  int /*<<< orphan*/  ifnet_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct in6_addr*,int) ; 
 int necp_socket_is_allowed_to_send_recv_internal (struct inpcb*,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
necp_socket_is_allowed_to_send_recv_v6(struct inpcb *inp, u_int16_t local_port, u_int16_t remote_port, struct in6_addr *local_addr, struct in6_addr *remote_addr, ifnet_t interface, necp_kernel_policy_id *return_policy_id, u_int32_t *return_route_rule_id, necp_kernel_policy_id *return_skip_policy_id)
{
	struct sockaddr_in6 local = {};
	struct sockaddr_in6 remote = {};
	local.sin6_family = remote.sin6_family = AF_INET6;
	local.sin6_len = remote.sin6_len = sizeof(struct sockaddr_in6);
	local.sin6_port = local_port;
	remote.sin6_port = remote_port;
	memcpy(&local.sin6_addr, local_addr, sizeof(local.sin6_addr));
	memcpy(&remote.sin6_addr, remote_addr, sizeof(remote.sin6_addr));

	return (necp_socket_is_allowed_to_send_recv_internal(inp, (struct sockaddr *)&local, (struct sockaddr *)&remote, interface,
														 return_policy_id, return_route_rule_id, return_skip_policy_id));
}