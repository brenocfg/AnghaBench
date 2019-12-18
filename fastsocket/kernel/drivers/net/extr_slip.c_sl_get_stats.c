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
struct slip {struct slcompress* slcomp; int /*<<< orphan*/  tx_misses; int /*<<< orphan*/  tx_compressed; int /*<<< orphan*/  rx_compressed; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct slcompress {scalar_t__ sls_o_misses; scalar_t__ sls_o_compressed; scalar_t__ sls_i_tossed; scalar_t__ sls_i_compressed; } ;
struct net_device_stats {int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct net_device_stats*,int /*<<< orphan*/ ,int) ; 
 struct slip* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *
sl_get_stats(struct net_device *dev)
{
	static struct net_device_stats stats;
	struct slip *sl = netdev_priv(dev);
#ifdef SL_INCLUDE_CSLIP
	struct slcompress *comp;
#endif

	memset(&stats, 0, sizeof(struct net_device_stats));

	stats.rx_packets     = sl->rx_packets;
	stats.tx_packets     = sl->tx_packets;
	stats.rx_bytes	     = sl->rx_bytes;
	stats.tx_bytes	     = sl->tx_bytes;
	stats.rx_dropped     = sl->rx_dropped;
	stats.tx_dropped     = sl->tx_dropped;
	stats.tx_errors      = sl->tx_errors;
	stats.rx_errors      = sl->rx_errors;
	stats.rx_over_errors = sl->rx_over_errors;
#ifdef SL_INCLUDE_CSLIP
	stats.rx_fifo_errors = sl->rx_compressed;
	stats.tx_fifo_errors = sl->tx_compressed;
	stats.collisions     = sl->tx_misses;
	comp = sl->slcomp;
	if (comp) {
		stats.rx_fifo_errors += comp->sls_i_compressed;
		stats.rx_dropped     += comp->sls_i_tossed;
		stats.tx_fifo_errors += comp->sls_o_compressed;
		stats.collisions     += comp->sls_o_misses;
	}
#endif /* CONFIG_INET */
	return (&stats);
}