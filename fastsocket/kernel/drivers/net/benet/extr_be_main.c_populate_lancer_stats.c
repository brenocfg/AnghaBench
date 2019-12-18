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
struct lancer_pport_stats {int /*<<< orphan*/  rx_drops_too_many_frags_lo; int /*<<< orphan*/  rx_drops_mtu_lo; int /*<<< orphan*/  num_forwards_lo; int /*<<< orphan*/  rx_jabbers; int /*<<< orphan*/  tx_control_frames_lo; int /*<<< orphan*/  tx_pause_frames_lo; int /*<<< orphan*/  rx_fifo_overflow; int /*<<< orphan*/  rx_symbol_errors_lo; scalar_t__ rx_vlan_filtered; scalar_t__ rx_address_filtered; int /*<<< orphan*/  rx_dropped_header_too_small; int /*<<< orphan*/  rx_out_of_range_errors; int /*<<< orphan*/  rx_dropped_too_short; int /*<<< orphan*/  rx_dropped_too_small; int /*<<< orphan*/  rx_dropped_invalid_tcp_length; int /*<<< orphan*/  rx_udp_checksum_errors; int /*<<< orphan*/  rx_tcp_checksum_errors; int /*<<< orphan*/  rx_ip_checksum_errors; int /*<<< orphan*/  rx_dropped_runt; int /*<<< orphan*/  rx_frames_too_long_lo; int /*<<< orphan*/  rx_in_range_errors; int /*<<< orphan*/  rx_control_frames_lo; int /*<<< orphan*/  rx_crc_errors_lo; int /*<<< orphan*/  rx_pause_frames_lo; } ;
struct be_drv_stats {int /*<<< orphan*/  rx_drops_too_many_frags; int /*<<< orphan*/  rx_drops_mtu; int /*<<< orphan*/  forwarded_packets; int /*<<< orphan*/  jabber_events; int /*<<< orphan*/  tx_controlframes; int /*<<< orphan*/  tx_pauseframes; int /*<<< orphan*/  rxpp_fifo_overflow_drop; int /*<<< orphan*/  rx_alignment_symbol_errors; scalar_t__ rx_address_filtered; int /*<<< orphan*/  rx_input_fifo_overflow_drop; int /*<<< orphan*/  rx_dropped_header_too_small; int /*<<< orphan*/  rx_out_range_errors; int /*<<< orphan*/  rx_dropped_too_short; int /*<<< orphan*/  rx_dropped_too_small; int /*<<< orphan*/  rx_dropped_tcp_length; int /*<<< orphan*/  rx_udp_checksum_errs; int /*<<< orphan*/  rx_tcp_checksum_errs; int /*<<< orphan*/  rx_ip_checksum_errs; int /*<<< orphan*/  rx_dropped_runt; int /*<<< orphan*/  rx_frame_too_long; int /*<<< orphan*/  rx_in_range_errors; int /*<<< orphan*/  rx_control_frames; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_pause_frames; } ;
struct be_adapter {struct be_drv_stats drv_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_dws_le_to_cpu (struct lancer_pport_stats*,int) ; 
 struct lancer_pport_stats* pport_stats_from_cmd (struct be_adapter*) ; 

__attribute__((used)) static void populate_lancer_stats(struct be_adapter *adapter)
{

	struct be_drv_stats *drvs = &adapter->drv_stats;
	struct lancer_pport_stats *pport_stats =
					pport_stats_from_cmd(adapter);

	be_dws_le_to_cpu(pport_stats, sizeof(*pport_stats));
	drvs->rx_pause_frames = pport_stats->rx_pause_frames_lo;
	drvs->rx_crc_errors = pport_stats->rx_crc_errors_lo;
	drvs->rx_control_frames = pport_stats->rx_control_frames_lo;
	drvs->rx_in_range_errors = pport_stats->rx_in_range_errors;
	drvs->rx_frame_too_long = pport_stats->rx_frames_too_long_lo;
	drvs->rx_dropped_runt = pport_stats->rx_dropped_runt;
	drvs->rx_ip_checksum_errs = pport_stats->rx_ip_checksum_errors;
	drvs->rx_tcp_checksum_errs = pport_stats->rx_tcp_checksum_errors;
	drvs->rx_udp_checksum_errs = pport_stats->rx_udp_checksum_errors;
	drvs->rx_dropped_tcp_length =
				pport_stats->rx_dropped_invalid_tcp_length;
	drvs->rx_dropped_too_small = pport_stats->rx_dropped_too_small;
	drvs->rx_dropped_too_short = pport_stats->rx_dropped_too_short;
	drvs->rx_out_range_errors = pport_stats->rx_out_of_range_errors;
	drvs->rx_dropped_header_too_small =
				pport_stats->rx_dropped_header_too_small;
	drvs->rx_input_fifo_overflow_drop = pport_stats->rx_fifo_overflow;
	drvs->rx_address_filtered =
					pport_stats->rx_address_filtered +
					pport_stats->rx_vlan_filtered;
	drvs->rx_alignment_symbol_errors = pport_stats->rx_symbol_errors_lo;
	drvs->rxpp_fifo_overflow_drop = pport_stats->rx_fifo_overflow;
	drvs->tx_pauseframes = pport_stats->tx_pause_frames_lo;
	drvs->tx_controlframes = pport_stats->tx_control_frames_lo;
	drvs->jabber_events = pport_stats->rx_jabbers;
	drvs->forwarded_packets = pport_stats->num_forwards_lo;
	drvs->rx_drops_mtu = pport_stats->rx_drops_mtu_lo;
	drvs->rx_drops_too_many_frags =
				pport_stats->rx_drops_too_many_frags_lo;
}