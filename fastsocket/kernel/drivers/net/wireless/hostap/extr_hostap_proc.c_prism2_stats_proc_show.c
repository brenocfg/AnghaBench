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
struct seq_file {TYPE_1__* private; } ;
struct comm_tallies_sums {int /*<<< orphan*/  rx_message_in_bad_msg_fragments; int /*<<< orphan*/  rx_message_in_msg_fragments; int /*<<< orphan*/  rx_discards_wep_undecryptable; int /*<<< orphan*/  tx_discards_wrong_sa; int /*<<< orphan*/  rx_discards_no_buffer; int /*<<< orphan*/  rx_fcs_errors; int /*<<< orphan*/  rx_multicast_octets; int /*<<< orphan*/  rx_unicast_octets; int /*<<< orphan*/  rx_fragments; int /*<<< orphan*/  rx_multicast_frames; int /*<<< orphan*/  rx_unicast_frames; int /*<<< orphan*/  tx_discards; int /*<<< orphan*/  tx_retry_limit_exceeded; int /*<<< orphan*/  tx_multiple_retry_frames; int /*<<< orphan*/  tx_single_retry_frames; int /*<<< orphan*/  tx_deferred_transmissions; int /*<<< orphan*/  tx_multicast_octets; int /*<<< orphan*/  tx_unicast_octets; int /*<<< orphan*/  tx_fragments; int /*<<< orphan*/  tx_multicast_frames; int /*<<< orphan*/  tx_unicast_frames; } ;
struct TYPE_2__ {struct comm_tallies_sums comm_tallies; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prism2_stats_proc_show(struct seq_file *m, void *v)
{
	local_info_t *local = m->private;
	struct comm_tallies_sums *sums = &local->comm_tallies;

	seq_printf(m, "TxUnicastFrames=%u\n", sums->tx_unicast_frames);
	seq_printf(m, "TxMulticastframes=%u\n", sums->tx_multicast_frames);
	seq_printf(m, "TxFragments=%u\n", sums->tx_fragments);
	seq_printf(m, "TxUnicastOctets=%u\n", sums->tx_unicast_octets);
	seq_printf(m, "TxMulticastOctets=%u\n", sums->tx_multicast_octets);
	seq_printf(m, "TxDeferredTransmissions=%u\n",
		   sums->tx_deferred_transmissions);
	seq_printf(m, "TxSingleRetryFrames=%u\n", sums->tx_single_retry_frames);
	seq_printf(m, "TxMultipleRetryFrames=%u\n",
		   sums->tx_multiple_retry_frames);
	seq_printf(m, "TxRetryLimitExceeded=%u\n",
		   sums->tx_retry_limit_exceeded);
	seq_printf(m, "TxDiscards=%u\n", sums->tx_discards);
	seq_printf(m, "RxUnicastFrames=%u\n", sums->rx_unicast_frames);
	seq_printf(m, "RxMulticastFrames=%u\n", sums->rx_multicast_frames);
	seq_printf(m, "RxFragments=%u\n", sums->rx_fragments);
	seq_printf(m, "RxUnicastOctets=%u\n", sums->rx_unicast_octets);
	seq_printf(m, "RxMulticastOctets=%u\n", sums->rx_multicast_octets);
	seq_printf(m, "RxFCSErrors=%u\n", sums->rx_fcs_errors);
	seq_printf(m, "RxDiscardsNoBuffer=%u\n", sums->rx_discards_no_buffer);
	seq_printf(m, "TxDiscardsWrongSA=%u\n", sums->tx_discards_wrong_sa);
	seq_printf(m, "RxDiscardsWEPUndecryptable=%u\n",
		   sums->rx_discards_wep_undecryptable);
	seq_printf(m, "RxMessageInMsgFragments=%u\n",
		   sums->rx_message_in_msg_fragments);
	seq_printf(m, "RxMessageInBadMsgFragments=%u\n",
		   sums->rx_message_in_bad_msg_fragments);
	/* FIX: this may grow too long for one page(?) */

	return 0;
}