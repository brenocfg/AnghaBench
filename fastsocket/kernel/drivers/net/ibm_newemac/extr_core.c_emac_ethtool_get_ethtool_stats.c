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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct emac_instance {int /*<<< orphan*/  estats; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct emac_instance* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void emac_ethtool_get_ethtool_stats(struct net_device *ndev,
					   struct ethtool_stats *estats,
					   u64 * tmp_stats)
{
	struct emac_instance *dev = netdev_priv(ndev);

	memcpy(tmp_stats, &dev->stats, sizeof(dev->stats));
	tmp_stats += sizeof(dev->stats) / sizeof(u64);
	memcpy(tmp_stats, &dev->estats, sizeof(dev->estats));
}