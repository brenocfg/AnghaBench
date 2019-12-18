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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  tx_underun; int /*<<< orphan*/  tx_aborted; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  rx_broadcast; int /*<<< orphan*/  rx_unicast; int /*<<< orphan*/  tx_multi_collision; int /*<<< orphan*/  tx_one_collision; int /*<<< orphan*/  align_errors; int /*<<< orphan*/  rx_missed; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_packets; } ;
struct rtl8169_private {TYPE_1__ counters; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8169_update_counters (struct net_device*) ; 

__attribute__((used)) static void rtl8169_get_ethtool_stats(struct net_device *dev,
				      struct ethtool_stats *stats, u64 *data)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	ASSERT_RTNL();

	rtl8169_update_counters(dev);

	data[0] = le64_to_cpu(tp->counters.tx_packets);
	data[1] = le64_to_cpu(tp->counters.rx_packets);
	data[2] = le64_to_cpu(tp->counters.tx_errors);
	data[3] = le32_to_cpu(tp->counters.rx_errors);
	data[4] = le16_to_cpu(tp->counters.rx_missed);
	data[5] = le16_to_cpu(tp->counters.align_errors);
	data[6] = le32_to_cpu(tp->counters.tx_one_collision);
	data[7] = le32_to_cpu(tp->counters.tx_multi_collision);
	data[8] = le64_to_cpu(tp->counters.rx_unicast);
	data[9] = le64_to_cpu(tp->counters.rx_broadcast);
	data[10] = le32_to_cpu(tp->counters.rx_multicast);
	data[11] = le16_to_cpu(tp->counters.tx_aborted);
	data[12] = le16_to_cpu(tp->counters.tx_underun);
}