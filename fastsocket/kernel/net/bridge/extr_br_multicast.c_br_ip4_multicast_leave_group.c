#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_bridge_port {int dummy; } ;
struct net_bridge {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip4; } ;
struct br_ip {int /*<<< orphan*/  proto; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  br_multicast_leave_group (struct net_bridge*,struct net_bridge_port*,struct br_ip*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_local_multicast (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void br_ip4_multicast_leave_group(struct net_bridge *br,
					 struct net_bridge_port *port,
					 __be32 group)
{
	struct br_ip br_group;

	if (ipv4_is_local_multicast(group))
		return;

	br_group.u.ip4 = group;
	br_group.proto = htons(ETH_P_IP);

	br_multicast_leave_group(br, port, &br_group);
}