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
struct param_range {int /*<<< orphan*/  count; int /*<<< orphan*/  max; } ;
struct TYPE_2__ {struct param_range cbs; struct param_range rfds; } ;
struct nic {TYPE_1__ params; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 struct nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void e100_get_ringparam(struct net_device *netdev,
	struct ethtool_ringparam *ring)
{
	struct nic *nic = netdev_priv(netdev);
	struct param_range *rfds = &nic->params.rfds;
	struct param_range *cbs = &nic->params.cbs;

	ring->rx_max_pending = rfds->max;
	ring->tx_max_pending = cbs->max;
	ring->rx_pending = rfds->count;
	ring->tx_pending = cbs->count;
}