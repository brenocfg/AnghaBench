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
struct regulatory_request {char* alpha2; scalar_t__ wiphy_idx; scalar_t__ intersect; int /*<<< orphan*/  initiator; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_ATTR_REG_ALPHA2 ; 
 int /*<<< orphan*/  NL80211_ATTR_REG_INITIATOR ; 
 int /*<<< orphan*/  NL80211_ATTR_REG_TYPE ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  NL80211_CMD_REG_CHANGE ; 
 int /*<<< orphan*/  NL80211_REGDOM_TYPE_COUNTRY ; 
 int /*<<< orphan*/  NL80211_REGDOM_TYPE_CUSTOM_WORLD ; 
 int /*<<< orphan*/  NL80211_REGDOM_TYPE_INTERSECTION ; 
 int /*<<< orphan*/  NL80211_REGDOM_TYPE_WORLD ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 scalar_t__ WIPHY_IDX_INVALID ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_multicast_allns (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ nl80211_regulatory_mcgrp ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void nl80211_send_reg_change_event(struct regulatory_request *request)
{
	struct sk_buff *msg;
	void *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_REG_CHANGE);
	if (!hdr) {
		nlmsg_free(msg);
		return;
	}

	/* Userspace can always count this one always being set */
	if (nla_put_u8(msg, NL80211_ATTR_REG_INITIATOR, request->initiator))
		goto nla_put_failure;

	if (request->alpha2[0] == '0' && request->alpha2[1] == '0') {
		if (nla_put_u8(msg, NL80211_ATTR_REG_TYPE,
			       NL80211_REGDOM_TYPE_WORLD))
			goto nla_put_failure;
	} else if (request->alpha2[0] == '9' && request->alpha2[1] == '9') {
		if (nla_put_u8(msg, NL80211_ATTR_REG_TYPE,
			       NL80211_REGDOM_TYPE_CUSTOM_WORLD))
			goto nla_put_failure;
	} else if ((request->alpha2[0] == '9' && request->alpha2[1] == '8') ||
		   request->intersect) {
		if (nla_put_u8(msg, NL80211_ATTR_REG_TYPE,
			       NL80211_REGDOM_TYPE_INTERSECTION))
			goto nla_put_failure;
	} else {
		if (nla_put_u8(msg, NL80211_ATTR_REG_TYPE,
			       NL80211_REGDOM_TYPE_COUNTRY) ||
		    nla_put_string(msg, NL80211_ATTR_REG_ALPHA2,
				   request->alpha2))
			goto nla_put_failure;
	}

	if (request->wiphy_idx != WIPHY_IDX_INVALID &&
	    nla_put_u32(msg, NL80211_ATTR_WIPHY, request->wiphy_idx))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);

	rcu_read_lock();
	genlmsg_multicast_allns(msg, 0, nl80211_regulatory_mcgrp.id,
				GFP_ATOMIC);
	rcu_read_unlock();

	return;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	nlmsg_free(msg);
}