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
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_default_unicast_key ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  check_sdata_in_driver (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_drv_return_void (struct ieee80211_local*) ; 
 int /*<<< orphan*/  trace_drv_set_default_unicast_key (struct ieee80211_local*,struct ieee80211_sub_if_data*,int) ; 

__attribute__((used)) static inline void
drv_set_default_unicast_key(struct ieee80211_local *local,
			    struct ieee80211_sub_if_data *sdata,
			    int key_idx)
{
	check_sdata_in_driver(sdata);

	WARN_ON_ONCE(key_idx < -1 || key_idx > 3);

	trace_drv_set_default_unicast_key(local, sdata, key_idx);
	if (local->ops->set_default_unicast_key)
		local->ops->set_default_unicast_key(&local->hw, &sdata->vif,
						    key_idx);
	trace_drv_return_void(local);
}