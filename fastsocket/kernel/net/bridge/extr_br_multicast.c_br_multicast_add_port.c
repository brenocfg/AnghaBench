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
struct net_bridge_port {int multicast_router; int /*<<< orphan*/  multicast_query_timer; int /*<<< orphan*/  multicast_router_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_multicast_port_query_expired ; 
 int /*<<< orphan*/  br_multicast_router_expired ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

void br_multicast_add_port(struct net_bridge_port *port)
{
	port->multicast_router = 1;

	setup_timer(&port->multicast_router_timer, br_multicast_router_expired,
		    (unsigned long)port);
	setup_timer(&port->multicast_query_timer,
		    br_multicast_port_query_expired, (unsigned long)port);
}