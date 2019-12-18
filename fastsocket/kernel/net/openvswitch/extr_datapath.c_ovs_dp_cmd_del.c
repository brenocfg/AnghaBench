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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_pid; int /*<<< orphan*/  attrs; int /*<<< orphan*/  userhdr; } ;
struct datapath {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  OVS_DP_CMD_DEL ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  __dp_destroy (struct sk_buff*) ; 
 struct sk_buff* lookup_datapath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ovs_dp_cmd_build_info (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_dp_datapath_multicast_group ; 
 int /*<<< orphan*/  ovs_lock () ; 
 int /*<<< orphan*/  ovs_notify (struct sk_buff*,struct genl_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ovs_unlock () ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovs_dp_cmd_del(struct sk_buff *skb, struct genl_info *info)
{
	struct sk_buff *reply;
	struct datapath *dp;
	int err;

	ovs_lock();
	dp = lookup_datapath(sock_net(skb->sk), info->userhdr, info->attrs);
	err = PTR_ERR(dp);
	if (IS_ERR(dp))
		goto unlock;

	reply = ovs_dp_cmd_build_info(dp, info->snd_pid,
				      info->snd_seq, OVS_DP_CMD_DEL);
	err = PTR_ERR(reply);
	if (IS_ERR(reply))
		goto unlock;

	__dp_destroy(dp);
	ovs_unlock();

	ovs_notify(reply, info, &ovs_dp_datapath_multicast_group);

	return 0;
unlock:
	ovs_unlock();
	return err;
}