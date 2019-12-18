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
struct sk_buff {int dummy; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct carl9170_sta_info {int /*<<< orphan*/  sleeping; } ;
struct ar9170 {int /*<<< orphan*/  tx_ampdu_upload; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_CTL_CLEAR_PS_FILT ; 
 int IEEE80211_TX_CTL_NO_PS_BUFFER ; 
 int IEEE80211_TX_STAT_TX_FILTERED ; 
 struct ieee80211_sta* __carl9170_get_tx_sta (struct ar9170*,struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carl9170_release_dev_space (struct ar9170*,struct sk_buff*) ; 
 int /*<<< orphan*/  carl9170_tx_status (struct ar9170*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool carl9170_tx_ps_drop(struct ar9170 *ar, struct sk_buff *skb)
{
	struct ieee80211_sta *sta;
	struct carl9170_sta_info *sta_info;
	struct ieee80211_tx_info *tx_info;

	rcu_read_lock();
	sta = __carl9170_get_tx_sta(ar, skb);
	if (!sta)
		goto out_rcu;

	sta_info = (void *) sta->drv_priv;
	tx_info = IEEE80211_SKB_CB(skb);

	if (unlikely(sta_info->sleeping) &&
	    !(tx_info->flags & (IEEE80211_TX_CTL_NO_PS_BUFFER |
				IEEE80211_TX_CTL_CLEAR_PS_FILT))) {
		rcu_read_unlock();

		if (tx_info->flags & IEEE80211_TX_CTL_AMPDU)
			atomic_dec(&ar->tx_ampdu_upload);

		tx_info->flags |= IEEE80211_TX_STAT_TX_FILTERED;
		carl9170_release_dev_space(ar, skb);
		carl9170_tx_status(ar, skb, false);
		return true;
	}

out_rcu:
	rcu_read_unlock();
	return false;
}