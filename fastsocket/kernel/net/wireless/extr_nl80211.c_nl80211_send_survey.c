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
typedef  int /*<<< orphan*/  u32 ;
struct survey_info {int filled; int /*<<< orphan*/  channel_time_tx; int /*<<< orphan*/  channel_time_rx; int /*<<< orphan*/  channel_time_ext_busy; int /*<<< orphan*/  channel_time_busy; int /*<<< orphan*/  channel_time; int /*<<< orphan*/  noise; TYPE_1__* channel; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct TYPE_2__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NL80211_ATTR_IFINDEX ; 
 int /*<<< orphan*/  NL80211_ATTR_SURVEY_INFO ; 
 int /*<<< orphan*/  NL80211_CMD_NEW_SURVEY_RESULTS ; 
 int /*<<< orphan*/  NL80211_SURVEY_INFO_CHANNEL_TIME ; 
 int /*<<< orphan*/  NL80211_SURVEY_INFO_CHANNEL_TIME_BUSY ; 
 int /*<<< orphan*/  NL80211_SURVEY_INFO_CHANNEL_TIME_EXT_BUSY ; 
 int /*<<< orphan*/  NL80211_SURVEY_INFO_CHANNEL_TIME_RX ; 
 int /*<<< orphan*/  NL80211_SURVEY_INFO_CHANNEL_TIME_TX ; 
 int /*<<< orphan*/  NL80211_SURVEY_INFO_FREQUENCY ; 
 int /*<<< orphan*/  NL80211_SURVEY_INFO_IN_USE ; 
 int /*<<< orphan*/  NL80211_SURVEY_INFO_NOISE ; 
 int SURVEY_INFO_CHANNEL_TIME ; 
 int SURVEY_INFO_CHANNEL_TIME_BUSY ; 
 int SURVEY_INFO_CHANNEL_TIME_EXT_BUSY ; 
 int SURVEY_INFO_CHANNEL_TIME_RX ; 
 int SURVEY_INFO_CHANNEL_TIME_TX ; 
 int SURVEY_INFO_IN_USE ; 
 int SURVEY_INFO_NOISE_DBM ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int genlmsg_end (struct sk_buff*,void*) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_send_survey(struct sk_buff *msg, u32 portid, u32 seq,
				int flags, struct net_device *dev,
				struct survey_info *survey)
{
	void *hdr;
	struct nlattr *infoattr;

	hdr = nl80211hdr_put(msg, portid, seq, flags,
			     NL80211_CMD_NEW_SURVEY_RESULTS);
	if (!hdr)
		return -ENOMEM;

	if (nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->ifindex))
		goto nla_put_failure;

	infoattr = nla_nest_start(msg, NL80211_ATTR_SURVEY_INFO);
	if (!infoattr)
		goto nla_put_failure;

	if (nla_put_u32(msg, NL80211_SURVEY_INFO_FREQUENCY,
			survey->channel->center_freq))
		goto nla_put_failure;

	if ((survey->filled & SURVEY_INFO_NOISE_DBM) &&
	    nla_put_u8(msg, NL80211_SURVEY_INFO_NOISE, survey->noise))
		goto nla_put_failure;
	if ((survey->filled & SURVEY_INFO_IN_USE) &&
	    nla_put_flag(msg, NL80211_SURVEY_INFO_IN_USE))
		goto nla_put_failure;
	if ((survey->filled & SURVEY_INFO_CHANNEL_TIME) &&
	    nla_put_u64(msg, NL80211_SURVEY_INFO_CHANNEL_TIME,
			survey->channel_time))
		goto nla_put_failure;
	if ((survey->filled & SURVEY_INFO_CHANNEL_TIME_BUSY) &&
	    nla_put_u64(msg, NL80211_SURVEY_INFO_CHANNEL_TIME_BUSY,
			survey->channel_time_busy))
		goto nla_put_failure;
	if ((survey->filled & SURVEY_INFO_CHANNEL_TIME_EXT_BUSY) &&
	    nla_put_u64(msg, NL80211_SURVEY_INFO_CHANNEL_TIME_EXT_BUSY,
			survey->channel_time_ext_busy))
		goto nla_put_failure;
	if ((survey->filled & SURVEY_INFO_CHANNEL_TIME_RX) &&
	    nla_put_u64(msg, NL80211_SURVEY_INFO_CHANNEL_TIME_RX,
			survey->channel_time_rx))
		goto nla_put_failure;
	if ((survey->filled & SURVEY_INFO_CHANNEL_TIME_TX) &&
	    nla_put_u64(msg, NL80211_SURVEY_INFO_CHANNEL_TIME_TX,
			survey->channel_time_tx))
		goto nla_put_failure;

	nla_nest_end(msg, infoattr);

	return genlmsg_end(msg, hdr);

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}