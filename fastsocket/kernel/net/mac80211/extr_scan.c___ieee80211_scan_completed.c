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
struct ieee80211_local {int /*<<< orphan*/ * scan_channel; scalar_t__ scanning; int /*<<< orphan*/  scan_sdata; int /*<<< orphan*/ * scan_req; int /*<<< orphan*/ * int_scan_req; int /*<<< orphan*/ * hw_scan_req; int /*<<< orphan*/  mtx; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cfg80211_scan_done (int /*<<< orphan*/ *,int) ; 
 int drv_hw_scan (struct ieee80211_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv_sw_scan_complete (struct ieee80211_local*) ; 
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_configure_filter (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_hw_config (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ibss_notify_scan_completed (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_mesh_notify_scan_completed (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_mlme_notify_scan_completed (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_offchannel_return (struct ieee80211_local*) ; 
 scalar_t__ ieee80211_prep_hw_scan (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_recalc_idle (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_start_next_roc (struct ieee80211_local*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ieee80211_scan_completed(struct ieee80211_hw *hw, bool aborted,
				       bool was_hw_scan)
{
	struct ieee80211_local *local = hw_to_local(hw);

	lockdep_assert_held(&local->mtx);

	/*
	 * It's ok to abort a not-yet-running scan (that
	 * we have one at all will be verified by checking
	 * local->scan_req next), but not to complete it
	 * successfully.
	 */
	if (WARN_ON(!local->scanning && !aborted))
		aborted = true;

	if (WARN_ON(!local->scan_req))
		return;

	if (was_hw_scan && !aborted && ieee80211_prep_hw_scan(local)) {
		int rc;

		rc = drv_hw_scan(local,
			rcu_dereference_protected(local->scan_sdata,
						  lockdep_is_held(&local->mtx)),
			local->hw_scan_req);

		if (rc == 0)
			return;
	}

	kfree(local->hw_scan_req);
	local->hw_scan_req = NULL;

	if (local->scan_req != local->int_scan_req)
		cfg80211_scan_done(local->scan_req, aborted);
	local->scan_req = NULL;
	rcu_assign_pointer(local->scan_sdata, NULL);

	local->scanning = 0;
	local->scan_channel = NULL;

	/* Set power back to normal operating levels. */
	ieee80211_hw_config(local, 0);

	if (!was_hw_scan) {
		ieee80211_configure_filter(local);
		drv_sw_scan_complete(local);
		ieee80211_offchannel_return(local);
	}

	ieee80211_recalc_idle(local);

	ieee80211_mlme_notify_scan_completed(local);
	ieee80211_ibss_notify_scan_completed(local);
	ieee80211_mesh_notify_scan_completed(local);
	ieee80211_start_next_roc(local);
}