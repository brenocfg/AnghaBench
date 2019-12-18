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
struct ieee80211_sta {int dummy; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sta_remove ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_sta*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  check_sdata_in_driver (struct ieee80211_sub_if_data*) ; 
 struct ieee80211_sub_if_data* get_bss_sdata (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  trace_drv_return_void (struct ieee80211_local*) ; 
 int /*<<< orphan*/  trace_drv_sta_remove (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct ieee80211_sta*) ; 

__attribute__((used)) static inline void drv_sta_remove(struct ieee80211_local *local,
				  struct ieee80211_sub_if_data *sdata,
				  struct ieee80211_sta *sta)
{
	might_sleep();

	sdata = get_bss_sdata(sdata);
	check_sdata_in_driver(sdata);

	trace_drv_sta_remove(local, sdata, sta);
	if (local->ops->sta_remove)
		local->ops->sta_remove(&local->hw, &sdata->vif, sta);

	trace_drv_return_void(local);
}