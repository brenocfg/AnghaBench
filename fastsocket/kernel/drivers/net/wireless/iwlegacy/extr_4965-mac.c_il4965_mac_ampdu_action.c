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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct il_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  status; TYPE_1__* cfg; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {struct il_priv* priv; } ;
typedef  enum ieee80211_ampdu_mlme_action { ____Placeholder_ieee80211_ampdu_mlme_action } ieee80211_ampdu_mlme_action ;
struct TYPE_2__ {int sku; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_HT (char*,...) ; 
 int EACCES ; 
 int EINVAL ; 
#define  IEEE80211_AMPDU_RX_START 134 
#define  IEEE80211_AMPDU_RX_STOP 133 
#define  IEEE80211_AMPDU_TX_OPERATIONAL 132 
#define  IEEE80211_AMPDU_TX_START 131 
#define  IEEE80211_AMPDU_TX_STOP_CONT 130 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH 129 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH_CONT 128 
 int IL_SKU_N ; 
 int /*<<< orphan*/  S_EXIT_PENDING ; 
 int il4965_sta_rx_agg_start (struct il_priv*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int il4965_sta_rx_agg_stop (struct il_priv*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int il4965_tx_agg_start (struct il_priv*,struct ieee80211_vif*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int il4965_tx_agg_stop (struct il_priv*,struct ieee80211_vif*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
il4965_mac_ampdu_action(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			enum ieee80211_ampdu_mlme_action action,
			struct ieee80211_sta *sta, u16 tid, u16 * ssn,
			u8 buf_size)
{
	struct il_priv *il = hw->priv;
	int ret = -EINVAL;

	D_HT("A-MPDU action on addr %pM tid %d\n", sta->addr, tid);

	if (!(il->cfg->sku & IL_SKU_N))
		return -EACCES;

	mutex_lock(&il->mutex);

	switch (action) {
	case IEEE80211_AMPDU_RX_START:
		D_HT("start Rx\n");
		ret = il4965_sta_rx_agg_start(il, sta, tid, *ssn);
		break;
	case IEEE80211_AMPDU_RX_STOP:
		D_HT("stop Rx\n");
		ret = il4965_sta_rx_agg_stop(il, sta, tid);
		if (test_bit(S_EXIT_PENDING, &il->status))
			ret = 0;
		break;
	case IEEE80211_AMPDU_TX_START:
		D_HT("start Tx\n");
		ret = il4965_tx_agg_start(il, vif, sta, tid, ssn);
		break;
	case IEEE80211_AMPDU_TX_STOP_CONT:
	case IEEE80211_AMPDU_TX_STOP_FLUSH:
	case IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		D_HT("stop Tx\n");
		ret = il4965_tx_agg_stop(il, vif, sta, tid);
		if (test_bit(S_EXIT_PENDING, &il->status))
			ret = 0;
		break;
	case IEEE80211_AMPDU_TX_OPERATIONAL:
		ret = 0;
		break;
	}
	mutex_unlock(&il->mutex);

	return ret;
}