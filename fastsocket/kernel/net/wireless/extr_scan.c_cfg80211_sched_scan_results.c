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
struct wiphy {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sched_scan_results_wk; scalar_t__ sched_scan_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_cfg80211_sched_scan_results (struct wiphy*) ; 
 TYPE_1__* wiphy_to_dev (struct wiphy*) ; 

void cfg80211_sched_scan_results(struct wiphy *wiphy)
{
	trace_cfg80211_sched_scan_results(wiphy);
	/* ignore if we're not scanning */
	if (wiphy_to_dev(wiphy)->sched_scan_req)
		queue_work(cfg80211_wq,
			   &wiphy_to_dev(wiphy)->sched_scan_results_wk);
}