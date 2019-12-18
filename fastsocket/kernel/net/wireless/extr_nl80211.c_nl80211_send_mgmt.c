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
struct wireless_dev {struct net_device* netdev; } ;
struct sk_buff {int dummy; } ;
struct net_device {int ifindex; } ;
struct cfg80211_registered_device {int wiphy_idx; int /*<<< orphan*/  wiphy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NL80211_ATTR_FRAME ; 
 int /*<<< orphan*/  NL80211_ATTR_IFINDEX ; 
 int /*<<< orphan*/  NL80211_ATTR_RX_SIGNAL_DBM ; 
 int /*<<< orphan*/  NL80211_ATTR_WDEV ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY_FREQ ; 
 int /*<<< orphan*/  NL80211_CMD_FRAME ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int genlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_put_u64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdev_id (struct wireless_dev*) ; 
 int /*<<< orphan*/  wiphy_net (int /*<<< orphan*/ *) ; 

int nl80211_send_mgmt(struct cfg80211_registered_device *rdev,
		      struct wireless_dev *wdev, u32 nlportid,
		      int freq, int sig_dbm,
		      const u8 *buf, size_t len, gfp_t gfp)
{
	struct net_device *netdev = wdev->netdev;
	struct sk_buff *msg;
	void *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	if (!msg)
		return -ENOMEM;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_FRAME);
	if (!hdr) {
		nlmsg_free(msg);
		return -ENOMEM;
	}

	if (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    (netdev && nla_put_u32(msg, NL80211_ATTR_IFINDEX,
					netdev->ifindex)) ||
	    nla_put_u64(msg, NL80211_ATTR_WDEV, wdev_id(wdev)) ||
	    nla_put_u32(msg, NL80211_ATTR_WIPHY_FREQ, freq) ||
	    (sig_dbm &&
	     nla_put_u32(msg, NL80211_ATTR_RX_SIGNAL_DBM, sig_dbm)) ||
	    nla_put(msg, NL80211_ATTR_FRAME, len, buf))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);

	return genlmsg_unicast(wiphy_net(&rdev->wiphy), msg, nlportid);

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	nlmsg_free(msg);
	return -ENOBUFS;
}