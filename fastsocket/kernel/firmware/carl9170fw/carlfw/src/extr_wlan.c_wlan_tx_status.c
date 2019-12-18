#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct dma_queue {int dummy; } ;
struct dma_desc {int ctrl; } ;
struct TYPE_13__ {int /*<<< orphan*/  frame_control; } ;
struct TYPE_14__ {TYPE_4__ i3e; } ;
struct TYPE_10__ {int /*<<< orphan*/  ampdu; } ;
struct TYPE_11__ {TYPE_1__ mac; } ;
struct TYPE_15__ {TYPE_5__ data; TYPE_2__ hdr; } ;
struct TYPE_12__ {unsigned int queue; int cab; size_t vif_id; } ;
struct carl9170_tx_superframe {TYPE_6__ f; TYPE_3__ s; } ;
struct TYPE_17__ {int /*<<< orphan*/  down_queue; } ;
struct TYPE_16__ {int fw_desc_available; int /*<<< orphan*/  queued_bar; int /*<<< orphan*/ * cab_queue_len; int /*<<< orphan*/  (* fw_desc_callback ) (struct carl9170_tx_superframe*,int) ;struct dma_desc* fw_desc; struct carl9170_tx_superframe* fw_desc_data; int /*<<< orphan*/  tx_retry; scalar_t__* last_super_num; } ;
struct TYPE_18__ {TYPE_8__ pta; TYPE_7__ wlan; } ;

/* Variables and functions */
 int AR9170_CTRL_BAFAIL ; 
 int AR9170_CTRL_FAIL ; 
 int AR9170_CTRL_TXFAIL ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IEEE80211_FCTL_RETRY ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_put (int /*<<< orphan*/ *,struct dma_desc*) ; 
 int /*<<< orphan*/  dma_rearm (struct dma_desc*) ; 
 int /*<<< orphan*/  dma_reclaim (int /*<<< orphan*/ *,struct dma_desc*) ; 
 struct dma_desc* dma_unlink_head (struct dma_queue*) ; 
 int /*<<< orphan*/  down_trigger () ; 
 TYPE_9__ fw ; 
 struct carl9170_tx_superframe* get_super (struct dma_desc*) ; 
 scalar_t__ ieee80211_is_back_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct carl9170_tx_superframe*,int) ; 
 int /*<<< orphan*/  unhide_super (struct dma_desc*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wlan_tx_complete (struct carl9170_tx_superframe*,int) ; 
 scalar_t__ wlan_tx_consume_retry (struct carl9170_tx_superframe*) ; 
 int /*<<< orphan*/  wlan_txunstuck (unsigned int) ; 

__attribute__((used)) static bool wlan_tx_status(struct dma_queue *queue,
			   struct dma_desc *desc)
{
	struct carl9170_tx_superframe *super = get_super(desc);
	unsigned int qidx = super->s.queue;
	bool txfail = false, success;

	success = true;

	/* update hangcheck */
	fw.wlan.last_super_num[qidx] = 0;

	/*
	 * Note:
	 * There could be a corner case when the TXFAIL is set
	 * even though the frame was properly ACKed by the peer:
	 *   a BlockAckReq with the immediate policy will cause
	 *   the receiving peer to produce a BlockACK unfortunately
	 *   the MAC in this chip seems to be expecting a legacy
	 *   ACK and marks the BAR as failed!
	 */

	if (!!(desc->ctrl & AR9170_CTRL_FAIL)) {
		txfail = !!(desc->ctrl & AR9170_CTRL_TXFAIL);

		/* reset retry indicator flags */
		desc->ctrl &= ~(AR9170_CTRL_TXFAIL | AR9170_CTRL_BAFAIL);

		/*
		 * Note: wlan_tx_consume_retry will override the old
		 * phy [CCK,OFDM, HT, BW20/40, MCS...] and mac vectors
		 * [AMPDU,RTS/CTS,...] therefore be careful when they
		 * are used.
		 */
		if (wlan_tx_consume_retry(super)) {
			/*
			 * retry for simple and aggregated 802.11 frames.
			 *
			 * Note: We must not mess up the original frame
			 * order.
			 */

			if (!super->f.hdr.mac.ampdu) {
				/*
				 * 802.11 - 7.1.3.1.5.
				 * set "Retry Field" for consecutive attempts
				 *
				 * Note: For AMPDU see:
				 * 802.11n 9.9.1.6 "Retransmit Procedures"
				 */
				super->f.data.i3e.frame_control |=
					cpu_to_le16(IEEE80211_FCTL_RETRY);
			}

			if (txfail) {
				/* Normal TX Failure */

				/* demise descriptor ownership back to the hardware */
				dma_rearm(desc);

				/*
				 * And this will get the queue going again.
				 * To understand why: you have to get the HW
				 * specs... But sadly I never saw them.
				 */
				wlan_txunstuck(qidx);

				/* abort cycle - this is necessary due to HW design */
				return false;
			} else {
				/* (HT-) BlockACK failure */

				/*
				 * Unlink the failed attempt and put it into
				 * the retry queue. The caller routine must
				 * be aware of this so the frames don't get lost.
				 */

#ifndef CONFIG_CARL9170FW_DEBUG
				dma_unlink_head(queue);
#else /* CONFIG_CARL9170FW_DEBUG */
				BUG_ON(dma_unlink_head(queue) != desc);
#endif /* CONFIG_CARL9170FW_DEBUG */
				dma_put(&fw.wlan.tx_retry, desc);
				return true;
			}
		} else {
			/* out of frame attempts - discard frame */
			success = false;
		}
	}

#ifndef CONFIG_CARL9170FW_DEBUG
	dma_unlink_head(queue);
#else /* CONFIG_CARL9170FW_DEBUG */
	BUG_ON(dma_unlink_head(queue) != desc);
#endif /* CONFIG_CARL9170FW_DEBUG */
	if (txfail) {
		/*
		 * Issue the queue bump,
		 * We need to do this in case this was the frame's last
		 * possible retry attempt and it unfortunately: it failed.
		 */

		wlan_txunstuck(qidx);
	}

	unhide_super(desc);

	if (unlikely(super == fw.wlan.fw_desc_data)) {
		fw.wlan.fw_desc = desc;
		fw.wlan.fw_desc_available = 1;

		if (fw.wlan.fw_desc_callback)
			fw.wlan.fw_desc_callback(super, success);

		return true;
	}

#ifdef CONFIG_CARL9170FW_CAB_QUEUE
	if (unlikely(super->s.cab))
		fw.wlan.cab_queue_len[super->s.vif_id]--;
#endif /* CONFIG_CARL9170FW_CAB_QUEUE */

	wlan_tx_complete(super, success);

	if (ieee80211_is_back_req(super->f.data.i3e.frame_control)) {
		fw.wlan.queued_bar--;
	}

	/* recycle freed descriptors */
	dma_reclaim(&fw.pta.down_queue, desc);
	down_trigger();
	return true;
}