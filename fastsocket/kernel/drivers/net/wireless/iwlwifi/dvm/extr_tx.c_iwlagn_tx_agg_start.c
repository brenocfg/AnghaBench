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
typedef  size_t u16 ;
struct TYPE_2__ {scalar_t__ state; size_t ssn; int txq_id; } ;
struct iwl_tid_data {size_t next_reclaimed; TYPE_1__ agg; int /*<<< orphan*/  seq_number; } ;
struct iwl_rxon_context {int /*<<< orphan*/ * ac_to_queue; } ;
struct iwl_priv {int /*<<< orphan*/  sta_lock; struct iwl_tid_data** tid_data; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {size_t addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 size_t IEEE80211_SEQ_TO_SN (int /*<<< orphan*/ ) ; 
 scalar_t__ IWL_AGG_OFF ; 
 scalar_t__ IWL_AGG_STARTING ; 
 int /*<<< orphan*/  IWL_DEBUG_HT (struct iwl_priv*,char*,size_t,size_t) ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_priv*,char*,size_t,...) ; 
 scalar_t__ IWL_EMPTYING_HW_QUEUE_ADDBA ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 int IWL_INVALID_STATION ; 
 size_t IWL_MAX_TID_COUNT ; 
 int /*<<< orphan*/  ieee80211_start_tx_ba_cb_irqsafe (struct ieee80211_vif*,size_t,size_t) ; 
 struct iwl_rxon_context* iwl_rxon_ctx_from_vif (struct ieee80211_vif*) ; 
 int iwl_sta_id (struct ieee80211_sta*) ; 
 int iwl_sta_tx_modify_enable_tid (struct iwl_priv*,int,size_t) ; 
 int iwlagn_alloc_agg_txq (struct iwl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 size_t* tid_to_ac ; 
 scalar_t__ unlikely (int) ; 

int iwlagn_tx_agg_start(struct iwl_priv *priv, struct ieee80211_vif *vif,
			struct ieee80211_sta *sta, u16 tid, u16 *ssn)
{
	struct iwl_rxon_context *ctx = iwl_rxon_ctx_from_vif(vif);
	struct iwl_tid_data *tid_data;
	int sta_id, txq_id, ret;

	IWL_DEBUG_HT(priv, "TX AGG request on ra = %pM tid = %d\n",
		     sta->addr, tid);

	sta_id = iwl_sta_id(sta);
	if (sta_id == IWL_INVALID_STATION) {
		IWL_ERR(priv, "Start AGG on invalid station\n");
		return -ENXIO;
	}
	if (unlikely(tid >= IWL_MAX_TID_COUNT))
		return -EINVAL;

	if (priv->tid_data[sta_id][tid].agg.state != IWL_AGG_OFF) {
		IWL_ERR(priv, "Start AGG when state is not IWL_AGG_OFF !\n");
		return -ENXIO;
	}

	txq_id = iwlagn_alloc_agg_txq(priv, ctx->ac_to_queue[tid_to_ac[tid]]);
	if (txq_id < 0) {
		IWL_DEBUG_TX_QUEUES(priv,
			"No free aggregation queue for %pM/%d\n",
			sta->addr, tid);
		return txq_id;
	}

	ret = iwl_sta_tx_modify_enable_tid(priv, sta_id, tid);
	if (ret)
		return ret;

	spin_lock_bh(&priv->sta_lock);
	tid_data = &priv->tid_data[sta_id][tid];
	tid_data->agg.ssn = IEEE80211_SEQ_TO_SN(tid_data->seq_number);
	tid_data->agg.txq_id = txq_id;

	*ssn = tid_data->agg.ssn;

	if (*ssn == tid_data->next_reclaimed) {
		IWL_DEBUG_TX_QUEUES(priv, "Can proceed: ssn = next_recl = %d\n",
				    tid_data->agg.ssn);
		tid_data->agg.state = IWL_AGG_STARTING;
		ieee80211_start_tx_ba_cb_irqsafe(vif, sta->addr, tid);
	} else {
		IWL_DEBUG_TX_QUEUES(priv, "Can't proceed: ssn %d, "
				    "next_reclaimed = %d\n",
				    tid_data->agg.ssn,
				    tid_data->next_reclaimed);
		tid_data->agg.state = IWL_EMPTYING_HW_QUEUE_ADDBA;
	}
	spin_unlock_bh(&priv->sta_lock);

	return ret;
}