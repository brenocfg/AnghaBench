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
struct ieee80211_local {int /*<<< orphan*/  scan_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  mtx; int /*<<< orphan*/  scan_sdata; scalar_t__ scanning; int /*<<< orphan*/  scan_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_can_scan (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies_relative (int /*<<< orphan*/ ) ; 

void ieee80211_run_deferred_scan(struct ieee80211_local *local)
{
	lockdep_assert_held(&local->mtx);

	if (!local->scan_req || local->scanning)
		return;

	if (!ieee80211_can_scan(local,
				rcu_dereference_protected(
					local->scan_sdata,
					lockdep_is_held(&local->mtx))))
		return;

	ieee80211_queue_delayed_work(&local->hw, &local->scan_work,
				     round_jiffies_relative(0));
}