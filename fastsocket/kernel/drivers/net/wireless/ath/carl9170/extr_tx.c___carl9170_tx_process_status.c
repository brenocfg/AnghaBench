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
typedef  size_t uint8_t ;
struct sk_buff {int dummy; } ;
struct ieee80211_tx_info {int dummy; } ;
struct ar9170 {int /*<<< orphan*/ * tx_status; } ;

/* Variables and functions */
 size_t const CARL9170_TX_STATUS_QUEUE ; 
 size_t const CARL9170_TX_STATUS_RIX ; 
 size_t const CARL9170_TX_STATUS_RIX_S ; 
 size_t const CARL9170_TX_STATUS_SUCCESS ; 
 size_t const CARL9170_TX_STATUS_TRIES ; 
 size_t const CARL9170_TX_STATUS_TRIES_S ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 unsigned int* ar9170_qmap ; 
 struct sk_buff* carl9170_get_queued_skb (struct ar9170*,size_t const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carl9170_tx_fill_rateinfo (struct ar9170*,unsigned int,unsigned int,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  carl9170_tx_status (struct ar9170*,struct sk_buff*,int) ; 

__attribute__((used)) static void __carl9170_tx_process_status(struct ar9170 *ar,
	const uint8_t cookie, const uint8_t info)
{
	struct sk_buff *skb;
	struct ieee80211_tx_info *txinfo;
	unsigned int r, t, q;
	bool success = true;

	q = ar9170_qmap[info & CARL9170_TX_STATUS_QUEUE];

	skb = carl9170_get_queued_skb(ar, cookie, &ar->tx_status[q]);
	if (!skb) {
		/*
		 * We have lost the race to another thread.
		 */

		return ;
	}

	txinfo = IEEE80211_SKB_CB(skb);

	if (!(info & CARL9170_TX_STATUS_SUCCESS))
		success = false;

	r = (info & CARL9170_TX_STATUS_RIX) >> CARL9170_TX_STATUS_RIX_S;
	t = (info & CARL9170_TX_STATUS_TRIES) >> CARL9170_TX_STATUS_TRIES_S;

	carl9170_tx_fill_rateinfo(ar, r, t, txinfo);
	carl9170_tx_status(ar, skb, success);
}