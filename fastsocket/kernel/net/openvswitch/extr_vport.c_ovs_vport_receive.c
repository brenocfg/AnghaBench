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
struct vport_percpu_stats {int /*<<< orphan*/  sync; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct vport {int /*<<< orphan*/  percpu_stats; } ;
struct sk_buff {scalar_t__ len; } ;
struct ovs_key_ipv4_tunnel {int dummy; } ;
struct TYPE_2__ {struct ovs_key_ipv4_tunnel* tun_key; } ;

/* Variables and functions */
 TYPE_1__* OVS_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ovs_dp_process_received_packet (struct vport*,struct sk_buff*) ; 
 struct vport_percpu_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

void ovs_vport_receive(struct vport *vport, struct sk_buff *skb,
		       struct ovs_key_ipv4_tunnel *tun_key)
{
	struct vport_percpu_stats *stats;

	stats = this_cpu_ptr(vport->percpu_stats);
	u64_stats_update_begin(&stats->sync);
	stats->rx_packets++;
	stats->rx_bytes += skb->len;
	u64_stats_update_end(&stats->sync);

	OVS_CB(skb)->tun_key = tun_key;
	ovs_dp_process_received_packet(vport, skb);
}