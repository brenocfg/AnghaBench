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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct bcm_enet_stats {int stat_offset; int sizeof_stat; } ;
struct bcm_enet_priv {int /*<<< orphan*/  mib_update_lock; } ;

/* Variables and functions */
 int BCM_ENET_STATS_LEN ; 
 struct bcm_enet_stats* bcm_enet_gstrings_stats ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  update_mib_counters (struct bcm_enet_priv*) ; 

__attribute__((used)) static void bcm_enet_get_ethtool_stats(struct net_device *netdev,
				       struct ethtool_stats *stats,
				       u64 *data)
{
	struct bcm_enet_priv *priv;
	int i;

	priv = netdev_priv(netdev);

	mutex_lock(&priv->mib_update_lock);
	update_mib_counters(priv);

	for (i = 0; i < BCM_ENET_STATS_LEN; i++) {
		const struct bcm_enet_stats *s;
		char *p;

		s = &bcm_enet_gstrings_stats[i];
		p = (char *)priv + s->stat_offset;
		data[i] = (s->sizeof_stat == sizeof(u64)) ?
			*(u64 *)p : *(u32 *)p;
	}
	mutex_unlock(&priv->mib_update_lock);
}