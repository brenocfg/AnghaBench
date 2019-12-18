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
struct net {int dummy; } ;
struct in6_rtmsg {int /*<<< orphan*/  rtmsg_gateway; int /*<<< orphan*/  rtmsg_src; int /*<<< orphan*/  rtmsg_dst; int /*<<< orphan*/  rtmsg_flags; int /*<<< orphan*/  rtmsg_src_len; int /*<<< orphan*/  rtmsg_dst_len; int /*<<< orphan*/  rtmsg_info; int /*<<< orphan*/  rtmsg_metric; int /*<<< orphan*/  rtmsg_ifindex; } ;
struct TYPE_2__ {struct net* nl_net; } ;
struct fib6_config {int /*<<< orphan*/  fc_gateway; int /*<<< orphan*/  fc_src; int /*<<< orphan*/  fc_dst; TYPE_1__ fc_nlinfo; int /*<<< orphan*/  fc_flags; int /*<<< orphan*/  fc_src_len; int /*<<< orphan*/  fc_dst_len; int /*<<< orphan*/  fc_expires; int /*<<< orphan*/  fc_metric; int /*<<< orphan*/  fc_ifindex; int /*<<< orphan*/  fc_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT6_TABLE_MAIN ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct fib6_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtmsg_to_fib6_config(struct net *net,
				 struct in6_rtmsg *rtmsg,
				 struct fib6_config *cfg)
{
	memset(cfg, 0, sizeof(*cfg));

	cfg->fc_table = RT6_TABLE_MAIN;
	cfg->fc_ifindex = rtmsg->rtmsg_ifindex;
	cfg->fc_metric = rtmsg->rtmsg_metric;
	cfg->fc_expires = rtmsg->rtmsg_info;
	cfg->fc_dst_len = rtmsg->rtmsg_dst_len;
	cfg->fc_src_len = rtmsg->rtmsg_src_len;
	cfg->fc_flags = rtmsg->rtmsg_flags;

	cfg->fc_nlinfo.nl_net = net;

	ipv6_addr_copy(&cfg->fc_dst, &rtmsg->rtmsg_dst);
	ipv6_addr_copy(&cfg->fc_src, &rtmsg->rtmsg_src);
	ipv6_addr_copy(&cfg->fc_gateway, &rtmsg->rtmsg_gateway);
}