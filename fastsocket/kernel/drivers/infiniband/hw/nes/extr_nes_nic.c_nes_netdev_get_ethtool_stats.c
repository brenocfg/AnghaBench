#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int aggregated; int flushed; int no_desc; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;
struct TYPE_4__ {int rx_length_errors; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  tx_dropped; } ;
struct nes_vnic {int linearized_skbs; int tso_requests; int* qp_nic_index; int endnode_nstat_rx_discard; int endnode_nstat_rx_octets; int endnode_nstat_rx_frames; int endnode_nstat_tx_octets; int endnode_nstat_tx_frames; int endnode_ipv4_tcp_retransmits; int tx_sw_dropped; int sq_full; int segmented_tso_requests; TYPE_3__ lro_mgr; struct nes_device* nesdev; TYPE_1__ netstats; } ;
struct nes_device {int link_status_interrupts; int mac_index; int mac_pause_frames_sent; int mac_pause_frames_received; int port_rx_discards; int mac_rx_short_frames; int mac_rx_oversized_frames; int mac_rx_jabber_frames; int mac_rx_symbol_err_frames; int mac_rx_crc_errors; int mac_tx_errors; struct nes_adapter* nesadapter; int /*<<< orphan*/  mac_rx_errors; int /*<<< orphan*/  port_tx_discards; } ;
struct nes_adapter {int nic_rx_eth_route_err; int free_4kpbl; int free_256pbl; } ;
struct ethtool_stats {int /*<<< orphan*/  n_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_ETHTOOL_STAT_COUNT ; 
 scalar_t__ NES_IDX_ENDNODE0_NSTAT_RX_DISCARD ; 
 scalar_t__ NES_IDX_ENDNODE0_NSTAT_RX_FRAMES_HI ; 
 scalar_t__ NES_IDX_ENDNODE0_NSTAT_RX_FRAMES_LO ; 
 scalar_t__ NES_IDX_ENDNODE0_NSTAT_RX_OCTETS_HI ; 
 scalar_t__ NES_IDX_ENDNODE0_NSTAT_RX_OCTETS_LO ; 
 scalar_t__ NES_IDX_ENDNODE0_NSTAT_TX_FRAMES_HI ; 
 scalar_t__ NES_IDX_ENDNODE0_NSTAT_TX_FRAMES_LO ; 
 scalar_t__ NES_IDX_ENDNODE0_NSTAT_TX_OCTETS_HI ; 
 scalar_t__ NES_IDX_ENDNODE0_NSTAT_TX_OCTETS_LO ; 
 scalar_t__ NES_IDX_IPV4_TCP_REXMITS ; 
 scalar_t__ NES_IDX_MAC_RX_CRC_ERR_FRAMES ; 
 scalar_t__ NES_IDX_MAC_RX_JABBER_FRAMES ; 
 scalar_t__ NES_IDX_MAC_RX_LENGTH_ERR_FRAMES ; 
 scalar_t__ NES_IDX_MAC_RX_OVERSIZED_FRAMES ; 
 scalar_t__ NES_IDX_MAC_RX_PAUSE_FRAMES ; 
 scalar_t__ NES_IDX_MAC_RX_SHORT_FRAMES ; 
 scalar_t__ NES_IDX_MAC_RX_SYMBOL_ERR_FRAMES ; 
 scalar_t__ NES_IDX_MAC_TX_ERRORS ; 
 scalar_t__ NES_IDX_MAC_TX_PAUSE_FRAMES ; 
 scalar_t__ NES_IDX_PORT_RX_DISCARDS ; 
 scalar_t__ NES_IDX_PORT_TX_DISCARDS ; 
 size_t NES_MAX_PORT_COUNT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cm_accel_dropped_pkts ; 
 int /*<<< orphan*/  cm_accepts ; 
 int cm_backlog_drops ; 
 int /*<<< orphan*/  cm_closes ; 
 int /*<<< orphan*/  cm_connect_reqs ; 
 int /*<<< orphan*/  cm_connecteds ; 
 int /*<<< orphan*/  cm_connects ; 
 int /*<<< orphan*/  cm_disconnects ; 
 int /*<<< orphan*/  cm_listens_created ; 
 int /*<<< orphan*/  cm_listens_destroyed ; 
 int /*<<< orphan*/  cm_loopbacks ; 
 int /*<<< orphan*/  cm_nodes_created ; 
 int /*<<< orphan*/  cm_nodes_destroyed ; 
 int cm_packets_bounced ; 
 int cm_packets_created ; 
 int cm_packets_dropped ; 
 int cm_packets_received ; 
 int cm_packets_retrans ; 
 int cm_packets_sent ; 
 int /*<<< orphan*/  cm_rejects ; 
 int /*<<< orphan*/  cm_resets_recvd ; 
 int int_mod_timer_init ; 
 int mh_detected ; 
 int mh_pauses_sent ; 
 int /*<<< orphan*/  mod_qp_timouts ; 
 size_t nes_read_indexed (struct nes_device*,scalar_t__) ; 
 struct nes_vnic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pau_qps_created ; 
 int /*<<< orphan*/  pau_qps_destroyed ; 
 int /*<<< orphan*/  qps_created ; 
 int /*<<< orphan*/  qps_destroyed ; 
 int /*<<< orphan*/  sw_qps_destroyed ; 

__attribute__((used)) static void nes_netdev_get_ethtool_stats(struct net_device *netdev,
		struct ethtool_stats *target_ethtool_stats, u64 *target_stat_values)
{
	u64 u64temp;
	struct nes_vnic *nesvnic = netdev_priv(netdev);
	struct nes_device *nesdev = nesvnic->nesdev;
	struct nes_adapter *nesadapter = nesdev->nesadapter;
	u32 nic_count;
	u32 u32temp;
	u32 index = 0;

	target_ethtool_stats->n_stats = NES_ETHTOOL_STAT_COUNT;
	target_stat_values[index] = nesvnic->nesdev->link_status_interrupts;
	target_stat_values[++index] = nesvnic->linearized_skbs;
	target_stat_values[++index] = nesvnic->tso_requests;

	u32temp = nes_read_indexed(nesdev,
			NES_IDX_MAC_TX_PAUSE_FRAMES + (nesvnic->nesdev->mac_index*0x200));
	nesvnic->nesdev->mac_pause_frames_sent += u32temp;
	target_stat_values[++index] = nesvnic->nesdev->mac_pause_frames_sent;

	u32temp = nes_read_indexed(nesdev,
			NES_IDX_MAC_RX_PAUSE_FRAMES + (nesvnic->nesdev->mac_index*0x200));
	nesvnic->nesdev->mac_pause_frames_received += u32temp;

	u32temp = nes_read_indexed(nesdev,
			NES_IDX_PORT_RX_DISCARDS + (nesvnic->nesdev->mac_index*0x40));
	nesvnic->nesdev->port_rx_discards += u32temp;
	nesvnic->netstats.rx_dropped += u32temp;

	u32temp = nes_read_indexed(nesdev,
			NES_IDX_PORT_TX_DISCARDS + (nesvnic->nesdev->mac_index*0x40));
	nesvnic->nesdev->port_tx_discards += u32temp;
	nesvnic->netstats.tx_dropped += u32temp;

	u32temp = nes_read_indexed(nesdev,
			NES_IDX_MAC_RX_SHORT_FRAMES + (nesvnic->nesdev->mac_index*0x200));
	nesvnic->netstats.rx_dropped += u32temp;
	nesvnic->nesdev->mac_rx_errors += u32temp;
	nesvnic->nesdev->mac_rx_short_frames += u32temp;

	u32temp = nes_read_indexed(nesdev,
			NES_IDX_MAC_RX_OVERSIZED_FRAMES + (nesvnic->nesdev->mac_index*0x200));
	nesvnic->netstats.rx_dropped += u32temp;
	nesvnic->nesdev->mac_rx_errors += u32temp;
	nesvnic->nesdev->mac_rx_oversized_frames += u32temp;

	u32temp = nes_read_indexed(nesdev,
			NES_IDX_MAC_RX_JABBER_FRAMES + (nesvnic->nesdev->mac_index*0x200));
	nesvnic->netstats.rx_dropped += u32temp;
	nesvnic->nesdev->mac_rx_errors += u32temp;
	nesvnic->nesdev->mac_rx_jabber_frames += u32temp;

	u32temp = nes_read_indexed(nesdev,
			NES_IDX_MAC_RX_SYMBOL_ERR_FRAMES + (nesvnic->nesdev->mac_index*0x200));
	nesvnic->netstats.rx_dropped += u32temp;
	nesvnic->nesdev->mac_rx_errors += u32temp;
	nesvnic->nesdev->mac_rx_symbol_err_frames += u32temp;

	u32temp = nes_read_indexed(nesdev,
			NES_IDX_MAC_RX_LENGTH_ERR_FRAMES + (nesvnic->nesdev->mac_index*0x200));
	nesvnic->netstats.rx_length_errors += u32temp;
	nesvnic->nesdev->mac_rx_errors += u32temp;

	u32temp = nes_read_indexed(nesdev,
			NES_IDX_MAC_RX_CRC_ERR_FRAMES + (nesvnic->nesdev->mac_index*0x200));
	nesvnic->nesdev->mac_rx_errors += u32temp;
	nesvnic->nesdev->mac_rx_crc_errors += u32temp;
	nesvnic->netstats.rx_crc_errors += u32temp;

	u32temp = nes_read_indexed(nesdev,
			NES_IDX_MAC_TX_ERRORS + (nesvnic->nesdev->mac_index*0x200));
	nesvnic->nesdev->mac_tx_errors += u32temp;
	nesvnic->netstats.tx_errors += u32temp;

	for (nic_count = 0; nic_count < NES_MAX_PORT_COUNT; nic_count++) {
		if (nesvnic->qp_nic_index[nic_count] == 0xf)
			break;

		u32temp = nes_read_indexed(nesdev,
				NES_IDX_ENDNODE0_NSTAT_RX_DISCARD +
				(nesvnic->qp_nic_index[nic_count]*0x200));
		nesvnic->netstats.rx_dropped += u32temp;
		nesvnic->endnode_nstat_rx_discard += u32temp;

		u64temp = (u64)nes_read_indexed(nesdev,
				NES_IDX_ENDNODE0_NSTAT_RX_OCTETS_LO +
				(nesvnic->qp_nic_index[nic_count]*0x200));
		u64temp += ((u64)nes_read_indexed(nesdev,
				NES_IDX_ENDNODE0_NSTAT_RX_OCTETS_HI +
				(nesvnic->qp_nic_index[nic_count]*0x200))) << 32;

		nesvnic->endnode_nstat_rx_octets += u64temp;
		nesvnic->netstats.rx_bytes += u64temp;

		u64temp = (u64)nes_read_indexed(nesdev,
				NES_IDX_ENDNODE0_NSTAT_RX_FRAMES_LO +
				(nesvnic->qp_nic_index[nic_count]*0x200));
		u64temp += ((u64)nes_read_indexed(nesdev,
				NES_IDX_ENDNODE0_NSTAT_RX_FRAMES_HI +
				(nesvnic->qp_nic_index[nic_count]*0x200))) << 32;

		nesvnic->endnode_nstat_rx_frames += u64temp;
		nesvnic->netstats.rx_packets += u64temp;

		u64temp = (u64)nes_read_indexed(nesdev,
				NES_IDX_ENDNODE0_NSTAT_TX_OCTETS_LO +
				(nesvnic->qp_nic_index[nic_count]*0x200));
		u64temp += ((u64)nes_read_indexed(nesdev,
				NES_IDX_ENDNODE0_NSTAT_TX_OCTETS_HI +
				(nesvnic->qp_nic_index[nic_count]*0x200))) << 32;

		nesvnic->endnode_nstat_tx_octets += u64temp;
		nesvnic->netstats.tx_bytes += u64temp;

		u64temp = (u64)nes_read_indexed(nesdev,
				NES_IDX_ENDNODE0_NSTAT_TX_FRAMES_LO +
				(nesvnic->qp_nic_index[nic_count]*0x200));
		u64temp += ((u64)nes_read_indexed(nesdev,
				NES_IDX_ENDNODE0_NSTAT_TX_FRAMES_HI +
				(nesvnic->qp_nic_index[nic_count]*0x200))) << 32;

		nesvnic->endnode_nstat_tx_frames += u64temp;
		nesvnic->netstats.tx_packets += u64temp;

		u32temp = nes_read_indexed(nesdev,
				NES_IDX_IPV4_TCP_REXMITS + (nesvnic->qp_nic_index[nic_count]*0x200));
		nesvnic->endnode_ipv4_tcp_retransmits += u32temp;
	}

	target_stat_values[++index] = nesvnic->nesdev->mac_pause_frames_received;
	target_stat_values[++index] = nesdev->nesadapter->nic_rx_eth_route_err;
	target_stat_values[++index] = nesvnic->tx_sw_dropped;
	target_stat_values[++index] = nesvnic->sq_full;
	target_stat_values[++index] = nesvnic->segmented_tso_requests;
	target_stat_values[++index] = nesvnic->nesdev->mac_rx_symbol_err_frames;
	target_stat_values[++index] = nesvnic->nesdev->mac_rx_jabber_frames;
	target_stat_values[++index] = nesvnic->nesdev->mac_rx_oversized_frames;
	target_stat_values[++index] = nesvnic->nesdev->mac_rx_short_frames;
	target_stat_values[++index] = nesvnic->netstats.rx_length_errors;
	target_stat_values[++index] = nesvnic->nesdev->mac_rx_crc_errors;
	target_stat_values[++index] = nesvnic->nesdev->port_rx_discards;
	target_stat_values[++index] = nesvnic->endnode_nstat_rx_discard;
	target_stat_values[++index] = nesvnic->endnode_nstat_rx_octets;
	target_stat_values[++index] = nesvnic->endnode_nstat_rx_frames;
	target_stat_values[++index] = nesvnic->endnode_nstat_tx_octets;
	target_stat_values[++index] = nesvnic->endnode_nstat_tx_frames;
	target_stat_values[++index] = nesvnic->nesdev->mac_tx_errors;
	target_stat_values[++index] = mh_detected;
	target_stat_values[++index] = mh_pauses_sent;
	target_stat_values[++index] = nesvnic->endnode_ipv4_tcp_retransmits;
	target_stat_values[++index] = atomic_read(&cm_connects);
	target_stat_values[++index] = atomic_read(&cm_accepts);
	target_stat_values[++index] = atomic_read(&cm_disconnects);
	target_stat_values[++index] = atomic_read(&cm_connecteds);
	target_stat_values[++index] = atomic_read(&cm_connect_reqs);
	target_stat_values[++index] = atomic_read(&cm_rejects);
	target_stat_values[++index] = atomic_read(&mod_qp_timouts);
	target_stat_values[++index] = atomic_read(&qps_created);
	target_stat_values[++index] = atomic_read(&sw_qps_destroyed);
	target_stat_values[++index] = atomic_read(&qps_destroyed);
	target_stat_values[++index] = atomic_read(&cm_closes);
	target_stat_values[++index] = cm_packets_sent;
	target_stat_values[++index] = cm_packets_bounced;
	target_stat_values[++index] = cm_packets_created;
	target_stat_values[++index] = cm_packets_received;
	target_stat_values[++index] = cm_packets_dropped;
	target_stat_values[++index] = cm_packets_retrans;
	target_stat_values[++index] = atomic_read(&cm_listens_created);
	target_stat_values[++index] = atomic_read(&cm_listens_destroyed);
	target_stat_values[++index] = cm_backlog_drops;
	target_stat_values[++index] = atomic_read(&cm_loopbacks);
	target_stat_values[++index] = atomic_read(&cm_nodes_created);
	target_stat_values[++index] = atomic_read(&cm_nodes_destroyed);
	target_stat_values[++index] = atomic_read(&cm_accel_dropped_pkts);
	target_stat_values[++index] = atomic_read(&cm_resets_recvd);
	target_stat_values[++index] = nesadapter->free_4kpbl;
	target_stat_values[++index] = nesadapter->free_256pbl;
	target_stat_values[++index] = int_mod_timer_init;
	target_stat_values[++index] = nesvnic->lro_mgr.stats.aggregated;
	target_stat_values[++index] = nesvnic->lro_mgr.stats.flushed;
	target_stat_values[++index] = nesvnic->lro_mgr.stats.no_desc;
	target_stat_values[++index] = atomic_read(&pau_qps_created);
	target_stat_values[++index] = atomic_read(&pau_qps_destroyed);
}