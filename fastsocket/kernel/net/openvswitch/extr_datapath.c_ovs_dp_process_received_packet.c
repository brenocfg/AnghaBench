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
typedef  int /*<<< orphan*/  u64 ;
struct vport {int /*<<< orphan*/  upcall_pid; int /*<<< orphan*/  port_no; struct datapath* dp; } ;
struct sw_flow_key {int dummy; } ;
struct sw_flow {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dp_upcall_info {int /*<<< orphan*/  pid; int /*<<< orphan*/ * userdata; struct sw_flow_key* key; int /*<<< orphan*/  cmd; } ;
struct dp_stats_percpu {int /*<<< orphan*/  sync; int /*<<< orphan*/  n_hit; int /*<<< orphan*/  n_missed; } ;
struct datapath {int /*<<< orphan*/  table; int /*<<< orphan*/  stats_percpu; } ;
struct TYPE_2__ {struct sw_flow* flow; } ;

/* Variables and functions */
 TYPE_1__* OVS_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  OVS_PACKET_CMD_MISS ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ovs_dp_upcall (struct datapath*,struct sk_buff*,struct dp_upcall_info*) ; 
 int /*<<< orphan*/  ovs_execute_actions (struct datapath*,struct sk_buff*) ; 
 int ovs_flow_extract (struct sk_buff*,int /*<<< orphan*/ ,struct sw_flow_key*,int*) ; 
 struct sw_flow* ovs_flow_tbl_lookup (int /*<<< orphan*/ ,struct sw_flow_key*,int) ; 
 int /*<<< orphan*/  ovs_flow_used (struct sw_flow*,struct sk_buff*) ; 
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 
 struct dp_stats_percpu* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void ovs_dp_process_received_packet(struct vport *p, struct sk_buff *skb)
{
	struct datapath *dp = p->dp;
	struct sw_flow *flow;
	struct dp_stats_percpu *stats;
	struct sw_flow_key key;
	u64 *stats_counter;
	int error;
	int key_len;

	stats = this_cpu_ptr(dp->stats_percpu);

	/* Extract flow from 'skb' into 'key'. */
	error = ovs_flow_extract(skb, p->port_no, &key, &key_len);
	if (unlikely(error)) {
		kfree_skb(skb);
		return;
	}

	/* Look up flow. */
	flow = ovs_flow_tbl_lookup(rcu_dereference(dp->table), &key, key_len);
	if (unlikely(!flow)) {
		struct dp_upcall_info upcall;

		upcall.cmd = OVS_PACKET_CMD_MISS;
		upcall.key = &key;
		upcall.userdata = NULL;
		upcall.pid = p->upcall_pid;
		ovs_dp_upcall(dp, skb, &upcall);
		consume_skb(skb);
		stats_counter = &stats->n_missed;
		goto out;
	}

	OVS_CB(skb)->flow = flow;

	stats_counter = &stats->n_hit;
	ovs_flow_used(OVS_CB(skb)->flow, skb);
	ovs_execute_actions(dp, skb);

out:
	/* Update datapath statistics. */
	u64_stats_update_begin(&stats->sync);
	(*stats_counter)++;
	u64_stats_update_end(&stats->sync);
}