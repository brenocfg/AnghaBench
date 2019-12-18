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
struct ethtool_coalesce {int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  tx_coalesce_usecs; } ;
struct enic {int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  tx_coalesce_usecs; } ;

/* Variables and functions */
 struct enic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enic_get_coalesce(struct net_device *netdev,
	struct ethtool_coalesce *ecmd)
{
	struct enic *enic = netdev_priv(netdev);

	ecmd->tx_coalesce_usecs = enic->tx_coalesce_usecs;
	ecmd->rx_coalesce_usecs = enic->rx_coalesce_usecs;

	return 0;
}