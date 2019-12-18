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
struct nes_vnic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_DBG_NIC_TX ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct nes_vnic* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_timer (struct nes_vnic*) ; 

__attribute__((used)) static void nes_netdev_tx_timeout(struct net_device *netdev)
{
	struct nes_vnic *nesvnic = netdev_priv(netdev);

	if (netif_msg_timer(nesvnic))
		nes_debug(NES_DBG_NIC_TX, "%s: tx timeout\n", netdev->name);
}