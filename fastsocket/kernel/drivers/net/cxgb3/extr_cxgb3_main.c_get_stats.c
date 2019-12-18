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
struct TYPE_2__ {int /*<<< orphan*/  fifo_errors; } ;
struct port_info {TYPE_1__ phy; int /*<<< orphan*/  mac; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct mac_stats {int /*<<< orphan*/  link_faults; int /*<<< orphan*/  num_resets; int /*<<< orphan*/  num_toggled; int /*<<< orphan*/  rx_cong_drops; int /*<<< orphan*/  rx_frames_1519_max; int /*<<< orphan*/  rx_frames_1024_1518; int /*<<< orphan*/  rx_frames_512_1023; int /*<<< orphan*/  rx_frames_256_511; int /*<<< orphan*/  rx_frames_128_255; int /*<<< orphan*/  rx_frames_65_127; int /*<<< orphan*/  rx_frames_64; int /*<<< orphan*/  rx_fifo_ovfl; int /*<<< orphan*/  rx_too_long; int /*<<< orphan*/  rx_jabber; int /*<<< orphan*/  rx_short; int /*<<< orphan*/  rx_symbol_errs; int /*<<< orphan*/  rx_fcs_errs; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  rx_bcast_frames; int /*<<< orphan*/  rx_mcast_frames; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  rx_octets; int /*<<< orphan*/  tx_frames_1519_max; int /*<<< orphan*/  tx_frames_1024_1518; int /*<<< orphan*/  tx_frames_512_1023; int /*<<< orphan*/  tx_frames_256_511; int /*<<< orphan*/  tx_frames_128_255; int /*<<< orphan*/  tx_frames_65_127; int /*<<< orphan*/  tx_frames_64; int /*<<< orphan*/  tx_fifo_urun; int /*<<< orphan*/  tx_underrun; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  tx_bcast_frames; int /*<<< orphan*/  tx_mcast_frames; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  tx_octets; } ;
struct ethtool_stats {int dummy; } ;
struct adapter {int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGE_PSTAT_RX_CSUM_GOOD ; 
 int /*<<< orphan*/  SGE_PSTAT_TSO ; 
 int /*<<< orphan*/  SGE_PSTAT_TX_CSUM ; 
 int /*<<< orphan*/  SGE_PSTAT_VLANEX ; 
 int /*<<< orphan*/  SGE_PSTAT_VLANINS ; 
 void* collect_sge_port_stats (struct adapter*,struct port_info*,int /*<<< orphan*/ ) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct mac_stats* t3_mac_update_stats (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_stats(struct net_device *dev, struct ethtool_stats *stats,
		      u64 *data)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;
	const struct mac_stats *s;

	spin_lock(&adapter->stats_lock);
	s = t3_mac_update_stats(&pi->mac);
	spin_unlock(&adapter->stats_lock);

	*data++ = s->tx_octets;
	*data++ = s->tx_frames;
	*data++ = s->tx_mcast_frames;
	*data++ = s->tx_bcast_frames;
	*data++ = s->tx_pause;
	*data++ = s->tx_underrun;
	*data++ = s->tx_fifo_urun;

	*data++ = s->tx_frames_64;
	*data++ = s->tx_frames_65_127;
	*data++ = s->tx_frames_128_255;
	*data++ = s->tx_frames_256_511;
	*data++ = s->tx_frames_512_1023;
	*data++ = s->tx_frames_1024_1518;
	*data++ = s->tx_frames_1519_max;

	*data++ = s->rx_octets;
	*data++ = s->rx_frames;
	*data++ = s->rx_mcast_frames;
	*data++ = s->rx_bcast_frames;
	*data++ = s->rx_pause;
	*data++ = s->rx_fcs_errs;
	*data++ = s->rx_symbol_errs;
	*data++ = s->rx_short;
	*data++ = s->rx_jabber;
	*data++ = s->rx_too_long;
	*data++ = s->rx_fifo_ovfl;

	*data++ = s->rx_frames_64;
	*data++ = s->rx_frames_65_127;
	*data++ = s->rx_frames_128_255;
	*data++ = s->rx_frames_256_511;
	*data++ = s->rx_frames_512_1023;
	*data++ = s->rx_frames_1024_1518;
	*data++ = s->rx_frames_1519_max;

	*data++ = pi->phy.fifo_errors;

	*data++ = collect_sge_port_stats(adapter, pi, SGE_PSTAT_TSO);
	*data++ = collect_sge_port_stats(adapter, pi, SGE_PSTAT_VLANEX);
	*data++ = collect_sge_port_stats(adapter, pi, SGE_PSTAT_VLANINS);
	*data++ = collect_sge_port_stats(adapter, pi, SGE_PSTAT_TX_CSUM);
	*data++ = collect_sge_port_stats(adapter, pi, SGE_PSTAT_RX_CSUM_GOOD);
	*data++ = 0;
	*data++ = 0;
	*data++ = 0;
	*data++ = s->rx_cong_drops;

	*data++ = s->num_toggled;
	*data++ = s->num_resets;

	*data++ = s->link_faults;
}