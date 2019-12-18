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
struct atl2_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atl2_reinit_locked (struct atl2_adapter*) ; 
 struct atl2_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int atl2_nway_reset(struct net_device *netdev)
{
	struct atl2_adapter *adapter = netdev_priv(netdev);
	if (netif_running(netdev))
		atl2_reinit_locked(adapter);
	return 0;
}