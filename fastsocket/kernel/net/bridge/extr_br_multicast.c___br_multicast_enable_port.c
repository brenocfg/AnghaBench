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
struct net_bridge_port {int /*<<< orphan*/  multicast_query_timer; scalar_t__ multicast_startup_queries_sent; } ;

/* Variables and functions */
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ try_to_del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __br_multicast_enable_port(struct net_bridge_port *port)
{
	port->multicast_startup_queries_sent = 0;

	if (try_to_del_timer_sync(&port->multicast_query_timer) >= 0 ||
	    del_timer(&port->multicast_query_timer))
		mod_timer(&port->multicast_query_timer, jiffies);
}