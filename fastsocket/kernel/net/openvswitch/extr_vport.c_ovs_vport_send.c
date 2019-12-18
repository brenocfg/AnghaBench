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
struct vport_percpu_stats {int tx_bytes; int /*<<< orphan*/  sync; int /*<<< orphan*/  tx_packets; } ;
struct vport {int /*<<< orphan*/  percpu_stats; TYPE_1__* ops; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int (* send ) (struct vport*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VPORT_E_TX_DROPPED ; 
 int /*<<< orphan*/  VPORT_E_TX_ERROR ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  ovs_vport_record_error (struct vport*,int /*<<< orphan*/ ) ; 
 int stub1 (struct vport*,struct sk_buff*) ; 
 struct vport_percpu_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

int ovs_vport_send(struct vport *vport, struct sk_buff *skb)
{
	int sent = vport->ops->send(vport, skb);

	if (likely(sent > 0)) {
		struct vport_percpu_stats *stats;

		stats = this_cpu_ptr(vport->percpu_stats);

		u64_stats_update_begin(&stats->sync);
		stats->tx_packets++;
		stats->tx_bytes += sent;
		u64_stats_update_end(&stats->sync);
	} else if (sent < 0) {
		ovs_vport_record_error(vport, VPORT_E_TX_ERROR);
		kfree_skb(skb);
	} else
		ovs_vport_record_error(vport, VPORT_E_TX_DROPPED);

	return sent;
}