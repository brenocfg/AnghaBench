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
struct ks8842_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_P1MBSR ; 
 int ks8842_read16 (struct ks8842_adapter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void ks8842_update_link_status(struct net_device *netdev,
	struct ks8842_adapter *adapter)
{
	/* check the status of the link */
	if (ks8842_read16(adapter, 45, REG_P1MBSR) & 0x4) {
		netif_carrier_on(netdev);
		netif_wake_queue(netdev);
	} else {
		netif_stop_queue(netdev);
		netif_carrier_off(netdev);
	}
}