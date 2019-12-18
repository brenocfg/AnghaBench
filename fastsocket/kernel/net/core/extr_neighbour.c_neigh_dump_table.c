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
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct netlink_callback {int* args; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct net {int dummy; } ;
struct neighbour {int /*<<< orphan*/  dev; struct neighbour* next; } ;
struct neigh_table {int hash_mask; int /*<<< orphan*/  lock; struct neighbour** hash_buckets; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  RTM_NEWNEIGH ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 scalar_t__ neigh_fill_info (struct sk_buff*,struct neighbour*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int neigh_dump_table(struct neigh_table *tbl, struct sk_buff *skb,
			    struct netlink_callback *cb)
{
	struct net * net = sock_net(skb->sk);
	struct neighbour *n;
	int rc, h, s_h = cb->args[1];
	int idx, s_idx = idx = cb->args[2];

	read_lock_bh(&tbl->lock);
	for (h = 0; h <= tbl->hash_mask; h++) {
		if (h < s_h)
			continue;
		if (h > s_h)
			s_idx = 0;
		for (n = tbl->hash_buckets[h], idx = 0; n; n = n->next) {
			if (dev_net(n->dev) != net)
				continue;
			if (idx < s_idx)
				goto next;
			if (neigh_fill_info(skb, n, NETLINK_CB(cb->skb).pid,
					    cb->nlh->nlmsg_seq,
					    RTM_NEWNEIGH,
					    NLM_F_MULTI) <= 0) {
				read_unlock_bh(&tbl->lock);
				rc = -1;
				goto out;
			}
		next:
			idx++;
		}
	}
	read_unlock_bh(&tbl->lock);
	rc = skb->len;
out:
	cb->args[1] = h;
	cb->args[2] = idx;
	return rc;
}