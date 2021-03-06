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
typedef  scalar_t__ u32 ;
struct net_device {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_TSO ; 
 int /*<<< orphan*/  NETIF_F_TSO6 ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 

__attribute__((used)) static int ixgbevf_set_tso(struct net_device *netdev, u32 data)
{
	if (data) {
		netdev->features |= NETIF_F_TSO;
		netdev->features |= NETIF_F_TSO6;
	} else {
		netif_tx_stop_all_queues(netdev);
		netdev->features &= ~NETIF_F_TSO;
		netdev->features &= ~NETIF_F_TSO6;
		netif_tx_start_all_queues(netdev);
	}
	return 0;
}