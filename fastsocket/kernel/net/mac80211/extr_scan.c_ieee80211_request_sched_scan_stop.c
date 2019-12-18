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
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  mtx; int /*<<< orphan*/  sched_scan_sdata; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  sched_scan_stop; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  drv_sched_scan_stop (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 

int ieee80211_request_sched_scan_stop(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;
	int ret = 0;

	mutex_lock(&local->mtx);

	if (!local->ops->sched_scan_stop) {
		ret = -ENOTSUPP;
		goto out;
	}

	if (rcu_access_pointer(local->sched_scan_sdata))
		drv_sched_scan_stop(local, sdata);

out:
	mutex_unlock(&local->mtx);

	return ret;
}