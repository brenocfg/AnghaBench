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
struct ieee80211_sub_if_data {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct ieee80211_local {int /*<<< orphan*/  iflist_mtx; int /*<<< orphan*/  monitor_sdata; TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int IEEE80211_HW_WANT_MONITOR_VIF ; 
 int /*<<< orphan*/  drv_remove_interface (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_vif_release_channel (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ieee80211_sub_if_data* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_net () ; 

void ieee80211_del_virtual_monitor(struct ieee80211_local *local)
{
	struct ieee80211_sub_if_data *sdata;

	if (!(local->hw.flags & IEEE80211_HW_WANT_MONITOR_VIF))
		return;

	ASSERT_RTNL();

	mutex_lock(&local->iflist_mtx);

	sdata = rcu_dereference_protected(local->monitor_sdata,
					  lockdep_is_held(&local->iflist_mtx));
	if (!sdata) {
		mutex_unlock(&local->iflist_mtx);
		return;
	}

	rcu_assign_pointer(local->monitor_sdata, NULL);
	mutex_unlock(&local->iflist_mtx);

	synchronize_net();

	ieee80211_vif_release_channel(sdata);

	drv_remove_interface(local, sdata);

	kfree(sdata);
}