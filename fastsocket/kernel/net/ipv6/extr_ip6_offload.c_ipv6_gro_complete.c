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
struct sk_buff {scalar_t__ len; } ;
struct net_offload {int (* gro_complete ) (struct sk_buff*) ;} ;
struct ipv6hdr {int /*<<< orphan*/  payload_len; } ;
struct inet6_protocol {int (* gro_complete ) (struct sk_buff*) ;} ;
struct TYPE_2__ {size_t proto; } ;

/* Variables and functions */
 int ENOSYS ; 
 TYPE_1__* IPV6_GRO_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/ * inet6_offloads ; 
 int /*<<< orphan*/ * inet6_protos ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 
 int stub2 (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ipv6_gro_complete(struct sk_buff *skb)
{
	const struct net_offload *ops;
	const struct inet6_protocol *proto_ops;
	struct ipv6hdr *iph = ipv6_hdr(skb);
	int err = -ENOSYS;

	iph->payload_len = htons(skb->len - skb_network_offset(skb) -
				 sizeof(*iph));

	rcu_read_lock();
	ops = rcu_dereference(inet6_offloads[IPV6_GRO_CB(skb)->proto]);
	if (unlikely(!ops || !ops->gro_complete)) {
		proto_ops = rcu_dereference(inet6_protos[IPV6_GRO_CB(skb)->proto]);
		if (!proto_ops || !proto_ops->gro_complete) {
			WARN_ON(true);
			goto out_unlock;
		}
		err = proto_ops->gro_complete(skb);
	} else
		err = ops->gro_complete(skb);

out_unlock:
	rcu_read_unlock();

	return err;
}