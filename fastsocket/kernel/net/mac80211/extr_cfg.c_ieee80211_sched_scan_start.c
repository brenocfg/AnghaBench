#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct ieee80211_sub_if_data {TYPE_2__* local; } ;
struct cfg80211_sched_scan_request {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  sched_scan_start; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int ieee80211_request_sched_scan_start (struct ieee80211_sub_if_data*,struct cfg80211_sched_scan_request*) ; 

__attribute__((used)) static int
ieee80211_sched_scan_start(struct wiphy *wiphy,
			   struct net_device *dev,
			   struct cfg80211_sched_scan_request *req)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	if (!sdata->local->ops->sched_scan_start)
		return -EOPNOTSUPP;

	return ieee80211_request_sched_scan_start(sdata, req);
}