#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ beacon_timeout; int /*<<< orphan*/  bcn_mon_timer; } ;
struct TYPE_10__ {TYPE_4__ mgd; } ;
struct TYPE_6__ {int driver_flags; } ;
struct ieee80211_sub_if_data {TYPE_5__ u; TYPE_3__* local; TYPE_1__ vif; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_8__ {TYPE_2__ hw; } ;

/* Variables and functions */
 int IEEE80211_HW_CONNECTION_MONITOR ; 
 int IEEE80211_VIF_BEACON_FILTER ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies_up (scalar_t__) ; 

void ieee80211_sta_reset_beacon_monitor(struct ieee80211_sub_if_data *sdata)
{
	if (sdata->vif.driver_flags & IEEE80211_VIF_BEACON_FILTER)
		return;

	if (sdata->local->hw.flags & IEEE80211_HW_CONNECTION_MONITOR)
		return;

	mod_timer(&sdata->u.mgd.bcn_mon_timer,
		  round_jiffies_up(jiffies + sdata->u.mgd.beacon_timeout));
}