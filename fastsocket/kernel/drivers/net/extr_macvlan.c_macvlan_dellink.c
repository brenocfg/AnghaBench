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
struct net_device {int dummy; } ;
struct macvlan_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  vlans; } ;
struct macvlan_dev {int /*<<< orphan*/  list; struct macvlan_port* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macvlan_port_destroy (int /*<<< orphan*/ ) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

void macvlan_dellink(struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct macvlan_port *port = vlan->port;

	list_del_rcu(&vlan->list);
	unregister_netdevice(dev);

	if (list_empty(&port->vlans))
		macvlan_port_destroy(port->dev);
}