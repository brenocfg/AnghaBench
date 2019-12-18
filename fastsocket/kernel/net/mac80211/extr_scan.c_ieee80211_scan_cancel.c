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
struct ieee80211_local {int /*<<< orphan*/  mtx; int /*<<< orphan*/  hw; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  scan_sdata; TYPE_1__* ops; int /*<<< orphan*/  scanning; int /*<<< orphan*/  scan_req; } ;
struct TYPE_2__ {scalar_t__ cancel_hw_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_HW_SCANNING ; 
 int /*<<< orphan*/  __ieee80211_scan_completed (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv_cancel_hw_scan (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ieee80211_scan_cancel(struct ieee80211_local *local)
{
	/*
	 * We are canceling software scan, or deferred scan that was not
	 * yet really started (see __ieee80211_start_scan ).
	 *
	 * Regarding hardware scan:
	 * - we can not call  __ieee80211_scan_completed() as when
	 *   SCAN_HW_SCANNING bit is set this function change
	 *   local->hw_scan_req to operate on 5G band, what race with
	 *   driver which can use local->hw_scan_req
	 *
	 * - we can not cancel scan_work since driver can schedule it
	 *   by ieee80211_scan_completed(..., true) to finish scan
	 *
	 * Hence we only call the cancel_hw_scan() callback, but the low-level
	 * driver is still responsible for calling ieee80211_scan_completed()
	 * after the scan was completed/aborted.
	 */

	mutex_lock(&local->mtx);
	if (!local->scan_req)
		goto out;

	if (test_bit(SCAN_HW_SCANNING, &local->scanning)) {
		if (local->ops->cancel_hw_scan)
			drv_cancel_hw_scan(local,
				rcu_dereference_protected(local->scan_sdata,
						lockdep_is_held(&local->mtx)));
		goto out;
	}

	/*
	 * If the work is currently running, it must be blocked on
	 * the mutex, but we'll set scan_sdata = NULL and it'll
	 * simply exit once it acquires the mutex.
	 */
	cancel_delayed_work(&local->scan_work);
	/* and clean up */
	__ieee80211_scan_completed(&local->hw, true, false);
out:
	mutex_unlock(&local->mtx);
}