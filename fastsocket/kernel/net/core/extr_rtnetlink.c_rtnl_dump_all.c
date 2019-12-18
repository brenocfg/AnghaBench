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
struct sk_buff {int len; } ;
struct netlink_callback {int family; int /*<<< orphan*/ * args; TYPE_1__* nlh; } ;
struct TYPE_4__ {scalar_t__ (* dumpit ) (struct sk_buff*,struct netlink_callback*) ;} ;
struct TYPE_3__ {int nlmsg_type; } ;

/* Variables and functions */
 int PF_PACKET ; 
 int RTM_BASE ; 
 int RTNL_FAMILY_MAX ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__** rtnl_msg_handlers ; 
 scalar_t__ stub1 (struct sk_buff*,struct netlink_callback*) ; 

__attribute__((used)) static int rtnl_dump_all(struct sk_buff *skb, struct netlink_callback *cb)
{
	int idx;
	int s_idx = cb->family;

	if (s_idx == 0)
		s_idx = 1;
	for (idx = 1; idx <= RTNL_FAMILY_MAX; idx++) {
		int type = cb->nlh->nlmsg_type-RTM_BASE;
		if (idx < s_idx || idx == PF_PACKET)
			continue;
		if (rtnl_msg_handlers[idx] == NULL ||
		    rtnl_msg_handlers[idx][type].dumpit == NULL)
			continue;
		if (idx > s_idx)
			memset(&cb->args[0], 0, sizeof(cb->args));
		if (rtnl_msg_handlers[idx][type].dumpit(skb, cb))
			break;
	}
	cb->family = idx;

	return skb->len;
}