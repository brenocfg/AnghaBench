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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_mvm {int /*<<< orphan*/  mutex; TYPE_1__* nvm_data; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum ieee80211_ampdu_mlme_action { ____Placeholder_ieee80211_ampdu_mlme_action } ieee80211_ampdu_mlme_action ;
struct TYPE_4__ {int disable_11n; } ;
struct TYPE_3__ {int /*<<< orphan*/  sku_cap_11n_enable; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
#define  IEEE80211_AMPDU_RX_START 134 
#define  IEEE80211_AMPDU_RX_STOP 133 
#define  IEEE80211_AMPDU_TX_OPERATIONAL 132 
#define  IEEE80211_AMPDU_TX_START 131 
#define  IEEE80211_AMPDU_TX_STOP_CONT 130 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH 129 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH_CONT 128 
 int /*<<< orphan*/  IWL_DEBUG_HT (struct iwl_mvm*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int IWL_DISABLE_HT_RXAGG ; 
 int IWL_DISABLE_HT_TXAGG ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int iwl_mvm_sta_rx_agg (struct iwl_mvm*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int iwl_mvm_sta_tx_agg_flush (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_sta_tx_agg_oper (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_sta_tx_agg_start (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int iwl_mvm_sta_tx_agg_stop (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 TYPE_2__ iwlwifi_mod_params ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_mac_ampdu_action(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif,
				    enum ieee80211_ampdu_mlme_action action,
				    struct ieee80211_sta *sta, u16 tid,
				    u16 *ssn, u8 buf_size)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	int ret;

	IWL_DEBUG_HT(mvm, "A-MPDU action on addr %pM tid %d: action %d\n",
		     sta->addr, tid, action);

	if (!(mvm->nvm_data->sku_cap_11n_enable))
		return -EACCES;

	mutex_lock(&mvm->mutex);

	switch (action) {
	case IEEE80211_AMPDU_RX_START:
		if (iwlwifi_mod_params.disable_11n & IWL_DISABLE_HT_RXAGG) {
			ret = -EINVAL;
			break;
		}
		ret = iwl_mvm_sta_rx_agg(mvm, sta, tid, *ssn, true);
		break;
	case IEEE80211_AMPDU_RX_STOP:
		ret = iwl_mvm_sta_rx_agg(mvm, sta, tid, 0, false);
		break;
	case IEEE80211_AMPDU_TX_START:
		if (iwlwifi_mod_params.disable_11n & IWL_DISABLE_HT_TXAGG) {
			ret = -EINVAL;
			break;
		}
		ret = iwl_mvm_sta_tx_agg_start(mvm, vif, sta, tid, ssn);
		break;
	case IEEE80211_AMPDU_TX_STOP_CONT:
		ret = iwl_mvm_sta_tx_agg_stop(mvm, vif, sta, tid);
		break;
	case IEEE80211_AMPDU_TX_STOP_FLUSH:
	case IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		ret = iwl_mvm_sta_tx_agg_flush(mvm, vif, sta, tid);
		break;
	case IEEE80211_AMPDU_TX_OPERATIONAL:
		ret = iwl_mvm_sta_tx_agg_oper(mvm, vif, sta, tid, buf_size);
		break;
	default:
		WARN_ON_ONCE(1);
		ret = -EINVAL;
		break;
	}
	mutex_unlock(&mvm->mutex);

	return ret;
}