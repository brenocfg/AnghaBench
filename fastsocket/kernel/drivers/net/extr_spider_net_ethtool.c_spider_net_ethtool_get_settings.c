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
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct spider_net_card {TYPE_1__ phy; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int supported; int advertising; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_FIBRE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_FIBRE ; 
 struct spider_net_card* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
spider_net_ethtool_get_settings(struct net_device *netdev,
			       struct ethtool_cmd *cmd)
{
	struct spider_net_card *card;
	card = netdev_priv(netdev);

	cmd->supported   = (SUPPORTED_1000baseT_Full |
			     SUPPORTED_FIBRE);
	cmd->advertising = (ADVERTISED_1000baseT_Full |
			     ADVERTISED_FIBRE);
	cmd->port = PORT_FIBRE;
	cmd->speed = card->phy.speed;
	cmd->duplex = DUPLEX_FULL;

	return 0;
}