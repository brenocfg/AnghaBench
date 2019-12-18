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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sw_flow_actions {int /*<<< orphan*/  actions_len; int /*<<< orphan*/  actions; } ;
struct sw_flow {unsigned long used; int /*<<< orphan*/  lock; scalar_t__ tcp_flags; int /*<<< orphan*/  byte_count; scalar_t__ packet_count; int /*<<< orphan*/  key; int /*<<< orphan*/  sf_acts; } ;
struct sk_buff {int len; } ;
struct ovs_header {int /*<<< orphan*/  dp_ifindex; } ;
struct ovs_flow_stats {scalar_t__ n_packets; int /*<<< orphan*/  n_bytes; } ;
struct nlattr {int dummy; } ;
struct datapath {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  OVS_FLOW_ATTR_ACTIONS ; 
 int /*<<< orphan*/  OVS_FLOW_ATTR_KEY ; 
 int /*<<< orphan*/  OVS_FLOW_ATTR_STATS ; 
 int /*<<< orphan*/  OVS_FLOW_ATTR_TCP_FLAGS ; 
 int /*<<< orphan*/  OVS_FLOW_ATTR_USED ; 
 int actions_to_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  dp_flow_genl_family ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,struct ovs_header*) ; 
 int genlmsg_end (struct sk_buff*,struct ovs_header*) ; 
 struct ovs_header* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  get_dpifindex (struct datapath*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct ovs_flow_stats*) ; 
 scalar_t__ nla_put_u64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int ovs_flow_to_nlattrs (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  ovs_flow_used_time (unsigned long) ; 
 struct sw_flow_actions* ovsl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ovs_flow_cmd_fill_info(struct sw_flow *flow, struct datapath *dp,
				  struct sk_buff *skb, u32 pid,
				  u32 seq, u32 flags, u8 cmd)
{
	const int skb_orig_len = skb->len;
	const struct sw_flow_actions *sf_acts;
	struct nlattr *start;
	struct ovs_flow_stats stats;
	struct ovs_header *ovs_header;
	struct nlattr *nla;
	unsigned long used;
	u8 tcp_flags;
	int err;

	sf_acts = ovsl_dereference(flow->sf_acts);

	ovs_header = genlmsg_put(skb, pid, seq, &dp_flow_genl_family, flags, cmd);
	if (!ovs_header)
		return -EMSGSIZE;

	ovs_header->dp_ifindex = get_dpifindex(dp);

	nla = nla_nest_start(skb, OVS_FLOW_ATTR_KEY);
	if (!nla)
		goto nla_put_failure;
	err = ovs_flow_to_nlattrs(&flow->key, skb);
	if (err)
		goto error;
	nla_nest_end(skb, nla);

	spin_lock_bh(&flow->lock);
	used = flow->used;
	stats.n_packets = flow->packet_count;
	stats.n_bytes = flow->byte_count;
	tcp_flags = flow->tcp_flags;
	spin_unlock_bh(&flow->lock);

	if (used &&
	    nla_put_u64(skb, OVS_FLOW_ATTR_USED, ovs_flow_used_time(used)))
		goto nla_put_failure;

	if (stats.n_packets &&
	    nla_put(skb, OVS_FLOW_ATTR_STATS,
		    sizeof(struct ovs_flow_stats), &stats))
		goto nla_put_failure;

	if (tcp_flags &&
	    nla_put_u8(skb, OVS_FLOW_ATTR_TCP_FLAGS, tcp_flags))
		goto nla_put_failure;

	/* If OVS_FLOW_ATTR_ACTIONS doesn't fit, skip dumping the actions if
	 * this is the first flow to be dumped into 'skb'.  This is unusual for
	 * Netlink but individual action lists can be longer than
	 * NLMSG_GOODSIZE and thus entirely undumpable if we didn't do this.
	 * The userspace caller can always fetch the actions separately if it
	 * really wants them.  (Most userspace callers in fact don't care.)
	 *
	 * This can only fail for dump operations because the skb is always
	 * properly sized for single flows.
	 */
	start = nla_nest_start(skb, OVS_FLOW_ATTR_ACTIONS);
	if (start) {
		err = actions_to_attr(sf_acts->actions, sf_acts->actions_len, skb);
		if (!err)
			nla_nest_end(skb, start);
		else {
			if (skb_orig_len)
				goto error;

			nla_nest_cancel(skb, start);
		}
	} else if (skb_orig_len)
		goto nla_put_failure;

	return genlmsg_end(skb, ovs_header);

nla_put_failure:
	err = -EMSGSIZE;
error:
	genlmsg_cancel(skb, ovs_header);
	return err;
}