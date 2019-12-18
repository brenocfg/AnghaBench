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
struct port_info {int link_fault; } ;
struct net_device {int dummy; } ;
struct adapter {int /*<<< orphan*/  work_lock; struct net_device** port; } ;

/* Variables and functions */
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void t3_os_link_fault_handler(struct adapter *adapter, int port_id)
{
	struct net_device *netdev = adapter->port[port_id];
	struct port_info *pi = netdev_priv(netdev);

	spin_lock(&adapter->work_lock);
	pi->link_fault = 1;
	spin_unlock(&adapter->work_lock);
}