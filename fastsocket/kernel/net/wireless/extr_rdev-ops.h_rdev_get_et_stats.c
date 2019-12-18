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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_et_stats ) (int /*<<< orphan*/ *,struct net_device*,struct ethtool_stats*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct net_device*,struct ethtool_stats*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rdev_get_et_stats (int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  trace_rdev_return_void (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rdev_get_et_stats(struct cfg80211_registered_device *rdev,
				     struct net_device *dev,
				     struct ethtool_stats *stats, u64 *data)
{
	trace_rdev_get_et_stats(&rdev->wiphy, dev);
	rdev->ops->get_et_stats(&rdev->wiphy, dev, stats, data);
	trace_rdev_return_void(&rdev->wiphy);
}