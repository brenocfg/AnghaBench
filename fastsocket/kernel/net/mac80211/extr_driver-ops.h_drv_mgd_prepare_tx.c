#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* mgd_prepare_tx ) (int /*<<< orphan*/ *,TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  check_sdata_in_driver (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  trace_drv_mgd_prepare_tx (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  trace_drv_return_void (struct ieee80211_local*) ; 

__attribute__((used)) static inline void drv_mgd_prepare_tx(struct ieee80211_local *local,
				      struct ieee80211_sub_if_data *sdata)
{
	might_sleep();

	check_sdata_in_driver(sdata);
	WARN_ON_ONCE(sdata->vif.type != NL80211_IFTYPE_STATION);

	trace_drv_mgd_prepare_tx(local, sdata);
	if (local->ops->mgd_prepare_tx)
		local->ops->mgd_prepare_tx(&local->hw, &sdata->vif);
	trace_drv_return_void(local);
}