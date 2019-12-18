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
struct net_device {int dummy; } ;
struct ethtool_coalesce {int /*<<< orphan*/  use_adaptive_tx_coalesce; int /*<<< orphan*/  use_adaptive_rx_coalesce; int /*<<< orphan*/  tx_coalesce_usecs_low; int /*<<< orphan*/  tx_coalesce_usecs_high; int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  rx_coalesce_usecs_low; int /*<<< orphan*/  rx_coalesce_usecs_high; int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct be_eq_obj {int /*<<< orphan*/  enable_aic; int /*<<< orphan*/  min_eqd; int /*<<< orphan*/  max_eqd; int /*<<< orphan*/  cur_eqd; } ;
struct be_adapter {struct be_eq_obj* eq_obj; } ;

/* Variables and functions */
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int be_get_coalesce(struct net_device *netdev,
			   struct ethtool_coalesce *et)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	struct be_eq_obj *eqo = &adapter->eq_obj[0];


	et->rx_coalesce_usecs = eqo->cur_eqd;
	et->rx_coalesce_usecs_high = eqo->max_eqd;
	et->rx_coalesce_usecs_low = eqo->min_eqd;

	et->tx_coalesce_usecs = eqo->cur_eqd;
	et->tx_coalesce_usecs_high = eqo->max_eqd;
	et->tx_coalesce_usecs_low = eqo->min_eqd;

	et->use_adaptive_rx_coalesce = eqo->enable_aic;
	et->use_adaptive_tx_coalesce = eqo->enable_aic;

	return 0;
}