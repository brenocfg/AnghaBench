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
struct ieee80211_if_managed {int /*<<< orphan*/  mtx; int /*<<< orphan*/  timer; scalar_t__ auth_data; scalar_t__ assoc_data; int /*<<< orphan*/  chswitch_work; int /*<<< orphan*/  csa_connection_drop_work; int /*<<< orphan*/  request_smps_work; int /*<<< orphan*/  beacon_connection_loss_work; int /*<<< orphan*/  monitor_work; } ;
struct TYPE_2__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_destroy_assoc_data (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_destroy_auth_data (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ieee80211_mgd_stop(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;

	/*
	 * Make sure some work items will not run after this,
	 * they will not do anything but might not have been
	 * cancelled when disconnecting.
	 */
	cancel_work_sync(&ifmgd->monitor_work);
	cancel_work_sync(&ifmgd->beacon_connection_loss_work);
	cancel_work_sync(&ifmgd->request_smps_work);
	cancel_work_sync(&ifmgd->csa_connection_drop_work);
	cancel_work_sync(&ifmgd->chswitch_work);

	mutex_lock(&ifmgd->mtx);
	if (ifmgd->assoc_data)
		ieee80211_destroy_assoc_data(sdata, false);
	if (ifmgd->auth_data)
		ieee80211_destroy_auth_data(sdata, false);
	del_timer_sync(&ifmgd->timer);
	mutex_unlock(&ifmgd->mtx);
}