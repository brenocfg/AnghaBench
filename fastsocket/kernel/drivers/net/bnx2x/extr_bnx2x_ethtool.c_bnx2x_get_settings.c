#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int supported; scalar_t__ maxrxpkt; scalar_t__ maxtxpkt; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  advertising; int /*<<< orphan*/  cmd; int /*<<< orphan*/  lp_advertising; } ;
struct TYPE_10__ {int link_status; int /*<<< orphan*/  line_speed; int /*<<< orphan*/  duplex; scalar_t__ link_up; } ;
struct TYPE_9__ {scalar_t__* req_line_speed; TYPE_2__* phy; } ;
struct TYPE_8__ {int /*<<< orphan*/  prtad; } ;
struct TYPE_6__ {int* supported; int /*<<< orphan*/ * advertising; } ;
struct bnx2x {scalar_t__ state; int flags; TYPE_5__ link_vars; TYPE_4__ link_params; TYPE_3__ mdio; TYPE_1__ port; } ;
struct TYPE_7__ {scalar_t__ media_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_10000baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_1000baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_1000baseT_Half ; 
 int /*<<< orphan*/  ADVERTISED_100baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_100baseT_Half ; 
 int /*<<< orphan*/  ADVERTISED_10baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_10baseT_Half ; 
 int /*<<< orphan*/  ADVERTISED_20000baseKR2_Full ; 
 int /*<<< orphan*/  ADVERTISED_2500baseX_Full ; 
 int /*<<< orphan*/  ADVERTISED_Asym_Pause ; 
 int /*<<< orphan*/  ADVERTISED_Autoneg ; 
 int /*<<< orphan*/  ADVERTISED_Pause ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  BNX2X_MSG_ETHTOOL ; 
 scalar_t__ BNX2X_STATE_OPEN ; 
 int /*<<< orphan*/  BP_NOMCP (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 scalar_t__ ETH_PHY_SFP_1G_FIBER ; 
 scalar_t__ IS_MF (struct bnx2x*) ; 
 int LINK_STATUS_AUTO_NEGOTIATE_COMPLETE ; 
 int LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_10THD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_20GXFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_2500XFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE ; 
 int LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE ; 
 int MF_FUNC_DIS ; 
 scalar_t__ SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 size_t bnx2x_get_cur_phy_idx (struct bnx2x*) ; 
 int bnx2x_get_link_cfg_idx (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_get_mf_speed (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_get_port_type (struct bnx2x*) ; 
 int /*<<< orphan*/  ethtool_cmd_speed (struct ethtool_cmd*) ; 
 int /*<<< orphan*/  ethtool_cmd_speed_set (struct ethtool_cmd*,int /*<<< orphan*/ ) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnx2x_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct bnx2x *bp = netdev_priv(dev);
	int cfg_idx = bnx2x_get_link_cfg_idx(bp);

	/* Dual Media boards present all available port types */
	cmd->supported = bp->port.supported[cfg_idx] |
		(bp->port.supported[cfg_idx ^ 1] &
		 (SUPPORTED_TP | SUPPORTED_FIBRE));
	cmd->advertising = bp->port.advertising[cfg_idx];
	if (bp->link_params.phy[bnx2x_get_cur_phy_idx(bp)].media_type ==
	    ETH_PHY_SFP_1G_FIBER) {
		cmd->supported &= ~(SUPPORTED_10000baseT_Full);
		cmd->advertising &= ~(ADVERTISED_10000baseT_Full);
	}

	if ((bp->state == BNX2X_STATE_OPEN) && bp->link_vars.link_up &&
	    !(bp->flags & MF_FUNC_DIS)) {
		cmd->duplex = bp->link_vars.duplex;

		if (IS_MF(bp) && !BP_NOMCP(bp))
			ethtool_cmd_speed_set(cmd, bnx2x_get_mf_speed(bp));
		else
			ethtool_cmd_speed_set(cmd, bp->link_vars.line_speed);
	} else {
		cmd->duplex = DUPLEX_UNKNOWN;
		ethtool_cmd_speed_set(cmd, SPEED_UNKNOWN);
	}

	cmd->port = bnx2x_get_port_type(bp);

	cmd->phy_address = bp->mdio.prtad;
	cmd->transceiver = XCVR_INTERNAL;

	if (bp->link_params.req_line_speed[cfg_idx] == SPEED_AUTO_NEG)
		cmd->autoneg = AUTONEG_ENABLE;
	else
		cmd->autoneg = AUTONEG_DISABLE;

	/* Publish LP advertised speeds and FC */
	if (bp->link_vars.link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE) {
		u32 status = bp->link_vars.link_status;

		cmd->lp_advertising |= ADVERTISED_Autoneg;
		if (status & LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE)
			cmd->lp_advertising |= ADVERTISED_Pause;
		if (status & LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE)
			cmd->lp_advertising |= ADVERTISED_Asym_Pause;

		if (status & LINK_STATUS_LINK_PARTNER_10THD_CAPABLE)
			cmd->lp_advertising |= ADVERTISED_10baseT_Half;
		if (status & LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE)
			cmd->lp_advertising |= ADVERTISED_10baseT_Full;
		if (status & LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE)
			cmd->lp_advertising |= ADVERTISED_100baseT_Half;
		if (status & LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE)
			cmd->lp_advertising |= ADVERTISED_100baseT_Full;
		if (status & LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE)
			cmd->lp_advertising |= ADVERTISED_1000baseT_Half;
		if (status & LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE)
			cmd->lp_advertising |= ADVERTISED_1000baseT_Full;
		if (status & LINK_STATUS_LINK_PARTNER_2500XFD_CAPABLE)
			cmd->lp_advertising |= ADVERTISED_2500baseX_Full;
		if (status & LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE)
			cmd->lp_advertising |= ADVERTISED_10000baseT_Full;
		if (status & LINK_STATUS_LINK_PARTNER_20GXFD_CAPABLE)
			cmd->lp_advertising |= ADVERTISED_20000baseKR2_Full;
	}

	cmd->maxtxpkt = 0;
	cmd->maxrxpkt = 0;

	DP(BNX2X_MSG_ETHTOOL, "ethtool_cmd: cmd %d\n"
	   "  supported 0x%x  advertising 0x%x  speed %u\n"
	   "  duplex %d  port %d  phy_address %d  transceiver %d\n"
	   "  autoneg %d  maxtxpkt %d  maxrxpkt %d\n",
	   cmd->cmd, cmd->supported, cmd->advertising,
	   ethtool_cmd_speed(cmd),
	   cmd->duplex, cmd->port, cmd->phy_address, cmd->transceiver,
	   cmd->autoneg, cmd->maxtxpkt, cmd->maxrxpkt);

	return 0;
}