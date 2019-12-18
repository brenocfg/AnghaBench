#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tcphdr {int dummy; } ;
struct TYPE_5__ {scalar_t__ proto; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_6__ {TYPE_2__ ip; TYPE_1__ eth; } ;
struct sw_flow {int tcp_flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  byte_count; int /*<<< orphan*/  packet_count; int /*<<< orphan*/  used; TYPE_3__ key; } ;
struct sk_buff {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ IPPROTO_TCP ; 
 int TCP_FLAGS_OFFSET ; 
 int TCP_FLAG_MASK ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ likely (int) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tcp_hdr (struct sk_buff*) ; 

void ovs_flow_used(struct sw_flow *flow, struct sk_buff *skb)
{
	u8 tcp_flags = 0;

	if ((flow->key.eth.type == htons(ETH_P_IP) ||
	     flow->key.eth.type == htons(ETH_P_IPV6)) &&
	    flow->key.ip.proto == IPPROTO_TCP &&
	    likely(skb->len >= skb_transport_offset(skb) + sizeof(struct tcphdr))) {
		u8 *tcp = (u8 *)tcp_hdr(skb);
		tcp_flags = *(tcp + TCP_FLAGS_OFFSET) & TCP_FLAG_MASK;
	}

	spin_lock(&flow->lock);
	flow->used = jiffies;
	flow->packet_count++;
	flow->byte_count += skb->len;
	flow->tcp_flags |= tcp_flags;
	spin_unlock(&flow->lock);
}