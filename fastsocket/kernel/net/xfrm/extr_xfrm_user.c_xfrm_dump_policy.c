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
struct xfrm_policy_walk {int dummy; } ;
struct xfrm_dump_info {int /*<<< orphan*/  nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; struct sk_buff* out_skb; int /*<<< orphan*/  in_skb; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct netlink_callback {int* args; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  XFRM_POLICY_TYPE_ANY ; 
 int /*<<< orphan*/  dump_one_policy ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_policy_walk (struct net*,struct xfrm_policy_walk*,int /*<<< orphan*/ ,struct xfrm_dump_info*) ; 
 int /*<<< orphan*/  xfrm_policy_walk_init (struct xfrm_policy_walk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xfrm_dump_policy(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	struct xfrm_policy_walk *walk = (struct xfrm_policy_walk *) &cb->args[1];
	struct xfrm_dump_info info;

	BUILD_BUG_ON(sizeof(struct xfrm_policy_walk) >
		     sizeof(cb->args) - sizeof(cb->args[0]));

	info.in_skb = cb->skb;
	info.out_skb = skb;
	info.nlmsg_seq = cb->nlh->nlmsg_seq;
	info.nlmsg_flags = NLM_F_MULTI;

	if (!cb->args[0]) {
		cb->args[0] = 1;
		xfrm_policy_walk_init(walk, XFRM_POLICY_TYPE_ANY);
	}

	(void) xfrm_policy_walk(net, walk, dump_one_policy, &info);

	return skb->len;
}