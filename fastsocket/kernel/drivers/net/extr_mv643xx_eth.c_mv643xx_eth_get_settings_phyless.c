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
struct mv643xx_eth_private {int dummy; } ;
struct ethtool_cmd {int speed; int maxtxpkt; int maxrxpkt; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  transceiver; scalar_t__ phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_MII ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int FULL_DUPLEX ; 
 int /*<<< orphan*/  PORT_MII ; 
#define  PORT_SPEED_10 130 
#define  PORT_SPEED_100 129 
#define  PORT_SPEED_1000 128 
 int PORT_SPEED_MASK ; 
 int /*<<< orphan*/  PORT_STATUS ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int /*<<< orphan*/  SUPPORTED_MII ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 int rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv643xx_eth_get_settings_phyless(struct mv643xx_eth_private *mp,
				 struct ethtool_cmd *cmd)
{
	u32 port_status;

	port_status = rdlp(mp, PORT_STATUS);

	cmd->supported = SUPPORTED_MII;
	cmd->advertising = ADVERTISED_MII;
	switch (port_status & PORT_SPEED_MASK) {
	case PORT_SPEED_10:
		cmd->speed = SPEED_10;
		break;
	case PORT_SPEED_100:
		cmd->speed = SPEED_100;
		break;
	case PORT_SPEED_1000:
		cmd->speed = SPEED_1000;
		break;
	default:
		cmd->speed = -1;
		break;
	}
	cmd->duplex = (port_status & FULL_DUPLEX) ? DUPLEX_FULL : DUPLEX_HALF;
	cmd->port = PORT_MII;
	cmd->phy_address = 0;
	cmd->transceiver = XCVR_INTERNAL;
	cmd->autoneg = AUTONEG_DISABLE;
	cmd->maxtxpkt = 1;
	cmd->maxrxpkt = 1;

	return 0;
}