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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* tdls_mgmt ) (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_rdev_tdls_mgmt (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static inline int rdev_tdls_mgmt(struct cfg80211_registered_device *rdev,
				 struct net_device *dev, u8 *peer,
				 u8 action_code, u8 dialog_token,
				 u16 status_code, const u8 *buf, size_t len)
{
	int ret;
	trace_rdev_tdls_mgmt(&rdev->wiphy, dev, peer, action_code,
			     dialog_token, status_code, buf, len);
	ret = rdev->ops->tdls_mgmt(&rdev->wiphy, dev, peer, action_code,
				   dialog_token, status_code, buf, len);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}