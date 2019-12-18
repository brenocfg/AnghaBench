#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct TYPE_10__ {size_t read_ptr; scalar_t__ low_mark; int /*<<< orphan*/  n_bd; } ;
struct il_tx_queue {TYPE_5__ q; } ;
struct il_compressed_ba_resp {int sta_id; int tid; int /*<<< orphan*/  scd_ssn; int /*<<< orphan*/  scd_flow; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  seq_ctl; int /*<<< orphan*/  sta_addr_lo32; } ;
struct TYPE_6__ {struct il_compressed_ba_resp compressed_ba; } ;
struct il_rx_pkt {TYPE_1__ u; } ;
struct il_rx_buf {int dummy; } ;
struct TYPE_7__ {size_t max_txq_num; } ;
struct il_priv {int /*<<< orphan*/  sta_lock; scalar_t__ mac80211_registered; TYPE_4__* stations; struct il_tx_queue* txq; TYPE_2__ hw_params; } ;
struct il_ht_agg {size_t txq_id; size_t start_idx; scalar_t__ state; scalar_t__ bitmap; int /*<<< orphan*/  wait_for_ba; } ;
struct TYPE_9__ {TYPE_3__* tid; } ;
struct TYPE_8__ {struct il_ht_agg agg; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TX_REPLY (char*,size_t,unsigned long long,...) ; 
 scalar_t__ IL_EMPTYING_HW_QUEUE_DELBA ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int /*<<< orphan*/  il4965_free_tfds_in_queue (struct il_priv*,int,int,int) ; 
 int il4965_tx_queue_reclaim (struct il_priv*,size_t,int) ; 
 int /*<<< orphan*/  il4965_tx_status_reply_compressed_ba (struct il_priv*,struct il_ht_agg*,struct il_compressed_ba_resp*) ; 
 int /*<<< orphan*/  il4965_txq_check_empty (struct il_priv*,int,int,size_t) ; 
 int il_queue_dec_wrap (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ il_queue_space (TYPE_5__*) ; 
 int /*<<< orphan*/  il_wake_queue (struct il_priv*,struct il_tx_queue*) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
il4965_hdl_compressed_ba(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct il_compressed_ba_resp *ba_resp = &pkt->u.compressed_ba;
	struct il_tx_queue *txq = NULL;
	struct il_ht_agg *agg;
	int idx;
	int sta_id;
	int tid;
	unsigned long flags;

	/* "flow" corresponds to Tx queue */
	u16 scd_flow = le16_to_cpu(ba_resp->scd_flow);

	/* "ssn" is start of block-ack Tx win, corresponds to idx
	 * (in Tx queue's circular buffer) of first TFD/frame in win */
	u16 ba_resp_scd_ssn = le16_to_cpu(ba_resp->scd_ssn);

	if (scd_flow >= il->hw_params.max_txq_num) {
		IL_ERR("BUG_ON scd_flow is bigger than number of queues\n");
		return;
	}

	txq = &il->txq[scd_flow];
	sta_id = ba_resp->sta_id;
	tid = ba_resp->tid;
	agg = &il->stations[sta_id].tid[tid].agg;
	if (unlikely(agg->txq_id != scd_flow)) {
		/*
		 * FIXME: this is a uCode bug which need to be addressed,
		 * log the information and return for now!
		 * since it is possible happen very often and in order
		 * not to fill the syslog, don't enable the logging by default
		 */
		D_TX_REPLY("BA scd_flow %d does not match txq_id %d\n",
			   scd_flow, agg->txq_id);
		return;
	}

	/* Find idx just before block-ack win */
	idx = il_queue_dec_wrap(ba_resp_scd_ssn & 0xff, txq->q.n_bd);

	spin_lock_irqsave(&il->sta_lock, flags);

	D_TX_REPLY("N_COMPRESSED_BA [%d] Received from %pM, " "sta_id = %d\n",
		   agg->wait_for_ba, (u8 *) &ba_resp->sta_addr_lo32,
		   ba_resp->sta_id);
	D_TX_REPLY("TID = %d, SeqCtl = %d, bitmap = 0x%llx," "scd_flow = "
		   "%d, scd_ssn = %d\n", ba_resp->tid, ba_resp->seq_ctl,
		   (unsigned long long)le64_to_cpu(ba_resp->bitmap),
		   ba_resp->scd_flow, ba_resp->scd_ssn);
	D_TX_REPLY("DAT start_idx = %d, bitmap = 0x%llx\n", agg->start_idx,
		   (unsigned long long)agg->bitmap);

	/* Update driver's record of ACK vs. not for each frame in win */
	il4965_tx_status_reply_compressed_ba(il, agg, ba_resp);

	/* Release all TFDs before the SSN, i.e. all TFDs in front of
	 * block-ack win (we assume that they've been successfully
	 * transmitted ... if not, it's too late anyway). */
	if (txq->q.read_ptr != (ba_resp_scd_ssn & 0xff)) {
		/* calculate mac80211 ampdu sw queue to wake */
		int freed = il4965_tx_queue_reclaim(il, scd_flow, idx);
		il4965_free_tfds_in_queue(il, sta_id, tid, freed);

		if (il_queue_space(&txq->q) > txq->q.low_mark &&
		    il->mac80211_registered &&
		    agg->state != IL_EMPTYING_HW_QUEUE_DELBA)
			il_wake_queue(il, txq);

		il4965_txq_check_empty(il, sta_id, tid, scd_flow);
	}

	spin_unlock_irqrestore(&il->sta_lock, flags);
}