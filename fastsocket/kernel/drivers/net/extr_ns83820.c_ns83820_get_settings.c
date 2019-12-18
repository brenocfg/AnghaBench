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
struct ns83820 {int CFG_cache; scalar_t__ base; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int supported; int autoneg; int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 scalar_t__ CFG ; 
 int CFG_DUPSTS ; 
 int CFG_SPDSTS0 ; 
 int CFG_TBI_EN ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 struct ns83820* PRIV (struct net_device*) ; 
 int SPDSTS_POLARITY ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 scalar_t__ TANAR ; 
 scalar_t__ TBICR ; 
 int TBICR_MR_AN_ENABLE ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int ns83820_get_settings(struct net_device *ndev,
				struct ethtool_cmd *cmd)
{
	struct ns83820 *dev = PRIV(ndev);
	u32 cfg, tanar, tbicr;
	int have_optical = 0;
	int fullduplex   = 0;

	/*
	 * Here's the list of available ethtool commands from other drivers:
	 *	cmd->advertising =
	 *	cmd->speed =
	 *	cmd->duplex =
	 *	cmd->port = 0;
	 *	cmd->phy_address =
	 *	cmd->transceiver = 0;
	 *	cmd->autoneg =
	 *	cmd->maxtxpkt = 0;
	 *	cmd->maxrxpkt = 0;
	 */

	/* read current configuration */
	cfg   = readl(dev->base + CFG) ^ SPDSTS_POLARITY;
	tanar = readl(dev->base + TANAR);
	tbicr = readl(dev->base + TBICR);

	if (dev->CFG_cache & CFG_TBI_EN) {
		/* we have an optical interface */
		have_optical = 1;
		fullduplex = (cfg & CFG_DUPSTS) ? 1 : 0;

	} else {
		/* We have copper */
		fullduplex = (cfg & CFG_DUPSTS) ? 1 : 0;
        }

	cmd->supported = SUPPORTED_Autoneg;

	/* we have optical interface */
	if (dev->CFG_cache & CFG_TBI_EN) {
		cmd->supported |= SUPPORTED_1000baseT_Half |
					SUPPORTED_1000baseT_Full |
					SUPPORTED_FIBRE;
		cmd->port       = PORT_FIBRE;
	} /* TODO: else copper related  support */

	cmd->duplex = fullduplex ? DUPLEX_FULL : DUPLEX_HALF;
	switch (cfg / CFG_SPDSTS0 & 3) {
	case 2:
		cmd->speed = SPEED_1000;
		break;
	case 1:
		cmd->speed = SPEED_100;
		break;
	default:
		cmd->speed = SPEED_10;
		break;
	}
	cmd->autoneg = (tbicr & TBICR_MR_AN_ENABLE) ? 1: 0;
	return 0;
}