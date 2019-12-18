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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct cfg80211_bitrate_mask {int dummy; } ;
struct TYPE_2__ {int (* set_bitrate_mask ) (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/  const*,struct cfg80211_bitrate_mask const*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/  const*,struct cfg80211_bitrate_mask const*) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_rdev_set_bitrate_mask (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/  const*,struct cfg80211_bitrate_mask const*) ; 

__attribute__((used)) static inline int
rdev_set_bitrate_mask(struct cfg80211_registered_device *rdev,
		      struct net_device *dev, const u8 *peer,
		      const struct cfg80211_bitrate_mask *mask)
{
	int ret;
	trace_rdev_set_bitrate_mask(&rdev->wiphy, dev, peer, mask);
	ret = rdev->ops->set_bitrate_mask(&rdev->wiphy, dev, peer, mask);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}