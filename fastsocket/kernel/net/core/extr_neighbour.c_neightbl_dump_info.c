#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct rtgenmsg {int rtgen_family; } ;
struct netlink_callback {int* args; TYPE_2__* nlh; int /*<<< orphan*/  skb; } ;
struct net {int dummy; } ;
struct TYPE_4__ {struct neigh_parms* next; } ;
struct neigh_table {int family; TYPE_1__ parms; struct neigh_table* next; } ;
struct neigh_parms {struct neigh_parms* next; } ;
struct TYPE_6__ {int /*<<< orphan*/  pid; } ;
struct TYPE_5__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 TYPE_3__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  RTM_NEWNEIGHTBL ; 
 int /*<<< orphan*/  neigh_parms_net (struct neigh_parms*) ; 
 struct neigh_table* neigh_tables ; 
 int /*<<< orphan*/  neigh_tbl_lock ; 
 scalar_t__ neightbl_fill_info (struct sk_buff*,struct neigh_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ neightbl_fill_param_info (struct sk_buff*,struct neigh_table*,struct neigh_parms*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,struct net*) ; 
 scalar_t__ nlmsg_data (TYPE_2__*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int neightbl_dump_info(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct net *net = sock_net(skb->sk);
	int family, tidx, nidx = 0;
	int tbl_skip = cb->args[0];
	int neigh_skip = cb->args[1];
	struct neigh_table *tbl;

	family = ((struct rtgenmsg *) nlmsg_data(cb->nlh))->rtgen_family;

	read_lock(&neigh_tbl_lock);
	for (tbl = neigh_tables, tidx = 0; tbl; tbl = tbl->next, tidx++) {
		struct neigh_parms *p;

		if (tidx < tbl_skip || (family && tbl->family != family))
			continue;

		if (neightbl_fill_info(skb, tbl, NETLINK_CB(cb->skb).pid,
				       cb->nlh->nlmsg_seq, RTM_NEWNEIGHTBL,
				       NLM_F_MULTI) <= 0)
			break;

		for (nidx = 0, p = tbl->parms.next; p; p = p->next) {
			if (!net_eq(neigh_parms_net(p), net))
				continue;

			if (nidx < neigh_skip)
				goto next;

			if (neightbl_fill_param_info(skb, tbl, p,
						     NETLINK_CB(cb->skb).pid,
						     cb->nlh->nlmsg_seq,
						     RTM_NEWNEIGHTBL,
						     NLM_F_MULTI) <= 0)
				goto out;
		next:
			nidx++;
		}

		neigh_skip = 0;
	}
out:
	read_unlock(&neigh_tbl_lock);
	cb->args[0] = tidx;
	cb->args[1] = nidx;

	return skb->len;
}