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
struct sta_info {int dummy; } ;
struct ieee80211_if_managed {int flags; int /*<<< orphan*/  bssid; int /*<<< orphan*/  associated; scalar_t__ broken_ap; int /*<<< orphan*/  powersave; } ;
struct TYPE_2__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_1__ u; } ;

/* Variables and functions */
 int IEEE80211_STA_BEACON_POLL ; 
 int IEEE80211_STA_CONNECTION_POLL ; 
 int /*<<< orphan*/  WLAN_STA_AUTHORIZED ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ieee80211_powersave_allowed(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_if_managed *mgd = &sdata->u.mgd;
	struct sta_info *sta = NULL;
	bool authorized = false;

	if (!mgd->powersave)
		return false;

	if (mgd->broken_ap)
		return false;

	if (!mgd->associated)
		return false;

	if (mgd->flags & (IEEE80211_STA_BEACON_POLL |
			  IEEE80211_STA_CONNECTION_POLL))
		return false;

	rcu_read_lock();
	sta = sta_info_get(sdata, mgd->bssid);
	if (sta)
		authorized = test_sta_flag(sta, WLAN_STA_AUTHORIZED);
	rcu_read_unlock();

	return authorized;
}