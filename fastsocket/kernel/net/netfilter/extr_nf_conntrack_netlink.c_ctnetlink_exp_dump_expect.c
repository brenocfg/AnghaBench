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
struct sk_buff {int dummy; } ;
struct TYPE_3__ {long expires; } ;
struct nf_conntrack_expect {int /*<<< orphan*/  mask; int /*<<< orphan*/  tuple; TYPE_1__ timeout; struct nf_conn* master; } ;
struct nf_conn {TYPE_2__* tuplehash; } ;
struct TYPE_4__ {int /*<<< orphan*/  tuple; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_EXPECT_ID ; 
 int /*<<< orphan*/  CTA_EXPECT_MASTER ; 
 int /*<<< orphan*/  CTA_EXPECT_TIMEOUT ; 
 int /*<<< orphan*/  CTA_EXPECT_TUPLE ; 
 long HZ ; 
 size_t IP_CT_DIR_ORIGINAL ; 
 int /*<<< orphan*/  NLA_PUT_BE32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ctnetlink_exp_dump_mask (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ctnetlink_exp_dump_tuple (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (unsigned long) ; 
 long jiffies ; 

__attribute__((used)) static int
ctnetlink_exp_dump_expect(struct sk_buff *skb,
			  const struct nf_conntrack_expect *exp)
{
	struct nf_conn *master = exp->master;
	long timeout = (exp->timeout.expires - jiffies) / HZ;

	if (timeout < 0)
		timeout = 0;

	if (ctnetlink_exp_dump_tuple(skb, &exp->tuple, CTA_EXPECT_TUPLE) < 0)
		goto nla_put_failure;
	if (ctnetlink_exp_dump_mask(skb, &exp->tuple, &exp->mask) < 0)
		goto nla_put_failure;
	if (ctnetlink_exp_dump_tuple(skb,
				 &master->tuplehash[IP_CT_DIR_ORIGINAL].tuple,
				 CTA_EXPECT_MASTER) < 0)
		goto nla_put_failure;

	NLA_PUT_BE32(skb, CTA_EXPECT_TIMEOUT, htonl(timeout));
	NLA_PUT_BE32(skb, CTA_EXPECT_ID, htonl((unsigned long)exp));

	return 0;

nla_put_failure:
	return -1;
}