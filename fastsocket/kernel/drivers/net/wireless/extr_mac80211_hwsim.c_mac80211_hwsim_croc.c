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
struct mac80211_hwsim_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * tmp_chan; int /*<<< orphan*/  roc_done; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct mac80211_hwsim_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mac80211_hwsim_croc(struct ieee80211_hw *hw)
{
	struct mac80211_hwsim_data *hwsim = hw->priv;

	cancel_delayed_work_sync(&hwsim->roc_done);

	mutex_lock(&hwsim->mutex);
	hwsim->tmp_chan = NULL;
	mutex_unlock(&hwsim->mutex);

	wiphy_debug(hw->wiphy, "hwsim ROC canceled\n");

	return 0;
}