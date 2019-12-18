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
struct link_config {int requested_fc; int supported; scalar_t__ autoneg; int fc; } ;
struct port_info {int /*<<< orphan*/  mac; int /*<<< orphan*/  phy; struct link_config link_config; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int EINVAL ; 
 int PAUSE_AUTONEG ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int SUPPORTED_Autoneg ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  t3_link_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct link_config*) ; 
 int /*<<< orphan*/  t3_mac_set_speed_duplex_fc (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static int set_pauseparam(struct net_device *dev,
			  struct ethtool_pauseparam *epause)
{
	struct port_info *p = netdev_priv(dev);
	struct link_config *lc = &p->link_config;

	if (epause->autoneg == AUTONEG_DISABLE)
		lc->requested_fc = 0;
	else if (lc->supported & SUPPORTED_Autoneg)
		lc->requested_fc = PAUSE_AUTONEG;
	else
		return -EINVAL;

	if (epause->rx_pause)
		lc->requested_fc |= PAUSE_RX;
	if (epause->tx_pause)
		lc->requested_fc |= PAUSE_TX;
	if (lc->autoneg == AUTONEG_ENABLE) {
		if (netif_running(dev))
			t3_link_start(&p->phy, &p->mac, lc);
	} else {
		lc->fc = lc->requested_fc & (PAUSE_RX | PAUSE_TX);
		if (netif_running(dev))
			t3_mac_set_speed_duplex_fc(&p->mac, -1, -1, lc->fc);
	}
	return 0;
}