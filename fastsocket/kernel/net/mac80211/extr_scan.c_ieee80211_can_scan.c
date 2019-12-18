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
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {TYPE_2__ mgd; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; TYPE_1__ vif; } ;
struct ieee80211_local {int /*<<< orphan*/  roc_list; scalar_t__ radar_detect_enabled; } ;

/* Variables and functions */
 int IEEE80211_STA_BEACON_POLL ; 
 int IEEE80211_STA_CONNECTION_POLL ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ieee80211_can_scan(struct ieee80211_local *local,
			       struct ieee80211_sub_if_data *sdata)
{
	if (local->radar_detect_enabled)
		return false;

	if (!list_empty(&local->roc_list))
		return false;

	if (sdata->vif.type == NL80211_IFTYPE_STATION &&
	    sdata->u.mgd.flags & (IEEE80211_STA_BEACON_POLL |
				  IEEE80211_STA_CONNECTION_POLL))
		return false;

	return true;
}