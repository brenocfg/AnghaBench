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
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; } ;
struct ieee80211_sched_scan_ies {int dummy; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct cfg80211_sched_scan_request {int dummy; } ;
struct TYPE_2__ {int (* sched_scan_start ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cfg80211_sched_scan_request*,struct ieee80211_sched_scan_ies*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  check_sdata_in_driver (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cfg80211_sched_scan_request*,struct ieee80211_sched_scan_ies*) ; 
 int /*<<< orphan*/  trace_drv_return_int (struct ieee80211_local*,int) ; 
 int /*<<< orphan*/  trace_drv_sched_scan_start (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static inline int
drv_sched_scan_start(struct ieee80211_local *local,
		     struct ieee80211_sub_if_data *sdata,
		     struct cfg80211_sched_scan_request *req,
		     struct ieee80211_sched_scan_ies *ies)
{
	int ret;

	might_sleep();

	check_sdata_in_driver(sdata);

	trace_drv_sched_scan_start(local, sdata);
	ret = local->ops->sched_scan_start(&local->hw, &sdata->vif,
					      req, ies);
	trace_drv_return_int(local, ret);
	return ret;
}