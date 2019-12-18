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
typedef  int u16 ;
struct net_device {int dummy; } ;
struct atl1_hw {int media_type; } ;
struct atl1_adapter {struct atl1_hw hw; } ;

/* Variables and functions */
 int MEDIA_TYPE_1000M_FULL ; 
#define  MEDIA_TYPE_100M_FULL 130 
#define  MEDIA_TYPE_100M_HALF 129 
#define  MEDIA_TYPE_10M_FULL 128 
 int MEDIA_TYPE_AUTO_SENSOR ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int MII_CR_AUTO_NEG_EN ; 
 int MII_CR_FULL_DUPLEX ; 
 int MII_CR_RESET ; 
 int MII_CR_SPEED_10 ; 
 int MII_CR_SPEED_100 ; 
 int /*<<< orphan*/  atl1_down (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atl1_up (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atl1_write_phy_reg (struct atl1_hw*,int /*<<< orphan*/ ,int) ; 
 struct atl1_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int atl1_nway_reset(struct net_device *netdev)
{
	struct atl1_adapter *adapter = netdev_priv(netdev);
	struct atl1_hw *hw = &adapter->hw;

	if (netif_running(netdev)) {
		u16 phy_data;
		atl1_down(adapter);

		if (hw->media_type == MEDIA_TYPE_AUTO_SENSOR ||
			hw->media_type == MEDIA_TYPE_1000M_FULL) {
			phy_data = MII_CR_RESET | MII_CR_AUTO_NEG_EN;
		} else {
			switch (hw->media_type) {
			case MEDIA_TYPE_100M_FULL:
				phy_data = MII_CR_FULL_DUPLEX |
					MII_CR_SPEED_100 | MII_CR_RESET;
				break;
			case MEDIA_TYPE_100M_HALF:
				phy_data = MII_CR_SPEED_100 | MII_CR_RESET;
				break;
			case MEDIA_TYPE_10M_FULL:
				phy_data = MII_CR_FULL_DUPLEX |
					MII_CR_SPEED_10 | MII_CR_RESET;
				break;
			default:
				/* MEDIA_TYPE_10M_HALF */
				phy_data = MII_CR_SPEED_10 | MII_CR_RESET;
			}
		}
		atl1_write_phy_reg(hw, MII_BMCR, phy_data);
		atl1_up(adapter);
	}
	return 0;
}