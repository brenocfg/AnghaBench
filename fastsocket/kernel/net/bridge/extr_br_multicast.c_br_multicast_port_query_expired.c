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
struct net_bridge_port {scalar_t__ state; scalar_t__ multicast_startup_queries_sent; struct net_bridge* br; } ;
struct net_bridge {scalar_t__ multicast_startup_query_count; int /*<<< orphan*/  multicast_lock; } ;

/* Variables and functions */
 scalar_t__ BR_STATE_BLOCKING ; 
 scalar_t__ BR_STATE_DISABLED ; 
 int /*<<< orphan*/  br_multicast_send_query (struct net_bridge*,struct net_bridge_port*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_multicast_port_query_expired(unsigned long data)
{
	struct net_bridge_port *port = (void *)data;
	struct net_bridge *br = port->br;

	spin_lock(&br->multicast_lock);
	if (port->state == BR_STATE_DISABLED ||
	    port->state == BR_STATE_BLOCKING)
		goto out;

	if (port->multicast_startup_queries_sent <
	    br->multicast_startup_query_count)
		port->multicast_startup_queries_sent++;

	br_multicast_send_query(port->br, port,
				port->multicast_startup_queries_sent);

out:
	spin_unlock(&br->multicast_lock);
}