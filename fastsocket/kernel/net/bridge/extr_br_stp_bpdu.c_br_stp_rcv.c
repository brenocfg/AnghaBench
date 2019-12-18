#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stp_proto {int dummy; } ;
struct sk_buff {unsigned char* data; } ;
struct net_device {int /*<<< orphan*/  br_port; } ;
struct net_bridge_port {scalar_t__ state; struct net_bridge* br; } ;
struct net_bridge {scalar_t__ stp_enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  group_addr; TYPE_1__* dev; } ;
struct TYPE_7__ {unsigned char* prio; unsigned char* addr; } ;
struct TYPE_6__ {unsigned char* prio; unsigned char* addr; } ;
struct br_config_bpdu {int topology_change; int topology_change_ack; unsigned char root_path_cost; unsigned char port_id; void* forward_delay; void* hello_time; void* max_age; void* message_age; TYPE_3__ bridge_id; TYPE_2__ root; } ;
struct TYPE_8__ {unsigned char* h_dest; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 unsigned char const BPDU_TYPE_CONFIG ; 
 unsigned char const BPDU_TYPE_TCN ; 
 scalar_t__ BR_KERNEL_STP ; 
 scalar_t__ BR_STATE_DISABLED ; 
 int IFF_UP ; 
 void* br_get_ticks (unsigned char const*) ; 
 int /*<<< orphan*/  br_received_config_bpdu (struct net_bridge_port*,struct br_config_bpdu*) ; 
 int /*<<< orphan*/  br_received_tcn_bpdu (struct net_bridge_port*) ; 
 scalar_t__ compare_ether_addr (unsigned char const*,int /*<<< orphan*/ ) ; 
 TYPE_4__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 struct net_bridge_port* rcu_dereference (int /*<<< orphan*/ ) ; 
 unsigned char* skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void br_stp_rcv(const struct stp_proto *proto, struct sk_buff *skb,
		struct net_device *dev)
{
	const unsigned char *dest = eth_hdr(skb)->h_dest;
	struct net_bridge_port *p = rcu_dereference(dev->br_port);
	struct net_bridge *br;
	const unsigned char *buf;

	if (!p)
		goto err;

	if (!pskb_may_pull(skb, 4))
		goto err;

	/* compare of protocol id and version */
	buf = skb->data;
	if (buf[0] != 0 || buf[1] != 0 || buf[2] != 0)
		goto err;

	br = p->br;
	spin_lock(&br->lock);

	if (br->stp_enabled != BR_KERNEL_STP)
		goto out;

	if (!(br->dev->flags & IFF_UP))
		goto out;

	if (p->state == BR_STATE_DISABLED)
		goto out;

	if (compare_ether_addr(dest, br->group_addr) != 0)
		goto out;

	buf = skb_pull(skb, 3);

	if (buf[0] == BPDU_TYPE_CONFIG) {
		struct br_config_bpdu bpdu;

		if (!pskb_may_pull(skb, 32))
			goto out;

		buf = skb->data;
		bpdu.topology_change = (buf[1] & 0x01) ? 1 : 0;
		bpdu.topology_change_ack = (buf[1] & 0x80) ? 1 : 0;

		bpdu.root.prio[0] = buf[2];
		bpdu.root.prio[1] = buf[3];
		bpdu.root.addr[0] = buf[4];
		bpdu.root.addr[1] = buf[5];
		bpdu.root.addr[2] = buf[6];
		bpdu.root.addr[3] = buf[7];
		bpdu.root.addr[4] = buf[8];
		bpdu.root.addr[5] = buf[9];
		bpdu.root_path_cost =
			(buf[10] << 24) |
			(buf[11] << 16) |
			(buf[12] << 8) |
			buf[13];
		bpdu.bridge_id.prio[0] = buf[14];
		bpdu.bridge_id.prio[1] = buf[15];
		bpdu.bridge_id.addr[0] = buf[16];
		bpdu.bridge_id.addr[1] = buf[17];
		bpdu.bridge_id.addr[2] = buf[18];
		bpdu.bridge_id.addr[3] = buf[19];
		bpdu.bridge_id.addr[4] = buf[20];
		bpdu.bridge_id.addr[5] = buf[21];
		bpdu.port_id = (buf[22] << 8) | buf[23];

		bpdu.message_age = br_get_ticks(buf+24);
		bpdu.max_age = br_get_ticks(buf+26);
		bpdu.hello_time = br_get_ticks(buf+28);
		bpdu.forward_delay = br_get_ticks(buf+30);

		br_received_config_bpdu(p, &bpdu);
	}

	else if (buf[0] == BPDU_TYPE_TCN) {
		br_received_tcn_bpdu(p);
	}
 out:
	spin_unlock(&br->lock);
 err:
	kfree_skb(skb);
}