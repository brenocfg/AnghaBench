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
struct station_parameters {int dummy; } ;
struct net_device {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* change_station ) (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ *,struct station_parameters*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ *,struct station_parameters*) ; 
 int /*<<< orphan*/  trace_rdev_change_station (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ *,struct station_parameters*) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int rdev_change_station(struct cfg80211_registered_device *rdev,
				      struct net_device *dev, u8 *mac,
				      struct station_parameters *params)
{
	int ret;
	trace_rdev_change_station(&rdev->wiphy, dev, mac, params);
	ret = rdev->ops->change_station(&rdev->wiphy, dev, mac, params);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}