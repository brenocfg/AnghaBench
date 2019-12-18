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
struct sw_flow_key {int dummy; } ;
struct sw_flow {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct ovs_header {int /*<<< orphan*/  dp_ifindex; } ;
struct nlattr {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_pid; struct ovs_header* userhdr; struct nlattr** attrs; } ;
struct flow_table {int dummy; } ;
struct datapath {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 size_t OVS_FLOW_ATTR_KEY ; 
 int /*<<< orphan*/  OVS_FLOW_CMD_NEW ; 
 int PTR_ERR (struct sk_buff*) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 struct datapath* get_dp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ovs_flow_cmd_build_info (struct sw_flow*,struct datapath*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ovs_flow_from_nlattrs (struct sw_flow_key*,int*,struct nlattr*) ; 
 struct sw_flow* ovs_flow_tbl_lookup (struct flow_table*,struct sw_flow_key*,int) ; 
 int /*<<< orphan*/  ovs_lock () ; 
 int /*<<< orphan*/  ovs_unlock () ; 
 struct flow_table* ovsl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovs_flow_cmd_get(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **a = info->attrs;
	struct ovs_header *ovs_header = info->userhdr;
	struct sw_flow_key key;
	struct sk_buff *reply;
	struct sw_flow *flow;
	struct datapath *dp;
	struct flow_table *table;
	int err;
	int key_len;

	if (!a[OVS_FLOW_ATTR_KEY])
		return -EINVAL;
	err = ovs_flow_from_nlattrs(&key, &key_len, a[OVS_FLOW_ATTR_KEY]);
	if (err)
		return err;

	ovs_lock();
	dp = get_dp(sock_net(skb->sk), ovs_header->dp_ifindex);
	if (!dp) {
		err = -ENODEV;
		goto unlock;
	}

	table = ovsl_dereference(dp->table);
	flow = ovs_flow_tbl_lookup(table, &key, key_len);
	if (!flow) {
		err = -ENOENT;
		goto unlock;
	}

	reply = ovs_flow_cmd_build_info(flow, dp, info->snd_pid,
					info->snd_seq, OVS_FLOW_CMD_NEW);
	if (IS_ERR(reply)) {
		err = PTR_ERR(reply);
		goto unlock;
	}

	ovs_unlock();
	return genlmsg_reply(reply, info);
unlock:
	ovs_unlock();
	return err;
}