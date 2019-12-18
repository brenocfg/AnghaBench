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
struct wiphy {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  sched_scan_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cfg80211_stop_sched_scan (struct cfg80211_registered_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_cfg80211_sched_scan_stopped (struct wiphy*) ; 
 struct cfg80211_registered_device* wiphy_to_dev (struct wiphy*) ; 

void cfg80211_sched_scan_stopped(struct wiphy *wiphy)
{
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wiphy);

	trace_cfg80211_sched_scan_stopped(wiphy);

	mutex_lock(&rdev->sched_scan_mtx);
	__cfg80211_stop_sched_scan(rdev, true);
	mutex_unlock(&rdev->sched_scan_mtx);
}