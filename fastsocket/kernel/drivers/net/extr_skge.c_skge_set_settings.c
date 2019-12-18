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
typedef  int u32 ;
struct skge_port {int duplex; int speed; scalar_t__ autoneg; int advertising; struct skge_hw* hw; } ;
struct skge_hw {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {scalar_t__ autoneg; int advertising; int speed; int duplex; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 int EINVAL ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  skge_down (struct net_device*) ; 
 int skge_supported_modes (struct skge_hw const*) ; 
 int skge_up (struct net_device*) ; 

__attribute__((used)) static int skge_set_settings(struct net_device *dev, struct ethtool_cmd *ecmd)
{
	struct skge_port *skge = netdev_priv(dev);
	const struct skge_hw *hw = skge->hw;
	u32 supported = skge_supported_modes(hw);
	int err = 0;

	if (ecmd->autoneg == AUTONEG_ENABLE) {
		ecmd->advertising = supported;
		skge->duplex = -1;
		skge->speed = -1;
	} else {
		u32 setting;

		switch (ecmd->speed) {
		case SPEED_1000:
			if (ecmd->duplex == DUPLEX_FULL)
				setting = SUPPORTED_1000baseT_Full;
			else if (ecmd->duplex == DUPLEX_HALF)
				setting = SUPPORTED_1000baseT_Half;
			else
				return -EINVAL;
			break;
		case SPEED_100:
			if (ecmd->duplex == DUPLEX_FULL)
				setting = SUPPORTED_100baseT_Full;
			else if (ecmd->duplex == DUPLEX_HALF)
				setting = SUPPORTED_100baseT_Half;
			else
				return -EINVAL;
			break;

		case SPEED_10:
			if (ecmd->duplex == DUPLEX_FULL)
				setting = SUPPORTED_10baseT_Full;
			else if (ecmd->duplex == DUPLEX_HALF)
				setting = SUPPORTED_10baseT_Half;
			else
				return -EINVAL;
			break;
		default:
			return -EINVAL;
		}

		if ((setting & supported) == 0)
			return -EINVAL;

		skge->speed = ecmd->speed;
		skge->duplex = ecmd->duplex;
	}

	skge->autoneg = ecmd->autoneg;
	skge->advertising = ecmd->advertising;

	if (netif_running(dev)) {
		skge_down(dev);
		err = skge_up(dev);
		if (err) {
			dev_close(dev);
			return err;
		}
	}

	return (0);
}