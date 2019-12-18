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
struct iwl_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  hw; int /*<<< orphan*/  trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_wait_tx_queue_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ iwlagn_txfifo_flush (struct iwl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void iwlagn_dev_txfifo_flush(struct iwl_priv *priv)
{
	mutex_lock(&priv->mutex);
	ieee80211_stop_queues(priv->hw);
	if (iwlagn_txfifo_flush(priv, 0)) {
		IWL_ERR(priv, "flush request fail\n");
		goto done;
	}
	IWL_DEBUG_INFO(priv, "wait transmit/flush all frames\n");
	iwl_trans_wait_tx_queue_empty(priv->trans);
done:
	ieee80211_wake_queues(priv->hw);
	mutex_unlock(&priv->mutex);
}