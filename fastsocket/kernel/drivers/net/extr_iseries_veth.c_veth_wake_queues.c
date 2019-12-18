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
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  veth_debug (char*,int,int /*<<< orphan*/ ) ; 
 struct net_device** veth_dev ; 

__attribute__((used)) static void veth_wake_queues(struct veth_lpar_connection *cnx)
{
	int i;

	for (i = 0; i < HVMAXARCHITECTEDVIRTUALLANS; i++) {
		struct net_device *dev = veth_dev[i];
		struct veth_port *port;
		unsigned long flags;

		if (! dev)
			continue;

		port = netdev_priv(dev);

		if (! (port->lpar_map & (1<<cnx->remote_lp)))
			continue;

		spin_lock_irqsave(&port->queue_lock, flags);

		port->stopped_map &= ~(1 << cnx->remote_lp);

		if (0 == port->stopped_map && netif_queue_stopped(dev)) {
			veth_debug("cnx %d: woke queue for %s.\n",
					cnx->remote_lp, dev->name);
			netif_wake_queue(dev);
		}
		spin_unlock_irqrestore(&port->queue_lock, flags);
	}
}