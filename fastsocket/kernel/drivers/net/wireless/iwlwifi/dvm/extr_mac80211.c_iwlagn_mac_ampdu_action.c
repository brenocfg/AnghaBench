#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_13__ {int /*<<< orphan*/  flags; } ;
struct TYPE_16__ {TYPE_5__ general_params; } ;
struct TYPE_14__ {TYPE_8__ lq; } ;
struct iwl_station_priv {TYPE_6__ lq_sta; } ;
struct TYPE_12__ {int /*<<< orphan*/  use_rts_for_aggregation; } ;
struct iwl_priv {int /*<<< orphan*/  mutex; TYPE_4__ hw_params; int /*<<< orphan*/  agg_tids_count; TYPE_3__* trans; TYPE_1__* nvm_data; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum ieee80211_ampdu_mlme_action { ____Placeholder_ieee80211_ampdu_mlme_action } ieee80211_ampdu_mlme_action ;
struct TYPE_15__ {int disable_11n; } ;
struct TYPE_11__ {TYPE_2__* ops; } ;
struct TYPE_10__ {int /*<<< orphan*/  txq_enable; } ;
struct TYPE_9__ {int /*<<< orphan*/  sku_cap_11n_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int EACCES ; 
 int EINVAL ; 
#define  IEEE80211_AMPDU_RX_START 134 
#define  IEEE80211_AMPDU_RX_STOP 133 
#define  IEEE80211_AMPDU_TX_OPERATIONAL 132 
#define  IEEE80211_AMPDU_TX_START 131 
#define  IEEE80211_AMPDU_TX_STOP_CONT 130 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH 129 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH_CONT 128 
 int /*<<< orphan*/  IWL_DEBUG_HT (struct iwl_priv*,char*,...) ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*) ; 
 int IWL_DISABLE_HT_RXAGG ; 
 int IWL_DISABLE_HT_TXAGG ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  LINK_QUAL_FLAGS_SET_STA_TLC_RTS_MSK ; 
 int /*<<< orphan*/  iwl_rxon_ctx_from_vif (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_send_lq_cmd (struct iwl_priv*,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int iwl_sta_rx_agg_start (struct iwl_priv*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_sta_rx_agg_stop (struct iwl_priv*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int iwlagn_tx_agg_flush (struct iwl_priv*,struct ieee80211_vif*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int iwlagn_tx_agg_oper (struct iwl_priv*,struct ieee80211_vif*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwlagn_tx_agg_start (struct iwl_priv*,struct ieee80211_vif*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int iwlagn_tx_agg_stop (struct iwl_priv*,struct ieee80211_vif*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 TYPE_7__ iwlwifi_mod_params ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwlagn_mac_ampdu_action(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   enum ieee80211_ampdu_mlme_action action,
				   struct ieee80211_sta *sta, u16 tid, u16 *ssn,
				   u8 buf_size)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	int ret = -EINVAL;
	struct iwl_station_priv *sta_priv = (void *) sta->drv_priv;

	IWL_DEBUG_HT(priv, "A-MPDU action on addr %pM tid %d\n",
		     sta->addr, tid);

	if (!(priv->nvm_data->sku_cap_11n_enable))
		return -EACCES;

	IWL_DEBUG_MAC80211(priv, "enter\n");
	mutex_lock(&priv->mutex);

	switch (action) {
	case IEEE80211_AMPDU_RX_START:
		if (iwlwifi_mod_params.disable_11n & IWL_DISABLE_HT_RXAGG)
			break;
		IWL_DEBUG_HT(priv, "start Rx\n");
		ret = iwl_sta_rx_agg_start(priv, sta, tid, *ssn);
		break;
	case IEEE80211_AMPDU_RX_STOP:
		IWL_DEBUG_HT(priv, "stop Rx\n");
		ret = iwl_sta_rx_agg_stop(priv, sta, tid);
		break;
	case IEEE80211_AMPDU_TX_START:
		if (!priv->trans->ops->txq_enable)
			break;
		if (iwlwifi_mod_params.disable_11n & IWL_DISABLE_HT_TXAGG)
			break;
		IWL_DEBUG_HT(priv, "start Tx\n");
		ret = iwlagn_tx_agg_start(priv, vif, sta, tid, ssn);
		break;
	case IEEE80211_AMPDU_TX_STOP_FLUSH:
	case IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		IWL_DEBUG_HT(priv, "Flush Tx\n");
		ret = iwlagn_tx_agg_flush(priv, vif, sta, tid);
		break;
	case IEEE80211_AMPDU_TX_STOP_CONT:
		IWL_DEBUG_HT(priv, "stop Tx\n");
		ret = iwlagn_tx_agg_stop(priv, vif, sta, tid);
		if ((ret == 0) && (priv->agg_tids_count > 0)) {
			priv->agg_tids_count--;
			IWL_DEBUG_HT(priv, "priv->agg_tids_count = %u\n",
				     priv->agg_tids_count);
		}
		if (!priv->agg_tids_count &&
		    priv->hw_params.use_rts_for_aggregation) {
			/*
			 * switch off RTS/CTS if it was previously enabled
			 */
			sta_priv->lq_sta.lq.general_params.flags &=
				~LINK_QUAL_FLAGS_SET_STA_TLC_RTS_MSK;
			iwl_send_lq_cmd(priv, iwl_rxon_ctx_from_vif(vif),
					&sta_priv->lq_sta.lq, CMD_ASYNC, false);
		}
		break;
	case IEEE80211_AMPDU_TX_OPERATIONAL:
		ret = iwlagn_tx_agg_oper(priv, vif, sta, tid, buf_size);
		break;
	}
	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");
	return ret;
}