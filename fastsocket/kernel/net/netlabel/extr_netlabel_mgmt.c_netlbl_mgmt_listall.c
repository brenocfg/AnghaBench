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
typedef  void* u32 ;
struct sk_buff {int len; } ;
struct netlink_callback {void** args; TYPE_1__* nlh; } ;
struct netlbl_domhsh_walk_arg {int /*<<< orphan*/  seq; struct sk_buff* skb; struct netlink_callback* nl_cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  netlbl_domhsh_walk (void**,void**,int /*<<< orphan*/ ,struct netlbl_domhsh_walk_arg*) ; 
 int /*<<< orphan*/  netlbl_mgmt_listall_cb ; 

__attribute__((used)) static int netlbl_mgmt_listall(struct sk_buff *skb,
			       struct netlink_callback *cb)
{
	struct netlbl_domhsh_walk_arg cb_arg;
	u32 skip_bkt = cb->args[0];
	u32 skip_chain = cb->args[1];

	cb_arg.nl_cb = cb;
	cb_arg.skb = skb;
	cb_arg.seq = cb->nlh->nlmsg_seq;

	netlbl_domhsh_walk(&skip_bkt,
			   &skip_chain,
			   netlbl_mgmt_listall_cb,
			   &cb_arg);

	cb->args[0] = skip_bkt;
	cb->args[1] = skip_chain;
	return skb->len;
}