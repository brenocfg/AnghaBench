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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct e1000_adapter {int /*<<< orphan*/  rx_csum; } ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_reinit_locked (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_reset (struct e1000_adapter*) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int e1000_set_rx_csum(struct net_device *netdev, u32 data)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	adapter->rx_csum = data;

	if (netif_running(netdev))
		e1000_reinit_locked(adapter);
	else
		e1000_reset(adapter);
	return 0;
}