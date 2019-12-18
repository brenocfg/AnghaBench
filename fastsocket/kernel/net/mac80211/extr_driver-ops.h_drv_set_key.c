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
struct ieee80211_key_conf {int dummy; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;
struct TYPE_2__ {int (* set_key ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct ieee80211_sta*,struct ieee80211_key_conf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  check_sdata_in_driver (struct ieee80211_sub_if_data*) ; 
 struct ieee80211_sub_if_data* get_bss_sdata (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct ieee80211_sta*,struct ieee80211_key_conf*) ; 
 int /*<<< orphan*/  trace_drv_return_int (struct ieee80211_local*,int) ; 
 int /*<<< orphan*/  trace_drv_set_key (struct ieee80211_local*,int,struct ieee80211_sub_if_data*,struct ieee80211_sta*,struct ieee80211_key_conf*) ; 

__attribute__((used)) static inline int drv_set_key(struct ieee80211_local *local,
			      enum set_key_cmd cmd,
			      struct ieee80211_sub_if_data *sdata,
			      struct ieee80211_sta *sta,
			      struct ieee80211_key_conf *key)
{
	int ret;

	might_sleep();

	sdata = get_bss_sdata(sdata);
	check_sdata_in_driver(sdata);

	trace_drv_set_key(local, cmd, sdata, sta, key);
	ret = local->ops->set_key(&local->hw, cmd, &sdata->vif, sta, key);
	trace_drv_return_int(local, ret);
	return ret;
}