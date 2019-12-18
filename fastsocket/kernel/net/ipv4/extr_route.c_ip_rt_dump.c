#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  rt_next; } ;
struct TYPE_6__ {TYPE_4__ dst; } ;
struct rtable {TYPE_1__ u; } ;
struct netlink_callback {int* args; TYPE_2__* nlh; int /*<<< orphan*/  skb; } ;
struct net {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  pid; } ;
struct TYPE_8__ {int /*<<< orphan*/  chain; } ;
struct TYPE_7__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 TYPE_5__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  RTM_NEWROUTE ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_clone (TYPE_4__*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,struct net*) ; 
 struct rtable* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 scalar_t__ rt_fill_info (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rt_hash_mask ; 
 TYPE_3__* rt_hash_table ; 
 scalar_t__ rt_is_expired (struct rtable*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

int ip_rt_dump(struct sk_buff *skb,  struct netlink_callback *cb)
{
	struct rtable *rt;
	int h, s_h;
	int idx, s_idx;
	struct net *net;

	net = sock_net(skb->sk);

	s_h = cb->args[0];
	if (s_h < 0)
		s_h = 0;
	s_idx = idx = cb->args[1];
	for (h = s_h; h <= rt_hash_mask; h++, s_idx = 0) {
		if (!rt_hash_table[h].chain)
			continue;
		rcu_read_lock_bh();
		for (rt = rcu_dereference(rt_hash_table[h].chain), idx = 0; rt;
		     rt = rcu_dereference(rt->u.dst.rt_next), idx++) {
			if (!net_eq(dev_net(rt->u.dst.dev), net) || idx < s_idx)
				continue;
			if (rt_is_expired(rt))
				continue;
			skb_dst_set(skb, dst_clone(&rt->u.dst));
			if (rt_fill_info(net, skb, NETLINK_CB(cb->skb).pid,
					 cb->nlh->nlmsg_seq, RTM_NEWROUTE,
					 1, NLM_F_MULTI) <= 0) {
				skb_dst_drop(skb);
				rcu_read_unlock_bh();
				goto done;
			}
			skb_dst_drop(skb);
		}
		rcu_read_unlock_bh();
	}

done:
	cb->args[0] = h;
	cb->args[1] = idx;
	return skb->len;
}