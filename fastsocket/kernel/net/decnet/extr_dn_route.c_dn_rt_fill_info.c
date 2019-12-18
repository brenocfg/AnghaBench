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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int len; } ;
struct rtmsg {int rtm_dst_len; int rtm_src_len; int rtm_flags; int /*<<< orphan*/  rtm_protocol; int /*<<< orphan*/  rtm_scope; int /*<<< orphan*/  rtm_type; int /*<<< orphan*/  rtm_table; scalar_t__ rtm_tos; int /*<<< orphan*/  rtm_family; } ;
struct nlmsghdr {int nlmsg_len; } ;
struct TYPE_7__ {scalar_t__ fld_src; scalar_t__ iif; } ;
struct TYPE_8__ {long expires; int /*<<< orphan*/  error; int /*<<< orphan*/  metrics; TYPE_1__* dev; } ;
struct TYPE_6__ {TYPE_4__ dst; } ;
struct dn_route {int rt_flags; scalar_t__ rt_daddr; scalar_t__ rt_local_src; scalar_t__ rt_gateway; TYPE_3__ fl; TYPE_2__ u; int /*<<< orphan*/  rt_type; } ;
struct TYPE_5__ {scalar_t__ ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_DECnet ; 
 struct rtmsg* NLMSG_DATA (struct nlmsghdr*) ; 
 struct nlmsghdr* NLMSG_NEW (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int) ; 
 int /*<<< orphan*/  RTA_DST ; 
 int /*<<< orphan*/  RTA_GATEWAY ; 
 int /*<<< orphan*/  RTA_IIF ; 
 int /*<<< orphan*/  RTA_OIF ; 
 int /*<<< orphan*/  RTA_PREFSRC ; 
 int /*<<< orphan*/  RTA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  RTA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTA_SRC ; 
 int /*<<< orphan*/  RTA_TABLE ; 
 int RTCF_NOTIFY ; 
 int RTM_F_CLONED ; 
 int RTM_F_NOTIFY ; 
 int /*<<< orphan*/  RTPROT_UNSPEC ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int /*<<< orphan*/  RT_TABLE_MAIN ; 
 long jiffies ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 scalar_t__ rtnetlink_put_metrics (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtnl_put_cacheinfo (struct sk_buff*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_dst (struct sk_buff*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static int dn_rt_fill_info(struct sk_buff *skb, u32 pid, u32 seq,
			   int event, int nowait, unsigned int flags)
{
	struct dn_route *rt = (struct dn_route *)skb_dst(skb);
	struct rtmsg *r;
	struct nlmsghdr *nlh;
	unsigned char *b = skb_tail_pointer(skb);
	long expires;

	nlh = NLMSG_NEW(skb, pid, seq, event, sizeof(*r), flags);
	r = NLMSG_DATA(nlh);
	r->rtm_family = AF_DECnet;
	r->rtm_dst_len = 16;
	r->rtm_src_len = 0;
	r->rtm_tos = 0;
	r->rtm_table = RT_TABLE_MAIN;
	RTA_PUT_U32(skb, RTA_TABLE, RT_TABLE_MAIN);
	r->rtm_type = rt->rt_type;
	r->rtm_flags = (rt->rt_flags & ~0xFFFF) | RTM_F_CLONED;
	r->rtm_scope = RT_SCOPE_UNIVERSE;
	r->rtm_protocol = RTPROT_UNSPEC;
	if (rt->rt_flags & RTCF_NOTIFY)
		r->rtm_flags |= RTM_F_NOTIFY;
	RTA_PUT(skb, RTA_DST, 2, &rt->rt_daddr);
	if (rt->fl.fld_src) {
		r->rtm_src_len = 16;
		RTA_PUT(skb, RTA_SRC, 2, &rt->fl.fld_src);
	}
	if (rt->u.dst.dev)
		RTA_PUT(skb, RTA_OIF, sizeof(int), &rt->u.dst.dev->ifindex);
	/*
	 * Note to self - change this if input routes reverse direction when
	 * they deal only with inputs and not with replies like they do
	 * currently.
	 */
	RTA_PUT(skb, RTA_PREFSRC, 2, &rt->rt_local_src);
	if (rt->rt_daddr != rt->rt_gateway)
		RTA_PUT(skb, RTA_GATEWAY, 2, &rt->rt_gateway);
	if (rtnetlink_put_metrics(skb, rt->u.dst.metrics) < 0)
		goto rtattr_failure;
	expires = rt->u.dst.expires ? rt->u.dst.expires - jiffies : 0;
	if (rtnl_put_cacheinfo(skb, &rt->u.dst, 0, 0, 0, expires,
			       rt->u.dst.error) < 0)
		goto rtattr_failure;
	if (rt->fl.iif)
		RTA_PUT(skb, RTA_IIF, sizeof(int), &rt->fl.iif);

	nlh->nlmsg_len = skb_tail_pointer(skb) - b;
	return skb->len;

nlmsg_failure:
rtattr_failure:
	nlmsg_trim(skb, b);
	return -1;
}