#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int flags; unsigned int max_remain_on_channel_duration; } ;
struct wireless_dev {int iftype; TYPE_2__ wiphy; TYPE_1__* ops; } ;
struct sk_buff {int dummy; } ;
struct genl_info {int* attrs; int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_pid; struct wireless_dev** user_ptr; } ;
struct cfg80211_registered_device {int iftype; TYPE_2__ wiphy; TYPE_1__* ops; } ;
struct cfg80211_chan_def {int /*<<< orphan*/  chan; } ;
struct TYPE_3__ {int /*<<< orphan*/  mgmt_tx; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  NL80211_ATTR_COOKIE ; 
 size_t NL80211_ATTR_DONT_WAIT_FOR_ACK ; 
 size_t NL80211_ATTR_DURATION ; 
 size_t NL80211_ATTR_FRAME ; 
 size_t NL80211_ATTR_OFFCHANNEL_TX_OK ; 
 size_t NL80211_ATTR_TX_NO_CCK_RATE ; 
 int /*<<< orphan*/  NL80211_CMD_FRAME ; 
#define  NL80211_IFTYPE_ADHOC 135 
#define  NL80211_IFTYPE_AP 134 
#define  NL80211_IFTYPE_AP_VLAN 133 
#define  NL80211_IFTYPE_MESH_POINT 132 
#define  NL80211_IFTYPE_P2P_CLIENT 131 
#define  NL80211_IFTYPE_P2P_DEVICE 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 unsigned int NL80211_MIN_REMAIN_ON_CHANNEL_TIME ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int PTR_ERR (void*) ; 
 int WIPHY_FLAG_OFFCHAN_TX ; 
 int cfg80211_mlme_mgmt_tx (struct wireless_dev*,struct wireless_dev*,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int nl80211_parse_chandef (struct wireless_dev*,struct genl_info*,struct cfg80211_chan_def*) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (int) ; 
 int nla_get_flag (int) ; 
 unsigned int nla_get_u32 (int) ; 
 int /*<<< orphan*/  nla_len (int) ; 
 scalar_t__ nla_put_u64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_tx_mgmt(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct wireless_dev *wdev = info->user_ptr[1];
	struct cfg80211_chan_def chandef;
	int err;
	void *hdr = NULL;
	u64 cookie;
	struct sk_buff *msg = NULL;
	unsigned int wait = 0;
	bool offchan, no_cck, dont_wait_for_ack;

	dont_wait_for_ack = info->attrs[NL80211_ATTR_DONT_WAIT_FOR_ACK];

	if (!info->attrs[NL80211_ATTR_FRAME])
		return -EINVAL;

	if (!rdev->ops->mgmt_tx)
		return -EOPNOTSUPP;

	switch (wdev->iftype) {
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_P2P_CLIENT:
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_AP_VLAN:
	case NL80211_IFTYPE_MESH_POINT:
	case NL80211_IFTYPE_P2P_GO:
	case NL80211_IFTYPE_P2P_DEVICE:
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (info->attrs[NL80211_ATTR_DURATION]) {
		if (!(rdev->wiphy.flags & WIPHY_FLAG_OFFCHAN_TX))
			return -EINVAL;
		wait = nla_get_u32(info->attrs[NL80211_ATTR_DURATION]);

		/*
		 * We should wait on the channel for at least a minimum amount
		 * of time (10ms) but no longer than the driver supports.
		 */
		if (wait < NL80211_MIN_REMAIN_ON_CHANNEL_TIME ||
		    wait > rdev->wiphy.max_remain_on_channel_duration)
			return -EINVAL;

	}

	offchan = info->attrs[NL80211_ATTR_OFFCHANNEL_TX_OK];

	if (offchan && !(rdev->wiphy.flags & WIPHY_FLAG_OFFCHAN_TX))
		return -EINVAL;

	no_cck = nla_get_flag(info->attrs[NL80211_ATTR_TX_NO_CCK_RATE]);

	err = nl80211_parse_chandef(rdev, info, &chandef);
	if (err)
		return err;

	if (!dont_wait_for_ack) {
		msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
		if (!msg)
			return -ENOMEM;

		hdr = nl80211hdr_put(msg, info->snd_pid, info->snd_seq, 0,
				     NL80211_CMD_FRAME);

		if (IS_ERR(hdr)) {
			err = PTR_ERR(hdr);
			goto free_msg;
		}
	}

	err = cfg80211_mlme_mgmt_tx(rdev, wdev, chandef.chan, offchan, wait,
				    nla_data(info->attrs[NL80211_ATTR_FRAME]),
				    nla_len(info->attrs[NL80211_ATTR_FRAME]),
				    no_cck, dont_wait_for_ack, &cookie);
	if (err)
		goto free_msg;

	if (msg) {
		if (nla_put_u64(msg, NL80211_ATTR_COOKIE, cookie))
			goto nla_put_failure;

		genlmsg_end(msg, hdr);
		return genlmsg_reply(msg, info);
	}

	return 0;

 nla_put_failure:
	err = -ENOBUFS;
 free_msg:
	nlmsg_free(msg);
	return err;
}