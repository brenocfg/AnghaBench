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
struct net_device {int /*<<< orphan*/  name; } ;
struct ehea_port {int /*<<< orphan*/  flags; int /*<<< orphan*/  port_lock; int /*<<< orphan*/  stats_work; int /*<<< orphan*/  reset_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  __EHEA_DISABLE_PORT_RESET ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ehea_down (struct net_device*) ; 
 int /*<<< orphan*/  ehea_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_ifdown (struct ehea_port*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  port_napi_disable (struct ehea_port*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ehea_stop(struct net_device *dev)
{
	int ret;
	struct ehea_port *port = netdev_priv(dev);

	if (netif_msg_ifdown(port))
		ehea_info("disabling port %s", dev->name);

	set_bit(__EHEA_DISABLE_PORT_RESET, &port->flags);
	cancel_work_sync(&port->reset_task);
	cancel_delayed_work_sync(&port->stats_work);
	mutex_lock(&port->port_lock);
	netif_tx_stop_all_queues(dev);
	port_napi_disable(port);
	ret = ehea_down(dev);
	mutex_unlock(&port->port_lock);
	clear_bit(__EHEA_DISABLE_PORT_RESET, &port->flags);
	return ret;
}