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
struct net_device {int flags; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {int /*<<< orphan*/  dmi_addr; struct dev_mc_list* next; } ;
struct atl1e_hw {int dummy; } ;
struct atl1e_adapter {struct atl1e_hw hw; } ;

/* Variables and functions */
 int AT_READ_REG (struct atl1e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1e_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AT_WRITE_REG_ARRAY (struct atl1e_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int MAC_CTRL_MC_ALL_EN ; 
 int MAC_CTRL_PROMIS_EN ; 
 int /*<<< orphan*/  REG_MAC_CTRL ; 
 int /*<<< orphan*/  REG_RX_HASH_TABLE ; 
 int atl1e_hash_mc_addr (struct atl1e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atl1e_hash_set (struct atl1e_hw*,int) ; 
 struct atl1e_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void atl1e_set_multi(struct net_device *netdev)
{
	struct atl1e_adapter *adapter = netdev_priv(netdev);
	struct atl1e_hw *hw = &adapter->hw;
	struct dev_mc_list *mc_ptr;
	u32 mac_ctrl_data = 0;
	u32 hash_value;

	/* Check for Promiscuous and All Multicast modes */
	mac_ctrl_data = AT_READ_REG(hw, REG_MAC_CTRL);

	if (netdev->flags & IFF_PROMISC) {
		mac_ctrl_data |= MAC_CTRL_PROMIS_EN;
	} else if (netdev->flags & IFF_ALLMULTI) {
		mac_ctrl_data |= MAC_CTRL_MC_ALL_EN;
		mac_ctrl_data &= ~MAC_CTRL_PROMIS_EN;
	} else {
		mac_ctrl_data &= ~(MAC_CTRL_PROMIS_EN | MAC_CTRL_MC_ALL_EN);
	}

	AT_WRITE_REG(hw, REG_MAC_CTRL, mac_ctrl_data);

	/* clear the old settings from the multicast hash table */
	AT_WRITE_REG(hw, REG_RX_HASH_TABLE, 0);
	AT_WRITE_REG_ARRAY(hw, REG_RX_HASH_TABLE, 1, 0);

	/* comoute mc addresses' hash value ,and put it into hash table */
	for (mc_ptr = netdev->mc_list; mc_ptr; mc_ptr = mc_ptr->next) {
		hash_value = atl1e_hash_mc_addr(hw, mc_ptr->dmi_addr);
		atl1e_hash_set(hw, hash_value);
	}
}