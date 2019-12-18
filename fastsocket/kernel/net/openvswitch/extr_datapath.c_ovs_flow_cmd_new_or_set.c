#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sw_flow_key {int dummy; } ;
struct sw_flow_actions {int /*<<< orphan*/  sk; int /*<<< orphan*/  lock; int /*<<< orphan*/  sf_acts; } ;
struct sw_flow {int /*<<< orphan*/  sk; int /*<<< orphan*/  lock; int /*<<< orphan*/  sf_acts; } ;
struct sk_buff {int /*<<< orphan*/  sk; int /*<<< orphan*/  lock; int /*<<< orphan*/  sf_acts; } ;
struct ovs_header {int /*<<< orphan*/  dp_ifindex; } ;
struct nlattr {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_pid; TYPE_2__* nlhdr; TYPE_1__* genlhdr; struct ovs_header* userhdr; struct nlattr** attrs; } ;
struct flow_table {int /*<<< orphan*/  sk; int /*<<< orphan*/  lock; int /*<<< orphan*/  sf_acts; } ;
struct datapath {int /*<<< orphan*/  table; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {int /*<<< orphan*/  genl_sock; } ;
struct TYPE_8__ {int nlmsg_flags; } ;
struct TYPE_7__ {scalar_t__ cmd; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct sw_flow_actions*) ; 
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
 size_t OVS_FLOW_ATTR_ACTIONS ; 
 size_t OVS_FLOW_ATTR_CLEAR ; 
 size_t OVS_FLOW_ATTR_KEY ; 
 scalar_t__ OVS_FLOW_CMD_NEW ; 
 scalar_t__ OVS_FLOW_CMD_SET ; 
 int PTR_ERR (struct sw_flow_actions*) ; 
 int /*<<< orphan*/  clear_stats (struct sw_flow_actions*) ; 
 struct datapath* get_dp (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sw_flow_actions*) ; 
 int /*<<< orphan*/  netlink_set_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 TYPE_4__ ovs_dp_flow_multicast_group ; 
 struct sw_flow_actions* ovs_flow_actions_alloc (int /*<<< orphan*/ ) ; 
 struct sw_flow_actions* ovs_flow_alloc () ; 
 struct sw_flow_actions* ovs_flow_cmd_build_info (struct sw_flow_actions*,struct datapath*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ovs_flow_deferred_free_acts (struct sw_flow_actions*) ; 
 int ovs_flow_from_nlattrs (struct sw_flow_key*,int*,struct nlattr*) ; 
 int /*<<< orphan*/  ovs_flow_tbl_deferred_destroy (struct sw_flow_actions*) ; 
 struct sw_flow_actions* ovs_flow_tbl_expand (struct sw_flow_actions*) ; 
 int /*<<< orphan*/  ovs_flow_tbl_insert (struct sw_flow_actions*,struct sw_flow_actions*,struct sw_flow_key*,int) ; 
 struct sw_flow_actions* ovs_flow_tbl_lookup (struct sw_flow_actions*,struct sw_flow_key*,int) ; 
 scalar_t__ ovs_flow_tbl_need_to_expand (struct sw_flow_actions*) ; 
 int /*<<< orphan*/  ovs_lock () ; 
 int /*<<< orphan*/  ovs_notify (struct sw_flow_actions*,struct genl_info*,TYPE_4__*) ; 
 int /*<<< orphan*/  ovs_unlock () ; 
 struct sw_flow_actions* ovsl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct sw_flow_actions*) ; 
 TYPE_3__* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int validate_and_copy_actions (struct nlattr*,struct sw_flow_key*,int /*<<< orphan*/ ,struct sw_flow_actions**) ; 

__attribute__((used)) static int ovs_flow_cmd_new_or_set(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **a = info->attrs;
	struct ovs_header *ovs_header = info->userhdr;
	struct sw_flow_key key;
	struct sw_flow *flow;
	struct sk_buff *reply;
	struct datapath *dp;
	struct flow_table *table;
	struct sw_flow_actions *acts = NULL;
	int error;
	int key_len;

	/* Extract key. */
	error = -EINVAL;
	if (!a[OVS_FLOW_ATTR_KEY])
		goto error;
	error = ovs_flow_from_nlattrs(&key, &key_len, a[OVS_FLOW_ATTR_KEY]);
	if (error)
		goto error;

	/* Validate actions. */
	if (a[OVS_FLOW_ATTR_ACTIONS]) {
		acts = ovs_flow_actions_alloc(nla_len(a[OVS_FLOW_ATTR_ACTIONS]));
		error = PTR_ERR(acts);
		if (IS_ERR(acts))
			goto error;

		error = validate_and_copy_actions(a[OVS_FLOW_ATTR_ACTIONS], &key,  0, &acts);
		if (error)
			goto err_kfree;
	} else if (info->genlhdr->cmd == OVS_FLOW_CMD_NEW) {
		error = -EINVAL;
		goto error;
	}

	ovs_lock();
	dp = get_dp(sock_net(skb->sk), ovs_header->dp_ifindex);
	error = -ENODEV;
	if (!dp)
		goto err_unlock_ovs;

	table = ovsl_dereference(dp->table);
	flow = ovs_flow_tbl_lookup(table, &key, key_len);
	if (!flow) {
		/* Bail out if we're not allowed to create a new flow. */
		error = -ENOENT;
		if (info->genlhdr->cmd == OVS_FLOW_CMD_SET)
			goto err_unlock_ovs;

		/* Expand table, if necessary, to make room. */
		if (ovs_flow_tbl_need_to_expand(table)) {
			struct flow_table *new_table;

			new_table = ovs_flow_tbl_expand(table);
			if (!IS_ERR(new_table)) {
				rcu_assign_pointer(dp->table, new_table);
				ovs_flow_tbl_deferred_destroy(table);
				table = ovsl_dereference(dp->table);
			}
		}

		/* Allocate flow. */
		flow = ovs_flow_alloc();
		if (IS_ERR(flow)) {
			error = PTR_ERR(flow);
			goto err_unlock_ovs;
		}
		clear_stats(flow);

		rcu_assign_pointer(flow->sf_acts, acts);

		/* Put flow in bucket. */
		ovs_flow_tbl_insert(table, flow, &key, key_len);

		reply = ovs_flow_cmd_build_info(flow, dp, info->snd_pid,
						info->snd_seq,
						OVS_FLOW_CMD_NEW);
	} else {
		/* We found a matching flow. */
		struct sw_flow_actions *old_acts;

		/* Bail out if we're not allowed to modify an existing flow.
		 * We accept NLM_F_CREATE in place of the intended NLM_F_EXCL
		 * because Generic Netlink treats the latter as a dump
		 * request.  We also accept NLM_F_EXCL in case that bug ever
		 * gets fixed.
		 */
		error = -EEXIST;
		if (info->genlhdr->cmd == OVS_FLOW_CMD_NEW &&
		    info->nlhdr->nlmsg_flags & (NLM_F_CREATE | NLM_F_EXCL))
			goto err_unlock_ovs;

		/* Update actions. */
		old_acts = ovsl_dereference(flow->sf_acts);
		rcu_assign_pointer(flow->sf_acts, acts);
		ovs_flow_deferred_free_acts(old_acts);

		reply = ovs_flow_cmd_build_info(flow, dp, info->snd_pid,
					       info->snd_seq, OVS_FLOW_CMD_NEW);

		/* Clear stats. */
		if (a[OVS_FLOW_ATTR_CLEAR]) {
			spin_lock_bh(&flow->lock);
			clear_stats(flow);
			spin_unlock_bh(&flow->lock);
		}
	}
	ovs_unlock();

	if (!IS_ERR(reply))
		ovs_notify(reply, info, &ovs_dp_flow_multicast_group);
	else
		netlink_set_err(sock_net(skb->sk)->genl_sock, 0,
				ovs_dp_flow_multicast_group.id, PTR_ERR(reply));
	return 0;

err_unlock_ovs:
	ovs_unlock();
err_kfree:
	kfree(acts);
error:
	return error;
}