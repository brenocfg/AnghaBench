#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct TYPE_12__ {TYPE_5__* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_6__ control; } ;
struct TYPE_8__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_9__ {TYPE_2__ beacon; } ;
struct ieee80211_mgmt {TYPE_3__ u; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; } ;
struct ath_vif {int /*<<< orphan*/  tsf_adjust; struct ath_buf* av_bcbuf; } ;
struct ath_txq {int axq_depth; int /*<<< orphan*/  axq_lock; } ;
struct TYPE_10__ {int seq_no; } ;
struct TYPE_7__ {struct ath_txq* cabq; } ;
struct ath_softc {int nvifs; int /*<<< orphan*/  dev; TYPE_4__ tx; TYPE_1__ beacon; int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int dummy; } ;
struct ath_buf {scalar_t__ bf_buf_addr; struct sk_buff* bf_mpdu; } ;
struct TYPE_11__ {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEACON ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int IEEE80211_SCTL_FRAG ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_ASSIGN_SEQ ; 
 int /*<<< orphan*/  ath9k_beacon_setup (struct ath_softc*,struct ieee80211_vif*,struct ath_buf*,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_tx_cabq (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath_draintxq (struct ath_softc*,struct ath_txq*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ieee80211_beacon_get (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 struct sk_buff* ieee80211_get_buffered_bc (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ath_buf *ath9k_beacon_generate(struct ieee80211_hw *hw,
					     struct ieee80211_vif *vif)
{
	struct ath_softc *sc = hw->priv;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_buf *bf;
	struct ath_vif *avp = (void *)vif->drv_priv;
	struct sk_buff *skb;
	struct ath_txq *cabq = sc->beacon.cabq;
	struct ieee80211_tx_info *info;
	struct ieee80211_mgmt *mgmt_hdr;
	int cabq_depth;

	if (avp->av_bcbuf == NULL)
		return NULL;

	bf = avp->av_bcbuf;
	skb = bf->bf_mpdu;
	if (skb) {
		dma_unmap_single(sc->dev, bf->bf_buf_addr,
				 skb->len, DMA_TO_DEVICE);
		dev_kfree_skb_any(skb);
		bf->bf_buf_addr = 0;
		bf->bf_mpdu = NULL;
	}

	skb = ieee80211_beacon_get(hw, vif);
	if (skb == NULL)
		return NULL;

	bf->bf_mpdu = skb;

	mgmt_hdr = (struct ieee80211_mgmt *)skb->data;
	mgmt_hdr->u.beacon.timestamp = avp->tsf_adjust;

	info = IEEE80211_SKB_CB(skb);
	if (info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ) {
		/*
		 * TODO: make sure the seq# gets assigned properly (vs. other
		 * TX frames)
		 */
		struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
		sc->tx.seq_no += 0x10;
		hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
		hdr->seq_ctrl |= cpu_to_le16(sc->tx.seq_no);
	}

	bf->bf_buf_addr = dma_map_single(sc->dev, skb->data,
					 skb->len, DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(sc->dev, bf->bf_buf_addr))) {
		dev_kfree_skb_any(skb);
		bf->bf_mpdu = NULL;
		bf->bf_buf_addr = 0;
		ath_err(common, "dma_mapping_error on beaconing\n");
		return NULL;
	}

	skb = ieee80211_get_buffered_bc(hw, vif);

	/*
	 * if the CABQ traffic from previous DTIM is pending and the current
	 *  beacon is also a DTIM.
	 *  1) if there is only one vif let the cab traffic continue.
	 *  2) if there are more than one vif and we are using staggered
	 *     beacons, then drain the cabq by dropping all the frames in
	 *     the cabq so that the current vifs cab traffic can be scheduled.
	 */
	spin_lock_bh(&cabq->axq_lock);
	cabq_depth = cabq->axq_depth;
	spin_unlock_bh(&cabq->axq_lock);

	if (skb && cabq_depth) {
		if (sc->nvifs > 1) {
			ath_dbg(common, BEACON,
				"Flushing previous cabq traffic\n");
			ath_draintxq(sc, cabq);
		}
	}

	ath9k_beacon_setup(sc, vif, bf, info->control.rates[0].idx);

	while (skb) {
		ath9k_tx_cabq(hw, skb);
		skb = ieee80211_get_buffered_bc(hw, vif);
	}

	return bf;
}