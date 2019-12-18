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
typedef  int u8 ;
typedef  unsigned int u16 ;
struct sk_buff {unsigned int len; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_4__* rates; int /*<<< orphan*/  vif; TYPE_1__* hw_key; } ;
struct ieee80211_tx_info {int flags; TYPE_5__ control; } ;
struct ieee80211_rate {unsigned int hw_value_short; unsigned int hw_value; } ;
struct ath5k_txq {int /*<<< orphan*/  lock; int /*<<< orphan*/  qnum; scalar_t__* link; int /*<<< orphan*/  txq_len; int /*<<< orphan*/  q; } ;
struct TYPE_9__ {scalar_t__ cap_has_mrr_support; } ;
struct TYPE_8__ {int txp_requested; } ;
struct ath5k_hw {int (* ah_setup_tx_desc ) (struct ath5k_hw*,struct ath5k_desc*,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ;int /*<<< orphan*/  dev; int /*<<< orphan*/  hw; TYPE_3__ ah_capabilities; int /*<<< orphan*/  ah_tx_ant; TYPE_2__ ah_txpower; } ;
struct ath5k_desc {scalar_t__ ds_link; int /*<<< orphan*/  ds_data; } ;
struct ath5k_buf {int /*<<< orphan*/  skbaddr; scalar_t__ daddr; int /*<<< orphan*/  list; struct sk_buff* skb; struct ath5k_desc* desc; } ;
typedef  int /*<<< orphan*/  mrr_tries ;
typedef  int /*<<< orphan*/  mrr_rate ;
struct TYPE_12__ {unsigned int hw_value; } ;
struct TYPE_10__ {int flags; unsigned int count; } ;
struct TYPE_7__ {unsigned int hw_key_idx; scalar_t__ icv_len; } ;

/* Variables and functions */
 unsigned int AR5K_TXDESC_CLRDMASK ; 
 unsigned int AR5K_TXDESC_CTSENA ; 
 unsigned int AR5K_TXDESC_INTREQ ; 
 unsigned int AR5K_TXDESC_NOACK ; 
 unsigned int AR5K_TXDESC_RTSENA ; 
 unsigned int AR5K_TXKEYIX_INVALID ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_RC_USE_CTS_PROTECT ; 
 int IEEE80211_TX_RC_USE_RTS_CTS ; 
 int IEEE80211_TX_RC_USE_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  ath5k_hw_set_txdp (struct ath5k_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ath5k_hw_setup_mrr_tx_desc (struct ath5k_hw*,struct ath5k_desc*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ath5k_hw_start_tx_dma (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_hw_packet_type (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_ctstoself_duration (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct ieee80211_tx_info*) ; 
 struct ieee80211_rate* ieee80211_get_alt_retry_rate (int /*<<< orphan*/ ,struct ieee80211_tx_info*,int) ; 
 int /*<<< orphan*/  ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 TYPE_6__* ieee80211_get_rts_cts_rate (int /*<<< orphan*/ ,struct ieee80211_tx_info*) ; 
 struct ieee80211_rate* ieee80211_get_tx_rate (int /*<<< orphan*/ ,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_rts_duration (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct ieee80211_tx_info*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct ath5k_hw*,struct ath5k_desc*,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int
ath5k_txbuf_setup(struct ath5k_hw *ah, struct ath5k_buf *bf,
		  struct ath5k_txq *txq, int padsize)
{
	struct ath5k_desc *ds = bf->desc;
	struct sk_buff *skb = bf->skb;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	unsigned int pktlen, flags, keyidx = AR5K_TXKEYIX_INVALID;
	struct ieee80211_rate *rate;
	unsigned int mrr_rate[3], mrr_tries[3];
	int i, ret;
	u16 hw_rate;
	u16 cts_rate = 0;
	u16 duration = 0;
	u8 rc_flags;

	flags = AR5K_TXDESC_INTREQ | AR5K_TXDESC_CLRDMASK;

	/* XXX endianness */
	bf->skbaddr = dma_map_single(ah->dev, skb->data, skb->len,
			DMA_TO_DEVICE);

	rate = ieee80211_get_tx_rate(ah->hw, info);
	if (!rate) {
		ret = -EINVAL;
		goto err_unmap;
	}

	if (info->flags & IEEE80211_TX_CTL_NO_ACK)
		flags |= AR5K_TXDESC_NOACK;

	rc_flags = info->control.rates[0].flags;
	hw_rate = (rc_flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE) ?
		rate->hw_value_short : rate->hw_value;

	pktlen = skb->len;

	/* FIXME: If we are in g mode and rate is a CCK rate
	 * subtract ah->ah_txpower.txp_cck_ofdm_pwr_delta
	 * from tx power (value is in dB units already) */
	if (info->control.hw_key) {
		keyidx = info->control.hw_key->hw_key_idx;
		pktlen += info->control.hw_key->icv_len;
	}
	if (rc_flags & IEEE80211_TX_RC_USE_RTS_CTS) {
		flags |= AR5K_TXDESC_RTSENA;
		cts_rate = ieee80211_get_rts_cts_rate(ah->hw, info)->hw_value;
		duration = le16_to_cpu(ieee80211_rts_duration(ah->hw,
			info->control.vif, pktlen, info));
	}
	if (rc_flags & IEEE80211_TX_RC_USE_CTS_PROTECT) {
		flags |= AR5K_TXDESC_CTSENA;
		cts_rate = ieee80211_get_rts_cts_rate(ah->hw, info)->hw_value;
		duration = le16_to_cpu(ieee80211_ctstoself_duration(ah->hw,
			info->control.vif, pktlen, info));
	}
	ret = ah->ah_setup_tx_desc(ah, ds, pktlen,
		ieee80211_get_hdrlen_from_skb(skb), padsize,
		get_hw_packet_type(skb),
		(ah->ah_txpower.txp_requested * 2),
		hw_rate,
		info->control.rates[0].count, keyidx, ah->ah_tx_ant, flags,
		cts_rate, duration);
	if (ret)
		goto err_unmap;

	/* Set up MRR descriptor */
	if (ah->ah_capabilities.cap_has_mrr_support) {
		memset(mrr_rate, 0, sizeof(mrr_rate));
		memset(mrr_tries, 0, sizeof(mrr_tries));
		for (i = 0; i < 3; i++) {
			rate = ieee80211_get_alt_retry_rate(ah->hw, info, i);
			if (!rate)
				break;

			mrr_rate[i] = rate->hw_value;
			mrr_tries[i] = info->control.rates[i + 1].count;
		}

		ath5k_hw_setup_mrr_tx_desc(ah, ds,
			mrr_rate[0], mrr_tries[0],
			mrr_rate[1], mrr_tries[1],
			mrr_rate[2], mrr_tries[2]);
	}

	ds->ds_link = 0;
	ds->ds_data = bf->skbaddr;

	spin_lock_bh(&txq->lock);
	list_add_tail(&bf->list, &txq->q);
	txq->txq_len++;
	if (txq->link == NULL) /* is this first packet? */
		ath5k_hw_set_txdp(ah, txq->qnum, bf->daddr);
	else /* no, so only link it */
		*txq->link = bf->daddr;

	txq->link = &ds->ds_link;
	ath5k_hw_start_tx_dma(ah, txq->qnum);
	mmiowb();
	spin_unlock_bh(&txq->lock);

	return 0;
err_unmap:
	dma_unmap_single(ah->dev, bf->skbaddr, skb->len, DMA_TO_DEVICE);
	return ret;
}