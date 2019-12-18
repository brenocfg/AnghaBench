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
struct sk_buff {int dummy; } ;
struct dp_upcall_info {scalar_t__ pid; } ;
struct dp_stats_percpu {int /*<<< orphan*/  sync; int /*<<< orphan*/  n_lost; } ;
struct datapath {int /*<<< orphan*/  stats_percpu; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOTCONN ; 
 int get_dpifindex (struct datapath*) ; 
 int /*<<< orphan*/  ovs_dp_get_net (struct datapath*) ; 
 int queue_gso_packets (int /*<<< orphan*/ ,int,struct sk_buff*,struct dp_upcall_info const*) ; 
 int queue_userspace_packet (int /*<<< orphan*/ ,int,struct sk_buff*,struct dp_upcall_info const*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 struct dp_stats_percpu* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

int ovs_dp_upcall(struct datapath *dp, struct sk_buff *skb,
		  const struct dp_upcall_info *upcall_info)
{
	struct dp_stats_percpu *stats;
	int dp_ifindex;
	int err;

	if (upcall_info->pid == 0) {
		err = -ENOTCONN;
		goto err;
	}

	dp_ifindex = get_dpifindex(dp);
	if (!dp_ifindex) {
		err = -ENODEV;
		goto err;
	}

	if (!skb_is_gso(skb))
		err = queue_userspace_packet(ovs_dp_get_net(dp), dp_ifindex, skb, upcall_info);
	else
		err = queue_gso_packets(ovs_dp_get_net(dp), dp_ifindex, skb, upcall_info);
	if (err)
		goto err;

	return 0;

err:
	stats = this_cpu_ptr(dp->stats_percpu);

	u64_stats_update_begin(&stats->sync);
	stats->n_lost++;
	u64_stats_update_end(&stats->sync);

	return err;
}