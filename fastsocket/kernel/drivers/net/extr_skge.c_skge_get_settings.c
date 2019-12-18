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
struct skge_port {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  advertising; struct skge_hw* hw; } ;
struct skge_hw {int /*<<< orphan*/  phy_addr; scalar_t__ copper; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  advertising; int /*<<< orphan*/  port; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  supported; int /*<<< orphan*/  transceiver; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skge_supported_modes (struct skge_hw*) ; 

__attribute__((used)) static int skge_get_settings(struct net_device *dev,
			     struct ethtool_cmd *ecmd)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;

	ecmd->transceiver = XCVR_INTERNAL;
	ecmd->supported = skge_supported_modes(hw);

	if (hw->copper) {
		ecmd->port = PORT_TP;
		ecmd->phy_address = hw->phy_addr;
	} else
		ecmd->port = PORT_FIBRE;

	ecmd->advertising = skge->advertising;
	ecmd->autoneg = skge->autoneg;
	ecmd->speed = skge->speed;
	ecmd->duplex = skge->duplex;
	return 0;
}