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
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_wakeup ) (int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_rdev_return_void (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rdev_set_wakeup (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void rdev_set_wakeup(struct cfg80211_registered_device *rdev,
				   bool enabled)
{
	trace_rdev_set_wakeup(&rdev->wiphy, enabled);
	rdev->ops->set_wakeup(&rdev->wiphy, enabled);
	trace_rdev_return_void(&rdev->wiphy);
}