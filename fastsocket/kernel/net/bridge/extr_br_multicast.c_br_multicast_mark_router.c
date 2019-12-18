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
struct net_bridge_port {int multicast_router; int /*<<< orphan*/  multicast_router_timer; int /*<<< orphan*/  rlist; } ;
struct net_bridge {int multicast_router; scalar_t__ multicast_querier_interval; int /*<<< orphan*/  multicast_router_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_multicast_add_router (struct net_bridge*,struct net_bridge_port*) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void br_multicast_mark_router(struct net_bridge *br,
				     struct net_bridge_port *port)
{
	unsigned long now = jiffies;

	if (!port) {
		if (br->multicast_router == 1)
			mod_timer(&br->multicast_router_timer,
				  now + br->multicast_querier_interval);
		return;
	}

	if (port->multicast_router != 1)
		return;

	if (!hlist_unhashed(&port->rlist))
		goto timer;

	br_multicast_add_router(br, port);

timer:
	mod_timer(&port->multicast_router_timer,
		  now + br->multicast_querier_interval);
}