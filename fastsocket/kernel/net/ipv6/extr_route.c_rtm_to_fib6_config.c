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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct rtmsg {int rtm_dst_len; int rtm_src_len; scalar_t__ rtm_type; int /*<<< orphan*/  rtm_protocol; void* rtm_table; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nl_net; struct nlmsghdr* nlh; int /*<<< orphan*/  pid; } ;
struct fib6_config {int fc_dst_len; int fc_src_len; int fc_mx_len; void* fc_table; int /*<<< orphan*/  fc_mx; void* fc_metric; void* fc_ifindex; int /*<<< orphan*/  fc_prefsrc; int /*<<< orphan*/  fc_src; int /*<<< orphan*/  fc_dst; int /*<<< orphan*/  fc_flags; int /*<<< orphan*/  fc_gateway; TYPE_1__ fc_nlinfo; int /*<<< orphan*/  fc_protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 size_t RTA_DST ; 
 size_t RTA_GATEWAY ; 
 int /*<<< orphan*/  RTA_MAX ; 
 size_t RTA_METRICS ; 
 size_t RTA_OIF ; 
 size_t RTA_PREFSRC ; 
 size_t RTA_PRIORITY ; 
 size_t RTA_SRC ; 
 size_t RTA_TABLE ; 
 int /*<<< orphan*/  RTF_GATEWAY ; 
 int /*<<< orphan*/  RTF_LOCAL ; 
 int /*<<< orphan*/  RTF_REJECT ; 
 int /*<<< orphan*/  RTF_UP ; 
 scalar_t__ RTN_LOCAL ; 
 scalar_t__ RTN_UNREACHABLE ; 
 int /*<<< orphan*/  memset (struct fib6_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  nla_memcpy (int /*<<< orphan*/ *,struct nlattr*,int) ; 
 struct rtmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtm_ipv6_policy ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtm_to_fib6_config(struct sk_buff *skb, struct nlmsghdr *nlh,
			      struct fib6_config *cfg)
{
	struct rtmsg *rtm;
	struct nlattr *tb[RTA_MAX+1];
	int err;

	err = nlmsg_parse(nlh, sizeof(*rtm), tb, RTA_MAX, rtm_ipv6_policy);
	if (err < 0)
		goto errout;

	err = -EINVAL;
	rtm = nlmsg_data(nlh);
	memset(cfg, 0, sizeof(*cfg));

	cfg->fc_table = rtm->rtm_table;
	cfg->fc_dst_len = rtm->rtm_dst_len;
	cfg->fc_src_len = rtm->rtm_src_len;
	cfg->fc_flags = RTF_UP;
	cfg->fc_protocol = rtm->rtm_protocol;

	if (rtm->rtm_type == RTN_UNREACHABLE)
		cfg->fc_flags |= RTF_REJECT;

	if (rtm->rtm_type == RTN_LOCAL)
		cfg->fc_flags |= RTF_LOCAL;

	cfg->fc_nlinfo.pid = NETLINK_CB(skb).pid;
	cfg->fc_nlinfo.nlh = nlh;
	cfg->fc_nlinfo.nl_net = sock_net(skb->sk);

	if (tb[RTA_GATEWAY]) {
		nla_memcpy(&cfg->fc_gateway, tb[RTA_GATEWAY], 16);
		cfg->fc_flags |= RTF_GATEWAY;
	}

	if (tb[RTA_DST]) {
		int plen = (rtm->rtm_dst_len + 7) >> 3;

		if (nla_len(tb[RTA_DST]) < plen)
			goto errout;

		nla_memcpy(&cfg->fc_dst, tb[RTA_DST], plen);
	}

	if (tb[RTA_SRC]) {
		int plen = (rtm->rtm_src_len + 7) >> 3;

		if (nla_len(tb[RTA_SRC]) < plen)
			goto errout;

		nla_memcpy(&cfg->fc_src, tb[RTA_SRC], plen);
	}

	if (tb[RTA_PREFSRC])
		nla_memcpy(&cfg->fc_prefsrc, tb[RTA_PREFSRC], 16);

	if (tb[RTA_OIF])
		cfg->fc_ifindex = nla_get_u32(tb[RTA_OIF]);

	if (tb[RTA_PRIORITY])
		cfg->fc_metric = nla_get_u32(tb[RTA_PRIORITY]);

	if (tb[RTA_METRICS]) {
		cfg->fc_mx = nla_data(tb[RTA_METRICS]);
		cfg->fc_mx_len = nla_len(tb[RTA_METRICS]);
	}

	if (tb[RTA_TABLE])
		cfg->fc_table = nla_get_u32(tb[RTA_TABLE]);

	err = 0;
errout:
	return err;
}