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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wireless_dev {int /*<<< orphan*/  ap_unexpected_nlportid; int /*<<< orphan*/  wiphy; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; int /*<<< orphan*/  wiphy_idx; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NL80211_ATTR_IFINDEX ; 
 int /*<<< orphan*/  NL80211_ATTR_MAC ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_net (int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __nl80211_unexpected_frame(struct net_device *dev, u8 cmd,
				       const u8 *addr, gfp_t gfp)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_dev(wdev->wiphy);
	struct sk_buff *msg;
	void *hdr;
	int err;
	u32 nlportid = ACCESS_ONCE(wdev->ap_unexpected_nlportid);

	if (!nlportid)
		return false;

	msg = nlmsg_new(100, gfp);
	if (!msg)
		return true;

	hdr = nl80211hdr_put(msg, 0, 0, 0, cmd);
	if (!hdr) {
		nlmsg_free(msg);
		return true;
	}

	if (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->ifindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, addr))
		goto nla_put_failure;

	err = genlmsg_end(msg, hdr);
	if (err < 0) {
		nlmsg_free(msg);
		return true;
	}

	genlmsg_unicast(wiphy_net(&rdev->wiphy), msg, nlportid);
	return true;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	nlmsg_free(msg);
	return true;
}