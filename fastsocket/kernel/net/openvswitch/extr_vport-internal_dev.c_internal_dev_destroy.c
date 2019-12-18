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
struct vport {int dummy; } ;
struct netdev_vport {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_promiscuity (int /*<<< orphan*/ ,int) ; 
 struct netdev_vport* netdev_vport_priv (struct vport*) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  unregister_netdevice (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void internal_dev_destroy(struct vport *vport)
{
	struct netdev_vport *netdev_vport = netdev_vport_priv(vport);

	netif_stop_queue(netdev_vport->dev);
	rtnl_lock();
	dev_set_promiscuity(netdev_vport->dev, -1);

	/* unregister_netdevice() waits for an RCU grace period. */
	unregister_netdevice(netdev_vport->dev);

	rtnl_unlock();
}