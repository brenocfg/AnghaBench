#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_8__ {int initial_rx_packets; int bufs_rec; int initial_tx_packets; int bufs_sent; int skbs_sent_pack; int bufs_sent_pack; int sg_skbs_sent; int sg_frags_sent; int sg_skbs_rx; int sg_frags_rx; int sg_alloc_page_rx; int large_send_bytes; int large_send_cnt; int sc_dp_p; int sc_p_dp; int inbound_time; int inbound_cnt; int inbound_do_qdio_time; int inbound_do_qdio_cnt; int outbound_handler_time; int outbound_handler_cnt; int outbound_time; int outbound_cnt; int outbound_do_qdio_time; int outbound_do_qdio_cnt; int tx_csum; int tx_lin; int cq_cnt; int cq_time; } ;
struct TYPE_7__ {int no_out_queues; TYPE_2__** out_qs; } ;
struct TYPE_5__ {int rx_packets; int tx_packets; } ;
struct qeth_card {TYPE_4__ perf_stats; TYPE_3__ qdio; TYPE_1__ stats; } ;
struct net_device {struct qeth_card* ml_priv; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  used_buffers; } ;

/* Variables and functions */
 int QETH_HIGH_WATERMARK_PACK ; 
 int QETH_LOW_WATERMARK_PACK ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

void qeth_core_get_ethtool_stats(struct net_device *dev,
		struct ethtool_stats *stats, u64 *data)
{
	struct qeth_card *card = dev->ml_priv;
	data[0] = card->stats.rx_packets -
				card->perf_stats.initial_rx_packets;
	data[1] = card->perf_stats.bufs_rec;
	data[2] = card->stats.tx_packets -
				card->perf_stats.initial_tx_packets;
	data[3] = card->perf_stats.bufs_sent;
	data[4] = card->stats.tx_packets - card->perf_stats.initial_tx_packets
			- card->perf_stats.skbs_sent_pack;
	data[5] = card->perf_stats.bufs_sent - card->perf_stats.bufs_sent_pack;
	data[6] = card->perf_stats.skbs_sent_pack;
	data[7] = card->perf_stats.bufs_sent_pack;
	data[8] = card->perf_stats.sg_skbs_sent;
	data[9] = card->perf_stats.sg_frags_sent;
	data[10] = card->perf_stats.sg_skbs_rx;
	data[11] = card->perf_stats.sg_frags_rx;
	data[12] = card->perf_stats.sg_alloc_page_rx;
	data[13] = (card->perf_stats.large_send_bytes >> 10);
	data[14] = card->perf_stats.large_send_cnt;
	data[15] = card->perf_stats.sc_dp_p;
	data[16] = card->perf_stats.sc_p_dp;
	data[17] = QETH_LOW_WATERMARK_PACK;
	data[18] = QETH_HIGH_WATERMARK_PACK;
	data[19] = atomic_read(&card->qdio.out_qs[0]->used_buffers);
	data[20] = (card->qdio.no_out_queues > 1) ?
			atomic_read(&card->qdio.out_qs[1]->used_buffers) : 0;
	data[21] = (card->qdio.no_out_queues > 2) ?
			atomic_read(&card->qdio.out_qs[2]->used_buffers) : 0;
	data[22] = (card->qdio.no_out_queues > 3) ?
			atomic_read(&card->qdio.out_qs[3]->used_buffers) : 0;
	data[23] = card->perf_stats.inbound_time;
	data[24] = card->perf_stats.inbound_cnt;
	data[25] = card->perf_stats.inbound_do_qdio_time;
	data[26] = card->perf_stats.inbound_do_qdio_cnt;
	data[27] = card->perf_stats.outbound_handler_time;
	data[28] = card->perf_stats.outbound_handler_cnt;
	data[29] = card->perf_stats.outbound_time;
	data[30] = card->perf_stats.outbound_cnt;
	data[31] = card->perf_stats.outbound_do_qdio_time;
	data[32] = card->perf_stats.outbound_do_qdio_cnt;
	data[33] = card->perf_stats.tx_csum;
	data[34] = card->perf_stats.tx_lin;
	data[35] = card->perf_stats.cq_cnt;
	data[36] = card->perf_stats.cq_time;
}