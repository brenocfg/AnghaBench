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
struct wireless_dev {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct cfg80211_chan_def {int dummy; } ;
struct TYPE_2__ {int (* get_channel ) (int /*<<< orphan*/ *,struct wireless_dev*,struct cfg80211_chan_def*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct wireless_dev*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  trace_rdev_get_channel (int /*<<< orphan*/ *,struct wireless_dev*) ; 
 int /*<<< orphan*/  trace_rdev_return_chandef (int /*<<< orphan*/ *,int,struct cfg80211_chan_def*) ; 

__attribute__((used)) static inline int
rdev_get_channel(struct cfg80211_registered_device *rdev,
		 struct wireless_dev *wdev,
		 struct cfg80211_chan_def *chandef)
{
	int ret;

	trace_rdev_get_channel(&rdev->wiphy, wdev);
	ret = rdev->ops->get_channel(&rdev->wiphy, wdev, chandef);
	trace_rdev_return_chandef(&rdev->wiphy, ret, chandef);

	return ret;
}