#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ieee80211_local {int /*<<< orphan*/  sched_scan_stopped_work; int /*<<< orphan*/  hw; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_api_sched_scan_stopped (struct ieee80211_local*) ; 

void ieee80211_sched_scan_stopped(struct ieee80211_hw *hw)
{
	struct ieee80211_local *local = hw_to_local(hw);

	trace_api_sched_scan_stopped(local);

	ieee80211_queue_work(&local->hw, &local->sched_scan_stopped_work);
}