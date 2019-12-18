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
struct wireless_dev {struct wireless_dev* netdev; } ;
struct sk_buff {int dummy; } ;
struct genl_ops {int internal_flags; } ;
struct genl_info {struct wireless_dev** user_ptr; } ;

/* Variables and functions */
 int NL80211_FLAG_NEED_RTNL ; 
 int NL80211_FLAG_NEED_WDEV ; 
 int /*<<< orphan*/  cfg80211_unlock_rdev (struct wireless_dev*) ; 
 int /*<<< orphan*/  dev_put (struct wireless_dev*) ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void nl80211_post_doit(struct genl_ops *ops, struct sk_buff *skb,
			      struct genl_info *info)
{
	if (info->user_ptr[0])
		cfg80211_unlock_rdev(info->user_ptr[0]);
	if (info->user_ptr[1]) {
		if (ops->internal_flags & NL80211_FLAG_NEED_WDEV) {
			struct wireless_dev *wdev = info->user_ptr[1];

			if (wdev->netdev)
				dev_put(wdev->netdev);
		} else {
			dev_put(info->user_ptr[1]);
		}
	}
	if (ops->internal_flags & NL80211_FLAG_NEED_RTNL)
		rtnl_unlock();
}