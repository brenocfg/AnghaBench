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
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_2__ {int (* get_rssi ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_sta*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  might_sleep () ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_sta*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_drv_get_rssi (struct ieee80211_local*,struct ieee80211_sta*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int drv_get_rssi(struct ieee80211_local *local,
				struct ieee80211_sub_if_data *sdata,
				struct ieee80211_sta *sta,
				s8 *rssi_dbm)
{
	int ret;

	might_sleep();

	ret = local->ops->get_rssi(&local->hw, &sdata->vif, sta, rssi_dbm);
	trace_drv_get_rssi(local, sta, *rssi_dbm, ret);

	return ret;
}