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
struct ethtool_cmd {int supported; int advertising; void* duplex; void* speed; void* autoneg; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  transceiver; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_MII ; 
 int ADVERTISED_Pause ; 
 int ADVERTISED_TP ; 
 void* AUTONEG_DISABLE ; 
 void* AUTONEG_ENABLE ; 
 void* DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 int EOPNOTSUPP ; 
#define  KS8695_DTYPE_HPNA 130 
#define  KS8695_DTYPE_LAN 129 
#define  KS8695_DTYPE_WAN 128 
 scalar_t__ KS8695_WMC ; 
 int /*<<< orphan*/  PORT_MII ; 
 void* SPEED_10 ; 
 void* SPEED_100 ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_MII ; 
 int SUPPORTED_Pause ; 
 int SUPPORTED_TP ; 
 int WMC_WANA100F ; 
 int WMC_WANA100H ; 
 int WMC_WANA10F ; 
 int WMC_WANA10H ; 
 int WMC_WANAP ; 
 int WMC_WAND ; 
 int WMC_WANF100 ; 
 int WMC_WANFF ; 
 int WMC_WDS ; 
 int WMC_WSS ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 struct ks8695_priv* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int
ks8695_get_settings(struct net_device *ndev, struct ethtool_cmd *cmd)
{
	struct ks8695_priv *ksp = netdev_priv(ndev);
	u32 ctrl;

	/* All ports on the KS8695 support these... */
	cmd->supported = (SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
			  SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
			  SUPPORTED_TP | SUPPORTED_MII);
	cmd->transceiver = XCVR_INTERNAL;

	/* Port specific extras */
	switch (ksp->dtype) {
	case KS8695_DTYPE_HPNA:
		cmd->phy_address = 0;
		/* not supported for HPNA */
		cmd->autoneg = AUTONEG_DISABLE;

		/* BUG: Erm, dtype hpna implies no phy regs */
		/*
		ctrl = readl(KS8695_MISC_VA + KS8695_HMC);
		cmd->speed = (ctrl & HMC_HSS) ? SPEED_100 : SPEED_10;
		cmd->duplex = (ctrl & HMC_HDS) ? DUPLEX_FULL : DUPLEX_HALF;
		*/
		return -EOPNOTSUPP;
	case KS8695_DTYPE_WAN:
		cmd->advertising = ADVERTISED_TP | ADVERTISED_MII;
		cmd->port = PORT_MII;
		cmd->supported |= (SUPPORTED_Autoneg | SUPPORTED_Pause);
		cmd->phy_address = 0;

		ctrl = readl(ksp->phyiface_regs + KS8695_WMC);
		if ((ctrl & WMC_WAND) == 0) {
			/* auto-negotiation is enabled */
			cmd->advertising |= ADVERTISED_Autoneg;
			if (ctrl & WMC_WANA100F)
				cmd->advertising |= ADVERTISED_100baseT_Full;
			if (ctrl & WMC_WANA100H)
				cmd->advertising |= ADVERTISED_100baseT_Half;
			if (ctrl & WMC_WANA10F)
				cmd->advertising |= ADVERTISED_10baseT_Full;
			if (ctrl & WMC_WANA10H)
				cmd->advertising |= ADVERTISED_10baseT_Half;
			if (ctrl & WMC_WANAP)
				cmd->advertising |= ADVERTISED_Pause;
			cmd->autoneg = AUTONEG_ENABLE;

			cmd->speed = (ctrl & WMC_WSS) ? SPEED_100 : SPEED_10;
			cmd->duplex = (ctrl & WMC_WDS) ?
				DUPLEX_FULL : DUPLEX_HALF;
		} else {
			/* auto-negotiation is disabled */
			cmd->autoneg = AUTONEG_DISABLE;

			cmd->speed = (ctrl & WMC_WANF100) ?
				SPEED_100 : SPEED_10;
			cmd->duplex = (ctrl & WMC_WANFF) ?
				DUPLEX_FULL : DUPLEX_HALF;
		}
		break;
	case KS8695_DTYPE_LAN:
		return -EOPNOTSUPP;
	}

	return 0;
}