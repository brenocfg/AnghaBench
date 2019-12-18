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
struct sk_buff {int dummy; } ;
struct net_device {TYPE_1__* ops; } ;
struct genl_info {int /*<<< orphan*/ * attrs; struct net_device** user_ptr; } ;
struct cfg80211_update_ft_ies_params {int /*<<< orphan*/  ie_len; int /*<<< orphan*/  ie; int /*<<< orphan*/  md; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  ft_params ;
struct TYPE_2__ {int /*<<< orphan*/  update_ft_ies; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_IE ; 
 size_t NL80211_ATTR_MDID ; 
 int /*<<< orphan*/  is_valid_ie_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cfg80211_update_ft_ies_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_len (int /*<<< orphan*/ ) ; 
 int rdev_update_ft_ies (struct net_device*,struct net_device*,struct cfg80211_update_ft_ies_params*) ; 

__attribute__((used)) static int nl80211_update_ft_ies(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct cfg80211_update_ft_ies_params ft_params;
	struct net_device *dev = info->user_ptr[1];

	if (!rdev->ops->update_ft_ies)
		return -EOPNOTSUPP;

	if (!info->attrs[NL80211_ATTR_MDID] ||
	    !is_valid_ie_attr(info->attrs[NL80211_ATTR_IE]))
		return -EINVAL;

	memset(&ft_params, 0, sizeof(ft_params));
	ft_params.md = nla_get_u16(info->attrs[NL80211_ATTR_MDID]);
	ft_params.ie = nla_data(info->attrs[NL80211_ATTR_IE]);
	ft_params.ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);

	return rdev_update_ft_ies(rdev, dev, &ft_params);
}