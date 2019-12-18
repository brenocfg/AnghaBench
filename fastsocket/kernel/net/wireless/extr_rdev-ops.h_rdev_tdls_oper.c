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
typedef  enum nl80211_tdls_operation { ____Placeholder_nl80211_tdls_operation } nl80211_tdls_operation ;
struct TYPE_2__ {int (* tdls_oper ) (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_rdev_tdls_oper (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int rdev_tdls_oper(struct cfg80211_registered_device *rdev,
				 struct net_device *dev, u8 *peer,
				 enum nl80211_tdls_operation oper)
{
	int ret;
	trace_rdev_tdls_oper(&rdev->wiphy, dev, peer, oper);
	ret = rdev->ops->tdls_oper(&rdev->wiphy, dev, peer, oper);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}