#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_sched_scan_ies {int /*<<< orphan*/ * ie; int /*<<< orphan*/ * len; } ;
struct TYPE_6__ {TYPE_2__* wiphy; } ;
struct ieee80211_local {int scan_ies_len; int /*<<< orphan*/  mtx; int /*<<< orphan*/  sched_scan_sdata; TYPE_3__ hw; TYPE_1__* ops; } ;
struct cfg80211_sched_scan_request {int ie_len; int /*<<< orphan*/  ie; } ;
struct TYPE_5__ {int /*<<< orphan*/ * bands; } ;
struct TYPE_4__ {int /*<<< orphan*/  sched_scan_start; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_MAX_SSID_LEN ; 
 int IEEE80211_NUM_BANDS ; 
 int drv_sched_scan_start (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct cfg80211_sched_scan_request*,struct ieee80211_sched_scan_ies*) ; 
 int /*<<< orphan*/  ieee80211_build_preq_ies (struct ieee80211_local*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ieee80211_sub_if_data*) ; 

int ieee80211_request_sched_scan_start(struct ieee80211_sub_if_data *sdata,
				       struct cfg80211_sched_scan_request *req)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_sched_scan_ies sched_scan_ies = {};
	int ret, i, iebufsz;

	iebufsz = 2 + IEEE80211_MAX_SSID_LEN +
		  local->scan_ies_len + req->ie_len;

	mutex_lock(&local->mtx);

	if (rcu_access_pointer(local->sched_scan_sdata)) {
		ret = -EBUSY;
		goto out;
	}

	if (!local->ops->sched_scan_start) {
		ret = -ENOTSUPP;
		goto out;
	}

	for (i = 0; i < IEEE80211_NUM_BANDS; i++) {
		if (!local->hw.wiphy->bands[i])
			continue;

		sched_scan_ies.ie[i] = kzalloc(iebufsz, GFP_KERNEL);
		if (!sched_scan_ies.ie[i]) {
			ret = -ENOMEM;
			goto out_free;
		}

		sched_scan_ies.len[i] =
			ieee80211_build_preq_ies(local, sched_scan_ies.ie[i],
						 iebufsz, req->ie, req->ie_len,
						 i, (u32) -1, 0);
	}

	ret = drv_sched_scan_start(local, sdata, req, &sched_scan_ies);
	if (ret == 0)
		rcu_assign_pointer(local->sched_scan_sdata, sdata);

out_free:
	while (i > 0)
		kfree(sched_scan_ies.ie[--i]);
out:
	mutex_unlock(&local->mtx);
	return ret;
}