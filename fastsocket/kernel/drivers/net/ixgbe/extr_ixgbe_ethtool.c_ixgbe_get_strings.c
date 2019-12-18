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
typedef  char u8 ;
typedef  int u32 ;
struct net_device {int num_tx_queues; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int IXGBE_GLOBAL_STATS_LEN ; 
 int IXGBE_MAX_PACKET_BUFFERS ; 
 int IXGBE_NUM_RX_QUEUES ; 
 int IXGBE_TEST_LEN ; 
 TYPE_1__* ixgbe_gstrings_stats ; 
 int /*<<< orphan*/ * ixgbe_gstrings_test ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void ixgbe_get_strings(struct net_device *netdev, u32 stringset,
                              u8 *data)
{
	char *p = (char *)data;
	int i;

	switch (stringset) {
	case ETH_SS_TEST:
		for (i = 0; i < IXGBE_TEST_LEN; i++) {
			memcpy(data, ixgbe_gstrings_test[i], ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		}
		break;
	case ETH_SS_STATS:
		for (i = 0; i < IXGBE_GLOBAL_STATS_LEN; i++) {
			memcpy(p, ixgbe_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}
		for (i = 0; i < netdev->num_tx_queues; i++) {
			sprintf(p, "tx_queue_%u_packets", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "tx_queue_%u_bytes", i);
			p += ETH_GSTRING_LEN;
		}
		for (i = 0; i < IXGBE_NUM_RX_QUEUES; i++) {
			sprintf(p, "rx_queue_%u_packets", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "rx_queue_%u_bytes", i);
			p += ETH_GSTRING_LEN;
		}
		for (i = 0; i < IXGBE_MAX_PACKET_BUFFERS; i++) {
			sprintf(p, "tx_pb_%u_pxon", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "tx_pb_%u_pxoff", i);
			p += ETH_GSTRING_LEN;
		}
		for (i = 0; i < IXGBE_MAX_PACKET_BUFFERS; i++) {
			sprintf(p, "rx_pb_%u_pxon", i);
			p += ETH_GSTRING_LEN;
			sprintf(p, "rx_pb_%u_pxoff", i);
			p += ETH_GSTRING_LEN;
		}
		/* BUG_ON(p - data != IXGBE_STATS_LEN * ETH_GSTRING_LEN); */
		break;
	}
}