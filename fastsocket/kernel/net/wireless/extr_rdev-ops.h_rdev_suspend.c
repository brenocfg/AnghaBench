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
struct cfg80211_wowlan {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* suspend ) (int /*<<< orphan*/ *,struct cfg80211_wowlan*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct cfg80211_wowlan*) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_rdev_suspend (int /*<<< orphan*/ *,struct cfg80211_wowlan*) ; 

__attribute__((used)) static inline int rdev_suspend(struct cfg80211_registered_device *rdev,
			       struct cfg80211_wowlan *wowlan)
{
	int ret;
	trace_rdev_suspend(&rdev->wiphy, wowlan);
	ret = rdev->ops->suspend(&rdev->wiphy, wowlan);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}