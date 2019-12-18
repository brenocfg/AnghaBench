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
typedef  void* u32 ;
struct sw_flow {int dummy; } ;
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct ovs_header {int /*<<< orphan*/  dp_ifindex; } ;
struct netlink_callback {void** args; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct flow_table {int dummy; } ;
struct datapath {int /*<<< orphan*/  table; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  OVS_FLOW_CMD_NEW ; 
 struct ovs_header* genlmsg_data (int /*<<< orphan*/ ) ; 
 struct datapath* get_dp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_data (TYPE_1__*) ; 
 scalar_t__ ovs_flow_cmd_fill_info (struct sw_flow*,struct datapath*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sw_flow* ovs_flow_tbl_next (struct flow_table*,void**,void**) ; 
 int /*<<< orphan*/  ovs_lock () ; 
 int /*<<< orphan*/  ovs_unlock () ; 
 struct flow_table* ovsl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovs_flow_cmd_dump(struct sk_buff *skb, struct netlink_callback *cb)
{
	struct ovs_header *ovs_header = genlmsg_data(nlmsg_data(cb->nlh));
	struct datapath *dp;
	struct flow_table *table;

	ovs_lock();
	dp = get_dp(sock_net(skb->sk), ovs_header->dp_ifindex);
	if (!dp) {
		ovs_unlock();
		return -ENODEV;
	}

	table = ovsl_dereference(dp->table);

	for (;;) {
		struct sw_flow *flow;
		u32 bucket, obj;

		bucket = cb->args[0];
		obj = cb->args[1];
		flow = ovs_flow_tbl_next(table, &bucket, &obj);
		if (!flow)
			break;

		if (ovs_flow_cmd_fill_info(flow, dp, skb,
					   NETLINK_CB(cb->skb).pid,
					   cb->nlh->nlmsg_seq, NLM_F_MULTI,
					   OVS_FLOW_CMD_NEW) < 0)
			break;

		cb->args[0] = bucket;
		cb->args[1] = obj;
	}
	ovs_unlock();
	return skb->len;
}