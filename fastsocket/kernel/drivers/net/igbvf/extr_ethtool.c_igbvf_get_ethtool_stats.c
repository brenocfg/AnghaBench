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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct igbvf_adapter {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_2__ {int stat_offset; int base_stat_offset; int sizeof_stat; } ;

/* Variables and functions */
 int IGBVF_GLOBAL_STATS_LEN ; 
 TYPE_1__* igbvf_gstrings_stats ; 
 int /*<<< orphan*/  igbvf_update_stats (struct igbvf_adapter*) ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void igbvf_get_ethtool_stats(struct net_device *netdev,
                                    struct ethtool_stats *stats,
                                    u64 *data)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);
	int i;

	igbvf_update_stats(adapter);
	for (i = 0; i < IGBVF_GLOBAL_STATS_LEN; i++) {
		char *p = (char *)adapter +
		          igbvf_gstrings_stats[i].stat_offset;
		char *b = (char *)adapter +
		          igbvf_gstrings_stats[i].base_stat_offset;
		data[i] = ((igbvf_gstrings_stats[i].sizeof_stat ==
		            sizeof(u64)) ? (*(u64 *)p - *(u64 *)b) :
		            (*(u32 *)p - *(u32 *)b));
	}

}