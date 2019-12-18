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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct rtmsg {int rtm_dst_len; int rtm_src_len; scalar_t__ rtm_flags; int /*<<< orphan*/  rtm_protocol; int /*<<< orphan*/  rtm_scope; int /*<<< orphan*/  rtm_type; int /*<<< orphan*/  rtm_table; scalar_t__ rtm_tos; int /*<<< orphan*/  rtm_family; } ;
struct nlmsghdr {int dummy; } ;
struct mr_table {int /*<<< orphan*/  id; } ;
struct mfc_cache {int /*<<< orphan*/  mfc_mcastgrp; int /*<<< orphan*/  mfc_origin; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NLA_PUT_BE32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  RTA_DST ; 
 int /*<<< orphan*/  RTA_SRC ; 
 int /*<<< orphan*/  RTA_TABLE ; 
 int /*<<< orphan*/  RTM_NEWROUTE ; 
 int /*<<< orphan*/  RTNL_FAMILY_IPMR ; 
 int /*<<< orphan*/  RTN_MULTICAST ; 
 int /*<<< orphan*/  RTPROT_UNSPEC ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 scalar_t__ __ipmr_fill_mroute (struct mr_table*,struct sk_buff*,struct mfc_cache*,struct rtmsg*) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct rtmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipmr_fill_mroute(struct mr_table *mrt, struct sk_buff *skb,
			    u32 pid, u32 seq, struct mfc_cache *c)
{
	struct nlmsghdr *nlh;
	struct rtmsg *rtm;

	nlh = nlmsg_put(skb, pid, seq, RTM_NEWROUTE, sizeof(*rtm), NLM_F_MULTI);
	if (nlh == NULL)
		return -EMSGSIZE;

	rtm = nlmsg_data(nlh);
	rtm->rtm_family   = RTNL_FAMILY_IPMR;
	rtm->rtm_dst_len  = 32;
	rtm->rtm_src_len  = 32;
	rtm->rtm_tos      = 0;
	rtm->rtm_table    = mrt->id;
	NLA_PUT_U32(skb, RTA_TABLE, mrt->id);
	rtm->rtm_type     = RTN_MULTICAST;
	rtm->rtm_scope    = RT_SCOPE_UNIVERSE;
	rtm->rtm_protocol = RTPROT_UNSPEC;
	rtm->rtm_flags    = 0;

	NLA_PUT_BE32(skb, RTA_SRC, c->mfc_origin);
	NLA_PUT_BE32(skb, RTA_DST, c->mfc_mcastgrp);

	if (__ipmr_fill_mroute(mrt, skb, c, rtm) < 0)
		goto nla_put_failure;

	return nlmsg_end(skb, nlh);

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}