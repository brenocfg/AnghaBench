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
struct mac80211_hwsim_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * hw_scan_vif; int /*<<< orphan*/ * hw_scan_request; int /*<<< orphan*/ * tmp_chan; int /*<<< orphan*/  hw; int /*<<< orphan*/  hw_scan; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct mac80211_hwsim_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mac80211_hwsim_cancel_hw_scan(struct ieee80211_hw *hw,
					  struct ieee80211_vif *vif)
{
	struct mac80211_hwsim_data *hwsim = hw->priv;

	wiphy_debug(hw->wiphy, "hwsim cancel_hw_scan\n");

	cancel_delayed_work_sync(&hwsim->hw_scan);

	mutex_lock(&hwsim->mutex);
	ieee80211_scan_completed(hwsim->hw, true);
	hwsim->tmp_chan = NULL;
	hwsim->hw_scan_request = NULL;
	hwsim->hw_scan_vif = NULL;
	mutex_unlock(&hwsim->mutex);
}