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
struct net_bridge_port {struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  multicast_lock; int /*<<< orphan*/  dev; scalar_t__ multicast_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  __br_multicast_enable_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void br_multicast_enable_port(struct net_bridge_port *port)
{
	struct net_bridge *br = port->br;

	spin_lock(&br->multicast_lock);
	if (br->multicast_disabled || !netif_running(br->dev))
		goto out;

	__br_multicast_enable_port(port);

out:
	spin_unlock(&br->multicast_lock);
}