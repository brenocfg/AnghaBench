#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wireless_dev {int /*<<< orphan*/  netdev; } ;
struct survey_info {TYPE_2__* channel; } ;
struct sk_buff {int len; } ;
struct netlink_callback {int* args; TYPE_3__* nlh; int /*<<< orphan*/  skb; } ;
struct ieee80211_channel {int flags; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  pid; } ;
struct TYPE_7__ {int /*<<< orphan*/  nlmsg_seq; } ;
struct TYPE_6__ {int /*<<< orphan*/  center_freq; } ;
struct TYPE_5__ {int /*<<< orphan*/  dump_survey; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int IEEE80211_CHAN_DISABLED ; 
 TYPE_4__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 struct ieee80211_channel* ieee80211_get_channel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl80211_finish_wdev_dump (struct cfg80211_registered_device*) ; 
 int nl80211_prepare_wdev_dump (struct sk_buff*,struct netlink_callback*,struct cfg80211_registered_device**,struct wireless_dev**) ; 
 scalar_t__ nl80211_send_survey (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct survey_info*) ; 
 int rdev_dump_survey (struct cfg80211_registered_device*,int /*<<< orphan*/ ,int,struct survey_info*) ; 

__attribute__((used)) static int nl80211_dump_survey(struct sk_buff *skb,
			struct netlink_callback *cb)
{
	struct survey_info survey;
	struct cfg80211_registered_device *dev;
	struct wireless_dev *wdev;
	int survey_idx = cb->args[2];
	int res;

	res = nl80211_prepare_wdev_dump(skb, cb, &dev, &wdev);
	if (res)
		return res;

	if (!wdev->netdev) {
		res = -EINVAL;
		goto out_err;
	}

	if (!dev->ops->dump_survey) {
		res = -EOPNOTSUPP;
		goto out_err;
	}

	while (1) {
		struct ieee80211_channel *chan;

		res = rdev_dump_survey(dev, wdev->netdev, survey_idx, &survey);
		if (res == -ENOENT)
			break;
		if (res)
			goto out_err;

		/* Survey without a channel doesn't make sense */
		if (!survey.channel) {
			res = -EINVAL;
			goto out;
		}

		chan = ieee80211_get_channel(&dev->wiphy,
					     survey.channel->center_freq);
		if (!chan || chan->flags & IEEE80211_CHAN_DISABLED) {
			survey_idx++;
			continue;
		}

		if (nl80211_send_survey(skb,
				NETLINK_CB(cb->skb).pid,
				cb->nlh->nlmsg_seq, NLM_F_MULTI,
				wdev->netdev, &survey) < 0)
			goto out;
		survey_idx++;
	}

 out:
	cb->args[2] = survey_idx;
	res = skb->len;
 out_err:
	nl80211_finish_wdev_dump(dev);
	return res;
}