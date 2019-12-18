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
struct TYPE_2__ {scalar_t__ type; int link_type; scalar_t__ guestlan; } ;
struct qeth_card {TYPE_1__ info; } ;
struct net_device {struct qeth_card* ml_priv; } ;
struct ethtool_cmd {int supported; int advertising; void* port; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  transceiver; } ;
typedef  enum qeth_link_types { ____Placeholder_qeth_link_types } qeth_link_types ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_FIBRE ; 
 int ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 void* PORT_FIBRE ; 
 void* PORT_TP ; 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
#define  QETH_LINK_TYPE_10GBIT_ETH 132 
#define  QETH_LINK_TYPE_FAST_ETH 131 
#define  QETH_LINK_TYPE_GBIT_ETH 130 
#define  QETH_LINK_TYPE_LANE_ETH100 129 
#define  QETH_LINK_TYPE_LANE_ETH1000 128 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 

int qeth_core_ethtool_get_settings(struct net_device *netdev,
					struct ethtool_cmd *ecmd)
{
	struct qeth_card *card = netdev->ml_priv;
	enum qeth_link_types link_type;

	if ((card->info.type == QETH_CARD_TYPE_IQD) || (card->info.guestlan))
		link_type = QETH_LINK_TYPE_10GBIT_ETH;
	else
		link_type = card->info.link_type;

	ecmd->transceiver = XCVR_INTERNAL;
	ecmd->supported = SUPPORTED_Autoneg;
	ecmd->advertising = ADVERTISED_Autoneg;
	ecmd->duplex = DUPLEX_FULL;
	ecmd->autoneg = AUTONEG_ENABLE;

	switch (link_type) {
	case QETH_LINK_TYPE_FAST_ETH:
	case QETH_LINK_TYPE_LANE_ETH100:
		ecmd->supported |= SUPPORTED_10baseT_Half |
					SUPPORTED_10baseT_Full |
					SUPPORTED_100baseT_Half |
					SUPPORTED_100baseT_Full |
					SUPPORTED_TP;
		ecmd->advertising |= ADVERTISED_10baseT_Half |
					ADVERTISED_10baseT_Full |
					ADVERTISED_100baseT_Half |
					ADVERTISED_100baseT_Full |
					ADVERTISED_TP;
		ecmd->speed = SPEED_100;
		ecmd->port = PORT_TP;
		break;

	case QETH_LINK_TYPE_GBIT_ETH:
	case QETH_LINK_TYPE_LANE_ETH1000:
		ecmd->supported |= SUPPORTED_10baseT_Half |
					SUPPORTED_10baseT_Full |
					SUPPORTED_100baseT_Half |
					SUPPORTED_100baseT_Full |
					SUPPORTED_1000baseT_Half |
					SUPPORTED_1000baseT_Full |
					SUPPORTED_FIBRE;
		ecmd->advertising |= ADVERTISED_10baseT_Half |
					ADVERTISED_10baseT_Full |
					ADVERTISED_100baseT_Half |
					ADVERTISED_100baseT_Full |
					ADVERTISED_1000baseT_Half |
					ADVERTISED_1000baseT_Full |
					ADVERTISED_FIBRE;
		ecmd->speed = SPEED_1000;
		ecmd->port = PORT_FIBRE;
		break;

	case QETH_LINK_TYPE_10GBIT_ETH:
		ecmd->supported |= SUPPORTED_10baseT_Half |
					SUPPORTED_10baseT_Full |
					SUPPORTED_100baseT_Half |
					SUPPORTED_100baseT_Full |
					SUPPORTED_1000baseT_Half |
					SUPPORTED_1000baseT_Full |
					SUPPORTED_10000baseT_Full |
					SUPPORTED_FIBRE;
		ecmd->advertising |= ADVERTISED_10baseT_Half |
					ADVERTISED_10baseT_Full |
					ADVERTISED_100baseT_Half |
					ADVERTISED_100baseT_Full |
					ADVERTISED_1000baseT_Half |
					ADVERTISED_1000baseT_Full |
					ADVERTISED_10000baseT_Full |
					ADVERTISED_FIBRE;
		ecmd->speed = SPEED_10000;
		ecmd->port = PORT_FIBRE;
		break;

	default:
		ecmd->supported |= SUPPORTED_10baseT_Half |
					SUPPORTED_10baseT_Full |
					SUPPORTED_TP;
		ecmd->advertising |= ADVERTISED_10baseT_Half |
					ADVERTISED_10baseT_Full |
					ADVERTISED_TP;
		ecmd->speed = SPEED_10;
		ecmd->port = PORT_TP;
	}

	return 0;
}