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
struct iwl_priv {scalar_t__ scan_type; int /*<<< orphan*/ * scan_request; int /*<<< orphan*/ * scan_vif; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_priv*,char*) ; 
 scalar_t__ IWL_SCAN_NORMAL ; 
 scalar_t__ IWL_SCAN_ROC ; 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_scan_roc_expired (struct iwl_priv*) ; 

__attribute__((used)) static void iwl_complete_scan(struct iwl_priv *priv, bool aborted)
{
	/* check if scan was requested from mac80211 */
	if (priv->scan_request) {
		IWL_DEBUG_SCAN(priv, "Complete scan in mac80211\n");
		ieee80211_scan_completed(priv->hw, aborted);
	}

	if (priv->scan_type == IWL_SCAN_ROC)
		iwl_scan_roc_expired(priv);

	priv->scan_type = IWL_SCAN_NORMAL;
	priv->scan_vif = NULL;
	priv->scan_request = NULL;
}