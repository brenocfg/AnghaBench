#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qlcnic_adapter {TYPE_1__* ahw; struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int linkup; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

void qlcnic_advert_link_change(struct qlcnic_adapter *adapter, int linkup)
{
	struct net_device *netdev = adapter->netdev;

	if (adapter->ahw->linkup && !linkup) {
		netdev_info(netdev, "NIC Link is down\n");
		adapter->ahw->linkup = 0;
		if (netif_running(netdev)) {
			netif_carrier_off(netdev);
			netif_stop_queue(netdev);
		}
	} else if (!adapter->ahw->linkup && linkup) {
		netdev_info(netdev, "NIC Link is up\n");
		adapter->ahw->linkup = 1;
		if (netif_running(netdev)) {
			netif_carrier_on(netdev);
			netif_wake_queue(netdev);
		}
	}
}