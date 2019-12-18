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
typedef  size_t u16 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct ath9k_htc_sta {int /*<<< orphan*/ * tid_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_lock; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ah; TYPE_1__ tx; } ;
typedef  enum ieee80211_ampdu_mlme_action { ____Placeholder_ieee80211_ampdu_mlme_action } ieee80211_ampdu_mlme_action ;

/* Variables and functions */
 int /*<<< orphan*/  AGGR_OPERATIONAL ; 
#define  IEEE80211_AMPDU_RX_START 134 
#define  IEEE80211_AMPDU_RX_STOP 133 
#define  IEEE80211_AMPDU_TX_OPERATIONAL 132 
#define  IEEE80211_AMPDU_TX_START 131 
#define  IEEE80211_AMPDU_TX_STOP_CONT 130 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH 129 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH_CONT 128 
 int /*<<< orphan*/  ath9k_htc_ps_restore (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_wakeup (struct ath9k_htc_priv*) ; 
 int ath9k_htc_tx_aggr_oper (struct ath9k_htc_priv*,struct ieee80211_vif*,struct ieee80211_sta*,int,size_t) ; 
 int /*<<< orphan*/  ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_start_tx_ba_cb_irqsafe (struct ieee80211_vif*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_cb_irqsafe (struct ieee80211_vif*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_htc_ampdu_action(struct ieee80211_hw *hw,
				  struct ieee80211_vif *vif,
				  enum ieee80211_ampdu_mlme_action action,
				  struct ieee80211_sta *sta,
				  u16 tid, u16 *ssn, u8 buf_size)
{
	struct ath9k_htc_priv *priv = hw->priv;
	struct ath9k_htc_sta *ista;
	int ret = 0;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);

	switch (action) {
	case IEEE80211_AMPDU_RX_START:
		break;
	case IEEE80211_AMPDU_RX_STOP:
		break;
	case IEEE80211_AMPDU_TX_START:
		ret = ath9k_htc_tx_aggr_oper(priv, vif, sta, action, tid);
		if (!ret)
			ieee80211_start_tx_ba_cb_irqsafe(vif, sta->addr, tid);
		break;
	case IEEE80211_AMPDU_TX_STOP_CONT:
	case IEEE80211_AMPDU_TX_STOP_FLUSH:
	case IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		ath9k_htc_tx_aggr_oper(priv, vif, sta, action, tid);
		ieee80211_stop_tx_ba_cb_irqsafe(vif, sta->addr, tid);
		break;
	case IEEE80211_AMPDU_TX_OPERATIONAL:
		ista = (struct ath9k_htc_sta *) sta->drv_priv;
		spin_lock_bh(&priv->tx.tx_lock);
		ista->tid_state[tid] = AGGR_OPERATIONAL;
		spin_unlock_bh(&priv->tx.tx_lock);
		break;
	default:
		ath_err(ath9k_hw_common(priv->ah), "Unknown AMPDU action\n");
	}

	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);

	return ret;
}