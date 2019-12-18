#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ len; } ;
struct ieee80211_tx_rate {int idx; int /*<<< orphan*/  count; } ;
struct TYPE_3__ {struct ieee80211_tx_rate* rates; int /*<<< orphan*/  ack_signal; } ;
struct ieee80211_tx_info {TYPE_1__ status; int /*<<< orphan*/  flags; } ;
struct ath5k_txq {int dummy; } ;
struct ath5k_tx_status {int ts_final_idx; int ts_status; int ts_antenna; int /*<<< orphan*/  ts_rssi; int /*<<< orphan*/  ts_final_retry; } ;
struct TYPE_4__ {int /*<<< orphan*/ * antenna_tx; int /*<<< orphan*/  txerr_fifo; int /*<<< orphan*/  txerr_retry; int /*<<< orphan*/  txerr_filt; int /*<<< orphan*/  ack_fail; int /*<<< orphan*/  tx_bytes_count; int /*<<< orphan*/  tx_all_count; } ;
struct ath5k_hw {int /*<<< orphan*/  hw; TYPE_2__ stats; } ;

/* Variables and functions */
 int AR5K_TXERR_FIFO ; 
 int AR5K_TXERR_FILT ; 
 int AR5K_TXERR_XRETRY ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_TX_FILTERED ; 
 int /*<<< orphan*/  ath5k_remove_padding (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  trace_ath5k_tx_complete (struct ath5k_hw*,struct sk_buff*,struct ath5k_txq*,struct ath5k_tx_status*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
ath5k_tx_frame_completed(struct ath5k_hw *ah, struct sk_buff *skb,
			 struct ath5k_txq *txq, struct ath5k_tx_status *ts)
{
	struct ieee80211_tx_info *info;
	u8 tries[3];
	int i;

	ah->stats.tx_all_count++;
	ah->stats.tx_bytes_count += skb->len;
	info = IEEE80211_SKB_CB(skb);

	tries[0] = info->status.rates[0].count;
	tries[1] = info->status.rates[1].count;
	tries[2] = info->status.rates[2].count;

	ieee80211_tx_info_clear_status(info);

	for (i = 0; i < ts->ts_final_idx; i++) {
		struct ieee80211_tx_rate *r =
			&info->status.rates[i];

		r->count = tries[i];
	}

	info->status.rates[ts->ts_final_idx].count = ts->ts_final_retry;
	info->status.rates[ts->ts_final_idx + 1].idx = -1;

	if (unlikely(ts->ts_status)) {
		ah->stats.ack_fail++;
		if (ts->ts_status & AR5K_TXERR_FILT) {
			info->flags |= IEEE80211_TX_STAT_TX_FILTERED;
			ah->stats.txerr_filt++;
		}
		if (ts->ts_status & AR5K_TXERR_XRETRY)
			ah->stats.txerr_retry++;
		if (ts->ts_status & AR5K_TXERR_FIFO)
			ah->stats.txerr_fifo++;
	} else {
		info->flags |= IEEE80211_TX_STAT_ACK;
		info->status.ack_signal = ts->ts_rssi;

		/* count the successful attempt as well */
		info->status.rates[ts->ts_final_idx].count++;
	}

	/*
	* Remove MAC header padding before giving the frame
	* back to mac80211.
	*/
	ath5k_remove_padding(skb);

	if (ts->ts_antenna > 0 && ts->ts_antenna < 5)
		ah->stats.antenna_tx[ts->ts_antenna]++;
	else
		ah->stats.antenna_tx[0]++; /* invalid */

	trace_ath5k_tx_complete(ah, skb, txq, ts);
	ieee80211_tx_status(ah->hw, skb);
}