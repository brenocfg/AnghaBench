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
struct iwl_priv {int /*<<< orphan*/  trans; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  mutex; scalar_t__ is_open; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_cancel_deferred_work (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_down (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_trans_stop_hw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwlagn_mac_stop(struct ieee80211_hw *hw)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);

	IWL_DEBUG_MAC80211(priv, "enter\n");

	if (!priv->is_open)
		return;

	priv->is_open = 0;

	mutex_lock(&priv->mutex);
	iwl_down(priv);
	mutex_unlock(&priv->mutex);

	iwl_cancel_deferred_work(priv);

	flush_workqueue(priv->workqueue);

	/* User space software may expect getting rfkill changes
	 * even if interface is down, trans->down will leave the RF
	 * kill interrupt enabled
	 */
	iwl_trans_stop_hw(priv->trans, false);

	IWL_DEBUG_MAC80211(priv, "leave\n");
}