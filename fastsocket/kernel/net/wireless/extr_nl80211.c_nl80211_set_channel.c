#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  ieee80211_ptr; } ;
struct genl_info {struct net_device** user_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  ieee80211_ptr; } ;

/* Variables and functions */
 int __nl80211_set_channel (struct net_device*,int /*<<< orphan*/ ,struct genl_info*) ; 

__attribute__((used)) static int nl80211_set_channel(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *netdev = info->user_ptr[1];

	return __nl80211_set_channel(rdev, netdev->ieee80211_ptr, info);
}