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
struct skge_port {int port; int /*<<< orphan*/  netdev; struct skge_hw* hw; } ;
struct skge_hw {scalar_t__ chip_id; int /*<<< orphan*/  phy_lock; struct net_device** dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_GENESIS ; 
 int /*<<< orphan*/  genesis_mac_init (struct skge_hw*,int) ; 
 int /*<<< orphan*/  genesis_reset (struct skge_hw*,int) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_set_multicast (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yukon_init (struct skge_hw*,int) ; 
 int /*<<< orphan*/  yukon_reset (struct skge_hw*,int) ; 

__attribute__((used)) static void skge_phy_reset(struct skge_port *skge)
{
	struct skge_hw *hw = skge->hw;
	int port = skge->port;
	struct net_device *dev = hw->dev[port];

	netif_stop_queue(skge->netdev);
	netif_carrier_off(skge->netdev);

	spin_lock_bh(&hw->phy_lock);
	if (hw->chip_id == CHIP_ID_GENESIS) {
		genesis_reset(hw, port);
		genesis_mac_init(hw, port);
	} else {
		yukon_reset(hw, port);
		yukon_init(hw, port);
	}
	spin_unlock_bh(&hw->phy_lock);

	skge_set_multicast(dev);
}