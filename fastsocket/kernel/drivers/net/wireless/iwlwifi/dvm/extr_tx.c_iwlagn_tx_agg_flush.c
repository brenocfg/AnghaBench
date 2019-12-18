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
struct TYPE_2__ {int txq_id; int state; } ;
struct iwl_tid_data {TYPE_1__ agg; } ;
struct iwl_priv {int /*<<< orphan*/  trans; int /*<<< orphan*/  agg_q_alloc; int /*<<< orphan*/  sta_lock; struct iwl_tid_data** tid_data; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
typedef  enum iwl_agg_state { ____Placeholder_iwl_agg_state } iwl_agg_state ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int IWL_AGG_OFF ; 
 int IWL_AGG_ON ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_priv*,char*,int,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 int iwl_sta_id (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_trans_txq_disable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwlagn_dealloc_agg_txq (struct iwl_priv*,int) ; 
 scalar_t__ iwlagn_txfifo_flush (struct iwl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

int iwlagn_tx_agg_flush(struct iwl_priv *priv, struct ieee80211_vif *vif,
			struct ieee80211_sta *sta, u16 tid)
{
	struct iwl_tid_data *tid_data;
	enum iwl_agg_state agg_state;
	int sta_id, txq_id;
	sta_id = iwl_sta_id(sta);

	/*
	 * First set the agg state to OFF to avoid calling
	 * ieee80211_stop_tx_ba_cb in iwlagn_check_ratid_empty.
	 */
	spin_lock_bh(&priv->sta_lock);

	tid_data = &priv->tid_data[sta_id][tid];
	txq_id = tid_data->agg.txq_id;
	agg_state = tid_data->agg.state;
	IWL_DEBUG_TX_QUEUES(priv, "Flush AGG: sta %d tid %d q %d state %d\n",
			    sta_id, tid, txq_id, tid_data->agg.state);

	tid_data->agg.state = IWL_AGG_OFF;

	spin_unlock_bh(&priv->sta_lock);

	if (iwlagn_txfifo_flush(priv, BIT(txq_id)))
		IWL_ERR(priv, "Couldn't flush the AGG queue\n");

	if (test_bit(txq_id, priv->agg_q_alloc)) {
		/*
		 * If the transport didn't know that we wanted to start
		 * agreggation, don't tell it that we want to stop them.
		 * This can happen when we don't get the addBA response on
		 * time, or we hadn't time to drain the AC queues.
		 */
		if (agg_state == IWL_AGG_ON)
			iwl_trans_txq_disable(priv->trans, txq_id);
		else
			IWL_DEBUG_TX_QUEUES(priv, "Don't disable tx agg: %d\n",
					    agg_state);
		iwlagn_dealloc_agg_txq(priv, txq_id);
	}

	return 0;
}