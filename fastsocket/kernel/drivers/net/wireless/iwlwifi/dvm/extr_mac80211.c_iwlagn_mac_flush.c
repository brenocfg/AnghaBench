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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  trans; int /*<<< orphan*/  status; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_DEBUG_TX (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  STATUS_EXIT_PENDING ; 
 scalar_t__ iwl_is_rfkill (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_trans_wait_tx_queue_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ iwlagn_txfifo_flush (struct iwl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwlagn_mac_flush(struct ieee80211_hw *hw, u32 queues, bool drop)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);

	mutex_lock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "enter\n");

	if (test_bit(STATUS_EXIT_PENDING, &priv->status)) {
		IWL_DEBUG_TX(priv, "Aborting flush due to device shutdown\n");
		goto done;
	}
	if (iwl_is_rfkill(priv)) {
		IWL_DEBUG_TX(priv, "Aborting flush due to RF Kill\n");
		goto done;
	}

	/*
	 * mac80211 will not push any more frames for transmit
	 * until the flush is completed
	 */
	if (drop) {
		IWL_DEBUG_MAC80211(priv, "send flush command\n");
		if (iwlagn_txfifo_flush(priv, 0)) {
			IWL_ERR(priv, "flush request fail\n");
			goto done;
		}
	}
	IWL_DEBUG_MAC80211(priv, "wait transmit/flush all frames\n");
	iwl_trans_wait_tx_queue_empty(priv->trans);
done:
	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");
}