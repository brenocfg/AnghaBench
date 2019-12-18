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
struct iwl_priv {int valid_contexts; int /*<<< orphan*/  mutex; int /*<<< orphan*/  hw_roc_duration; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_RXON_CTX_PAN ; 
 int /*<<< orphan*/  iwl_scan_cancel_timeout (struct iwl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwlagn_disable_roc (struct iwl_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwlagn_mac_cancel_remain_on_channel(struct ieee80211_hw *hw)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);

	if (!(priv->valid_contexts & BIT(IWL_RXON_CTX_PAN)))
		return -EOPNOTSUPP;

	IWL_DEBUG_MAC80211(priv, "enter\n");
	mutex_lock(&priv->mutex);
	iwl_scan_cancel_timeout(priv, priv->hw_roc_duration);
	iwlagn_disable_roc(priv);
	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");

	return 0;
}