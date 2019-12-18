#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
struct jme_adapter {int reg_txpfc; int reg_rxmcs; int /*<<< orphan*/  phy_lock; TYPE_1__ mii_if; int /*<<< orphan*/  dev; } ;
struct ethtool_pauseparam {int tx_pause; int rx_pause; int autoneg; } ;

/* Variables and functions */
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int RXMCS_FLOWCTRL ; 
 int TXPFC_PF_EN ; 
 int jme_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
jme_get_pauseparam(struct net_device *netdev,
			struct ethtool_pauseparam *ecmd)
{
	struct jme_adapter *jme = netdev_priv(netdev);
	u32 val;

	ecmd->tx_pause = (jme->reg_txpfc & TXPFC_PF_EN) != 0;
	ecmd->rx_pause = (jme->reg_rxmcs & RXMCS_FLOWCTRL) != 0;

	spin_lock_bh(&jme->phy_lock);
	val = jme_mdio_read(jme->dev, jme->mii_if.phy_id, MII_ADVERTISE);
	spin_unlock_bh(&jme->phy_lock);

	ecmd->autoneg =
		(val & (ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM)) != 0;
}