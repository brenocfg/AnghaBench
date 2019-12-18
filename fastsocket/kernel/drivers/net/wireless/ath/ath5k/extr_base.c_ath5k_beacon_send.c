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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ath5k_vif {struct ath5k_buf* bbuf; } ;
struct ath5k_hw {size_t bhalq; int bmisscount; scalar_t__ opmode; int num_ap_vifs; int num_mesh_vifs; int bintval; int /*<<< orphan*/  bsent; int /*<<< orphan*/  hw; TYPE_1__* cabq; int /*<<< orphan*/ * txqs; struct ieee80211_vif** bslot; int /*<<< orphan*/  reset_work; } ;
struct ath5k_buf {int /*<<< orphan*/  desc; scalar_t__ daddr; int /*<<< orphan*/ * skb; } ;
struct TYPE_2__ {scalar_t__ txq_len; scalar_t__ txq_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ATH5K_DBG_UNLIMIT (struct ath5k_hw*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_BEACON ; 
 int /*<<< orphan*/  ATH5K_DEBUG_RESET ; 
 int /*<<< orphan*/  ATH5K_WARN (struct ath5k_hw*,char*,...) ; 
 int ATH_BCBUF ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int TSF_TO_TU (scalar_t__) ; 
 int ath5k_beacon_update (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 scalar_t__ ath5k_hw_get_tsf64 (struct ath5k_hw*) ; 
 scalar_t__ ath5k_hw_num_tx_pending (struct ath5k_hw*,size_t) ; 
 int /*<<< orphan*/  ath5k_hw_set_txdp (struct ath5k_hw*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  ath5k_hw_start_tx_dma (struct ath5k_hw*,size_t) ; 
 int ath5k_hw_stop_beacon_queue (struct ath5k_hw*,size_t) ; 
 int /*<<< orphan*/  ath5k_tx_queue (int /*<<< orphan*/ ,struct sk_buff*,TYPE_1__*) ; 
 struct sk_buff* ieee80211_get_buffered_bc (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ath5k_tx (struct ath5k_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
ath5k_beacon_send(struct ath5k_hw *ah)
{
	struct ieee80211_vif *vif;
	struct ath5k_vif *avf;
	struct ath5k_buf *bf;
	struct sk_buff *skb;
	int err;

	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON, "in beacon_send\n");

	/*
	 * Check if the previous beacon has gone out.  If
	 * not, don't don't try to post another: skip this
	 * period and wait for the next.  Missed beacons
	 * indicate a problem and should not occur.  If we
	 * miss too many consecutive beacons reset the device.
	 */
	if (unlikely(ath5k_hw_num_tx_pending(ah, ah->bhalq) != 0)) {
		ah->bmisscount++;
		ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
			"missed %u consecutive beacons\n", ah->bmisscount);
		if (ah->bmisscount > 10) {	/* NB: 10 is a guess */
			ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
				"stuck beacon time (%u missed)\n",
				ah->bmisscount);
			ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
				  "stuck beacon, resetting\n");
			ieee80211_queue_work(ah->hw, &ah->reset_work);
		}
		return;
	}
	if (unlikely(ah->bmisscount != 0)) {
		ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
			"resume beacon xmit after %u misses\n",
			ah->bmisscount);
		ah->bmisscount = 0;
	}

	if ((ah->opmode == NL80211_IFTYPE_AP && ah->num_ap_vifs +
			ah->num_mesh_vifs > 1) ||
			ah->opmode == NL80211_IFTYPE_MESH_POINT) {
		u64 tsf = ath5k_hw_get_tsf64(ah);
		u32 tsftu = TSF_TO_TU(tsf);
		int slot = ((tsftu % ah->bintval) * ATH_BCBUF) / ah->bintval;
		vif = ah->bslot[(slot + 1) % ATH_BCBUF];
		ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
			"tsf %llx tsftu %x intval %u slot %u vif %p\n",
			(unsigned long long)tsf, tsftu, ah->bintval, slot, vif);
	} else /* only one interface */
		vif = ah->bslot[0];

	if (!vif)
		return;

	avf = (void *)vif->drv_priv;
	bf = avf->bbuf;

	/*
	 * Stop any current dma and put the new frame on the queue.
	 * This should never fail since we check above that no frames
	 * are still pending on the queue.
	 */
	if (unlikely(ath5k_hw_stop_beacon_queue(ah, ah->bhalq))) {
		ATH5K_WARN(ah, "beacon queue %u didn't start/stop ?\n", ah->bhalq);
		/* NB: hw still stops DMA, so proceed */
	}

	/* refresh the beacon for AP or MESH mode */
	if (ah->opmode == NL80211_IFTYPE_AP ||
	    ah->opmode == NL80211_IFTYPE_MESH_POINT) {
		err = ath5k_beacon_update(ah->hw, vif);
		if (err)
			return;
	}

	if (unlikely(bf->skb == NULL || ah->opmode == NL80211_IFTYPE_STATION ||
		     ah->opmode == NL80211_IFTYPE_MONITOR)) {
		ATH5K_WARN(ah, "bf=%p bf_skb=%p\n", bf, bf->skb);
		return;
	}

	trace_ath5k_tx(ah, bf->skb, &ah->txqs[ah->bhalq]);

	ath5k_hw_set_txdp(ah, ah->bhalq, bf->daddr);
	ath5k_hw_start_tx_dma(ah, ah->bhalq);
	ATH5K_DBG(ah, ATH5K_DEBUG_BEACON, "TXDP[%u] = %llx (%p)\n",
		ah->bhalq, (unsigned long long)bf->daddr, bf->desc);

	skb = ieee80211_get_buffered_bc(ah->hw, vif);
	while (skb) {
		ath5k_tx_queue(ah->hw, skb, ah->cabq);

		if (ah->cabq->txq_len >= ah->cabq->txq_max)
			break;

		skb = ieee80211_get_buffered_bc(ah->hw, vif);
	}

	ah->bsent++;
}