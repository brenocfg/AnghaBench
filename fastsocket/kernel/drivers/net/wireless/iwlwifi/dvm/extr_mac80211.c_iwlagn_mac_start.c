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
struct iwl_priv {int is_open; int /*<<< orphan*/  status; int /*<<< orphan*/  mutex; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  STATUS_READY ; 
 scalar_t__ WARN_ON (int) ; 
 int __iwl_up (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwlagn_led_enable (struct iwl_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwlagn_mac_start(struct ieee80211_hw *hw)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	int ret;

	IWL_DEBUG_MAC80211(priv, "enter\n");

	/* we should be verifying the device is ready to be opened */
	mutex_lock(&priv->mutex);
	ret = __iwl_up(priv);
	mutex_unlock(&priv->mutex);
	if (ret)
		return ret;

	IWL_DEBUG_INFO(priv, "Start UP work done.\n");

	/* Now we should be done, and the READY bit should be set. */
	if (WARN_ON(!test_bit(STATUS_READY, &priv->status)))
		ret = -EIO;

	iwlagn_led_enable(priv);

	priv->is_open = 1;
	IWL_DEBUG_MAC80211(priv, "leave\n");
	return 0;
}