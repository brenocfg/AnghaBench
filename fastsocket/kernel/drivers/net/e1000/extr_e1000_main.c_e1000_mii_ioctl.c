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
typedef  int u16 ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {int reg_num; int val_in; int /*<<< orphan*/  val_out; int /*<<< orphan*/  phy_id; } ;
struct ifreq {int dummy; } ;
struct e1000_hw {scalar_t__ media_type; int autoneg; int autoneg_advertised; int /*<<< orphan*/  phy_addr; } ;
struct e1000_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/  stats_lock; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int E1000_SUCCESS ; 
 int EFAULT ; 
 int EIO ; 
 int EOPNOTSUPP ; 
#define  M88E1000_EXT_PHY_SPEC_CTRL 133 
#define  M88E1000_PHY_SPEC_CTRL 132 
 int MII_CR_AUTO_NEG_EN ; 
 int MII_CR_POWER_DOWN ; 
#define  PHY_CTRL 131 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_phy_reset (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_read_phy_reg (struct e1000_hw*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_reinit_locked (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_reset (struct e1000_adapter*) ; 
 int e1000_set_spd_dplx (struct e1000_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_write_phy_reg (struct e1000_hw*,int,int) ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int e1000_mii_ioctl(struct net_device *netdev, struct ifreq *ifr,
			   int cmd)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	struct mii_ioctl_data *data = if_mii(ifr);
	int retval;
	u16 mii_reg;
	unsigned long flags;

	if (hw->media_type != e1000_media_type_copper)
		return -EOPNOTSUPP;

	switch (cmd) {
	case SIOCGMIIPHY:
		data->phy_id = hw->phy_addr;
		break;
	case SIOCGMIIREG:
		spin_lock_irqsave(&adapter->stats_lock, flags);
		if (e1000_read_phy_reg(hw, data->reg_num & 0x1F,
				   &data->val_out)) {
			spin_unlock_irqrestore(&adapter->stats_lock, flags);
			return -EIO;
		}
		spin_unlock_irqrestore(&adapter->stats_lock, flags);
		break;
	case SIOCSMIIREG:
		if (data->reg_num & ~(0x1F))
			return -EFAULT;
		mii_reg = data->val_in;
		spin_lock_irqsave(&adapter->stats_lock, flags);
		if (e1000_write_phy_reg(hw, data->reg_num,
					mii_reg)) {
			spin_unlock_irqrestore(&adapter->stats_lock, flags);
			return -EIO;
		}
		spin_unlock_irqrestore(&adapter->stats_lock, flags);
		if (hw->media_type == e1000_media_type_copper) {
			switch (data->reg_num) {
			case PHY_CTRL:
				if (mii_reg & MII_CR_POWER_DOWN)
					break;
				if (mii_reg & MII_CR_AUTO_NEG_EN) {
					hw->autoneg = 1;
					hw->autoneg_advertised = 0x2F;
				} else {
					u32 speed;
					if (mii_reg & 0x40)
						speed = SPEED_1000;
					else if (mii_reg & 0x2000)
						speed = SPEED_100;
					else
						speed = SPEED_10;
					retval = e1000_set_spd_dplx(
						adapter, speed,
						((mii_reg & 0x100)
						 ? DUPLEX_FULL :
						 DUPLEX_HALF));
					if (retval)
						return retval;
				}
				if (netif_running(adapter->netdev))
					e1000_reinit_locked(adapter);
				else
					e1000_reset(adapter);
				break;
			case M88E1000_PHY_SPEC_CTRL:
			case M88E1000_EXT_PHY_SPEC_CTRL:
				if (e1000_phy_reset(hw))
					return -EIO;
				break;
			}
		} else {
			switch (data->reg_num) {
			case PHY_CTRL:
				if (mii_reg & MII_CR_POWER_DOWN)
					break;
				if (netif_running(adapter->netdev))
					e1000_reinit_locked(adapter);
				else
					e1000_reset(adapter);
				break;
			}
		}
		break;
	default:
		return -EOPNOTSUPP;
	}
	return E1000_SUCCESS;
}