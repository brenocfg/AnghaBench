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
struct igb_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  igb_reinit_locked (struct igb_adapter*) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int igb_nway_reset(struct net_device *netdev)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	if (netif_running(netdev))
		igb_reinit_locked(adapter);
	return 0;
}