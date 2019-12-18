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
typedef  int /*<<< orphan*/  u16 ;
struct tcamsg {scalar_t__ tca__pad2; scalar_t__ tca__pad1; int /*<<< orphan*/  tca_family; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int len; } ;
struct nlmsghdr {int nlmsg_len; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 struct tcamsg* NLMSG_DATA (struct nlmsghdr*) ; 
 struct nlmsghdr* NLMSG_NEW (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCA_ACT_TAB ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 scalar_t__ tcf_action_dump (struct sk_buff*,struct tc_action*,int,int) ; 

__attribute__((used)) static int
tca_get_fill(struct sk_buff *skb, struct tc_action *a, u32 pid, u32 seq,
	     u16 flags, int event, int bind, int ref)
{
	struct tcamsg *t;
	struct nlmsghdr *nlh;
	unsigned char *b = skb_tail_pointer(skb);
	struct nlattr *nest;

	nlh = NLMSG_NEW(skb, pid, seq, event, sizeof(*t), flags);

	t = NLMSG_DATA(nlh);
	t->tca_family = AF_UNSPEC;
	t->tca__pad1 = 0;
	t->tca__pad2 = 0;

	nest = nla_nest_start(skb, TCA_ACT_TAB);
	if (nest == NULL)
		goto nla_put_failure;

	if (tcf_action_dump(skb, a, bind, ref) < 0)
		goto nla_put_failure;

	nla_nest_end(skb, nest);

	nlh->nlmsg_len = skb_tail_pointer(skb) - b;
	return skb->len;

nla_put_failure:
nlmsg_failure:
	nlmsg_trim(skb, b);
	return -1;
}