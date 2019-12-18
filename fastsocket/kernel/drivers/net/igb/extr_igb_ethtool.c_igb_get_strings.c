#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct igb_adapter {int num_tx_queues; int num_rx_queues; } ;
struct TYPE_4__ {int /*<<< orphan*/  stat_string; } ;
struct TYPE_3__ {int /*<<< orphan*/  stat_string; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int IGB_GLOBAL_STATS_LEN ; 
 int IGB_NETDEV_STATS_LEN ; 
 int IGB_TEST_LEN ; 
 TYPE_2__* igb_gstrings_net_stats ; 
 TYPE_1__* igb_gstrings_stats ; 
 int /*<<< orphan*/ * igb_gstrings_test ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void igb_get_strings(struct net_device *netdev, u32 stringset, u8 *data)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	u8 *p = data;
	int i;

	switch (stringset) {
	case ETH_SS_TEST:
		memcpy(data, *igb_gstrings_test,
			IGB_TEST_LEN*ETH_GSTRING_LEN);
		break;
	case ETH_SS_STATS:
		for (i = 0; i < IGB_GLOBAL_STATS_LEN; i++) {
			memcpy(p, igb_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}
		for (i = 0; i < IGB_NETDEV_STATS_LEN; i++) {
			memcpy(p, igb_gstrings_net_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}
		for (i = 0; i < adapter->num_tx_queues; i++) {
			sprintf(p, "tx_queue_%u_packets", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "tx_queue_%u_bytes", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "tx_queue_%u_restart", i);
			p += ETH_GSTRING_LEN;
		}
		for (i = 0; i < adapter->num_rx_queues; i++) {
			sprintf(p, "rx_queue_%u_packets", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "rx_queue_%u_bytes", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "rx_queue_%u_drops", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "rx_queue_%u_csum_err", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "rx_queue_%u_alloc_failed", i);
			p += ETH_GSTRING_LEN;
		}
		/* BUG_ON(p - data != IGB_STATS_LEN * ETH_GSTRING_LEN); */
		break;
	}
}