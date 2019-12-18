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
struct veth_port {int lpar_map; int stopped_map; int /*<<< orphan*/  queue_lock; } ;
struct veth_lpar_connection {int remote_lp; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int HVMAXARCHITECTEDVIRTUALLANS ; 
 struct veth_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  veth_debug (char*,int,int /*<<< orphan*/ ,int) ; 
 struct net_device** veth_dev ; 

__attribute__((used)) static void veth_stop_queues(struct veth_lpar_connection *cnx)
{
	int i;

	for (i = 0; i < HVMAXARCHITECTEDVIRTUALLANS; i++) {
		struct net_device *dev = veth_dev[i];
		struct veth_port *port;

		if (! dev)
			continue;

		port = netdev_priv(dev);

		/* If this cnx is not on the vlan for this port, continue */
		if (! (port->lpar_map & (1 << cnx->remote_lp)))
			continue;

		spin_lock(&port->queue_lock);

		netif_stop_queue(dev);
		port->stopped_map |= (1 << cnx->remote_lp);

		veth_debug("cnx %d: stopped queue for %s, map = 0x%x.\n",
				cnx->remote_lp, dev->name, port->stopped_map);

		spin_unlock(&port->queue_lock);
	}
}