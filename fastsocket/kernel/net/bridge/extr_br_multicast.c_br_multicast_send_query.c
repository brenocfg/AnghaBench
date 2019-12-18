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
typedef  scalar_t__ u32 ;
struct net_bridge_port {int /*<<< orphan*/  multicast_query_timer; } ;
struct net_bridge {scalar_t__ multicast_startup_query_count; int /*<<< orphan*/  multicast_query_timer; scalar_t__ multicast_query_interval; scalar_t__ multicast_startup_query_interval; int /*<<< orphan*/  multicast_querier_timer; int /*<<< orphan*/  multicast_querier; scalar_t__ multicast_disabled; int /*<<< orphan*/  dev; } ;
struct br_ip {void* proto; int /*<<< orphan*/  u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  __br_multicast_send_query (struct net_bridge*,struct net_bridge_port*,struct br_ip*) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_multicast_send_query(struct net_bridge *br,
				    struct net_bridge_port *port, u32 sent)
{
	unsigned long time;
	struct br_ip br_group;

	if (!netif_running(br->dev) || br->multicast_disabled ||
	    !br->multicast_querier ||
	    timer_pending(&br->multicast_querier_timer))
		return;

	memset(&br_group.u, 0, sizeof(br_group.u));

	br_group.proto = htons(ETH_P_IP);
	__br_multicast_send_query(br, port, &br_group);

#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	br_group.proto = htons(ETH_P_IPV6);
	__br_multicast_send_query(br, port, &br_group);
#endif

	time = jiffies;
	time += sent < br->multicast_startup_query_count ?
		br->multicast_startup_query_interval :
		br->multicast_query_interval;
	mod_timer(port ? &port->multicast_query_timer :
			 &br->multicast_query_timer, time);
}