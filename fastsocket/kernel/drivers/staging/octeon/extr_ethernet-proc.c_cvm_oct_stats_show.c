#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_4__ {int rx_packets; int rx_bytes; int rx_errors; int rx_dropped; int rx_length_errors; int rx_over_errors; int rx_crc_errors; int rx_frame_errors; int rx_fifo_errors; int rx_missed_errors; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_heartbeat_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct octeon_ethernet {scalar_t__ imode; TYPE_1__ stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_GMII ; 
 int TOTAL_NUMBER_OF_PORTS ; 
 TYPE_2__** cvm_oct_device ; 
 int /*<<< orphan*/  cvm_oct_stats_switch_show (struct seq_file*,void*) ; 
 struct octeon_ethernet* netdev_priv (TYPE_2__*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cvm_oct_stats_show(struct seq_file *m, void *v)
{
	struct octeon_ethernet *priv;
	int port;

	for (port = 0; port < TOTAL_NUMBER_OF_PORTS; port++) {

		if (cvm_oct_device[port]) {
			priv = netdev_priv(cvm_oct_device[port]);

			seq_printf(m, "\nOcteon Port %d (%s)\n", port,
				   cvm_oct_device[port]->name);
			seq_printf(m,
				   "rx_packets:             %12lu\t"
				   "tx_packets:             %12lu\n",
				   priv->stats.rx_packets,
				   priv->stats.tx_packets);
			seq_printf(m,
				   "rx_bytes:               %12lu\t"
				   "tx_bytes:               %12lu\n",
				   priv->stats.rx_bytes, priv->stats.tx_bytes);
			seq_printf(m,
				   "rx_errors:              %12lu\t"
				   "tx_errors:              %12lu\n",
				   priv->stats.rx_errors,
				   priv->stats.tx_errors);
			seq_printf(m,
				   "rx_dropped:             %12lu\t"
				   "tx_dropped:             %12lu\n",
				   priv->stats.rx_dropped,
				   priv->stats.tx_dropped);
			seq_printf(m,
				   "rx_length_errors:       %12lu\t"
				   "tx_aborted_errors:      %12lu\n",
				   priv->stats.rx_length_errors,
				   priv->stats.tx_aborted_errors);
			seq_printf(m,
				   "rx_over_errors:         %12lu\t"
				   "tx_carrier_errors:      %12lu\n",
				   priv->stats.rx_over_errors,
				   priv->stats.tx_carrier_errors);
			seq_printf(m,
				   "rx_crc_errors:          %12lu\t"
				   "tx_fifo_errors:         %12lu\n",
				   priv->stats.rx_crc_errors,
				   priv->stats.tx_fifo_errors);
			seq_printf(m,
				   "rx_frame_errors:        %12lu\t"
				   "tx_heartbeat_errors:    %12lu\n",
				   priv->stats.rx_frame_errors,
				   priv->stats.tx_heartbeat_errors);
			seq_printf(m,
				   "rx_fifo_errors:         %12lu\t"
				   "tx_window_errors:       %12lu\n",
				   priv->stats.rx_fifo_errors,
				   priv->stats.tx_window_errors);
			seq_printf(m,
				   "rx_missed_errors:       %12lu\t"
				   "multicast:              %12lu\n",
				   priv->stats.rx_missed_errors,
				   priv->stats.multicast);
		}
	}

	if (cvm_oct_device[0]) {
		priv = netdev_priv(cvm_oct_device[0]);
		if (priv->imode == CVMX_HELPER_INTERFACE_MODE_GMII)
			cvm_oct_stats_switch_show(m, v);
	}
	return 0;
}