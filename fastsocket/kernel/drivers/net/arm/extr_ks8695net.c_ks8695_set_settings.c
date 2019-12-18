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
struct net_device {int dummy; } ;
struct ks8695_priv {int dtype; scalar_t__ phyiface_regs; } ;
struct ethtool_cmd {scalar_t__ speed; scalar_t__ duplex; scalar_t__ port; scalar_t__ transceiver; scalar_t__ autoneg; int advertising; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  KS8695_DTYPE_HPNA 130 
#define  KS8695_DTYPE_LAN 129 
#define  KS8695_DTYPE_WAN 128 
 scalar_t__ KS8695_WMC ; 
 scalar_t__ PORT_MII ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int WMC_WANA100F ; 
 int WMC_WANA100H ; 
 int WMC_WANA10F ; 
 int WMC_WANA10H ; 
 int WMC_WAND ; 
 int WMC_WANF100 ; 
 int WMC_WANFF ; 
 int WMC_WANR ; 
 scalar_t__ XCVR_INTERNAL ; 
 struct ks8695_priv* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int
ks8695_set_settings(struct net_device *ndev, struct ethtool_cmd *cmd)
{
	struct ks8695_priv *ksp = netdev_priv(ndev);
	u32 ctrl;

	if ((cmd->speed != SPEED_10) && (cmd->speed != SPEED_100))
		return -EINVAL;
	if ((cmd->duplex != DUPLEX_HALF) && (cmd->duplex != DUPLEX_FULL))
		return -EINVAL;
	if (cmd->port != PORT_MII)
		return -EINVAL;
	if (cmd->transceiver != XCVR_INTERNAL)
		return -EINVAL;
	if ((cmd->autoneg != AUTONEG_DISABLE) &&
	    (cmd->autoneg != AUTONEG_ENABLE))
		return -EINVAL;

	if (cmd->autoneg == AUTONEG_ENABLE) {
		if ((cmd->advertising & (ADVERTISED_10baseT_Half |
				ADVERTISED_10baseT_Full |
				ADVERTISED_100baseT_Half |
				ADVERTISED_100baseT_Full)) == 0)
			return -EINVAL;

		switch (ksp->dtype) {
		case KS8695_DTYPE_HPNA:
			/* HPNA does not support auto-negotiation. */
			return -EINVAL;
		case KS8695_DTYPE_WAN:
			ctrl = readl(ksp->phyiface_regs + KS8695_WMC);

			ctrl &= ~(WMC_WAND | WMC_WANA100F | WMC_WANA100H |
				  WMC_WANA10F | WMC_WANA10H);
			if (cmd->advertising & ADVERTISED_100baseT_Full)
				ctrl |= WMC_WANA100F;
			if (cmd->advertising & ADVERTISED_100baseT_Half)
				ctrl |= WMC_WANA100H;
			if (cmd->advertising & ADVERTISED_10baseT_Full)
				ctrl |= WMC_WANA10F;
			if (cmd->advertising & ADVERTISED_10baseT_Half)
				ctrl |= WMC_WANA10H;

			/* force a re-negotiation */
			ctrl |= WMC_WANR;
			writel(ctrl, ksp->phyiface_regs + KS8695_WMC);
			break;
		case KS8695_DTYPE_LAN:
			return -EOPNOTSUPP;
		}

	} else {
		switch (ksp->dtype) {
		case KS8695_DTYPE_HPNA:
			/* BUG: dtype_hpna implies no phy registers */
			/*
			ctrl = __raw_readl(KS8695_MISC_VA + KS8695_HMC);

			ctrl &= ~(HMC_HSS | HMC_HDS);
			if (cmd->speed == SPEED_100)
				ctrl |= HMC_HSS;
			if (cmd->duplex == DUPLEX_FULL)
				ctrl |= HMC_HDS;

			__raw_writel(ctrl, KS8695_MISC_VA + KS8695_HMC);
			*/
			return -EOPNOTSUPP;
		case KS8695_DTYPE_WAN:
			ctrl = readl(ksp->phyiface_regs + KS8695_WMC);

			/* disable auto-negotiation */
			ctrl |= WMC_WAND;
			ctrl &= ~(WMC_WANF100 | WMC_WANFF);

			if (cmd->speed == SPEED_100)
				ctrl |= WMC_WANF100;
			if (cmd->duplex == DUPLEX_FULL)
				ctrl |= WMC_WANFF;

			writel(ctrl, ksp->phyiface_regs + KS8695_WMC);
			break;
		case KS8695_DTYPE_LAN:
			return -EOPNOTSUPP;
		}
	}

	return 0;
}