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
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct fib_rule_hdr {int /*<<< orphan*/  tos; scalar_t__ dst_len; scalar_t__ src_len; } ;
struct fib_rule {scalar_t__ action; int /*<<< orphan*/  table; } ;
struct TYPE_4__ {scalar_t__ plen; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {scalar_t__ plen; int /*<<< orphan*/  addr; } ;
struct fib6_rule {int /*<<< orphan*/  tclass; TYPE_2__ dst; TYPE_1__ src; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 size_t FRA_DST ; 
 size_t FRA_SRC ; 
 scalar_t__ FR_ACT_TO_TBL ; 
 int /*<<< orphan*/  RT6_TABLE_UNSPEC ; 
 int /*<<< orphan*/ * fib6_new_table (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_memcpy (int /*<<< orphan*/ *,struct nlattr*,int) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fib6_rule_configure(struct fib_rule *rule, struct sk_buff *skb,
			       struct fib_rule_hdr *frh,
			       struct nlattr **tb)
{
	int err = -EINVAL;
	struct net *net = sock_net(skb->sk);
	struct fib6_rule *rule6 = (struct fib6_rule *) rule;

	if (rule->action == FR_ACT_TO_TBL) {
		if (rule->table == RT6_TABLE_UNSPEC)
			goto errout;

		if (fib6_new_table(net, rule->table) == NULL) {
			err = -ENOBUFS;
			goto errout;
		}
	}

	if (frh->src_len)
		nla_memcpy(&rule6->src.addr, tb[FRA_SRC],
			   sizeof(struct in6_addr));

	if (frh->dst_len)
		nla_memcpy(&rule6->dst.addr, tb[FRA_DST],
			   sizeof(struct in6_addr));

	rule6->src.plen = frh->src_len;
	rule6->dst.plen = frh->dst_len;
	rule6->tclass = frh->tos;

	err = 0;
errout:
	return err;
}