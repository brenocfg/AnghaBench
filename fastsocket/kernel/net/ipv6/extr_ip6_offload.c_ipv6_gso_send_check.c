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
struct net_offload {int (* gso_send_check ) (struct sk_buff*) ;} ;
struct ipv6hdr {int /*<<< orphan*/  nexthdr; } ;
struct inet6_protocol {scalar_t__ gso_send_check; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/ * inet6_offloads ; 
 int /*<<< orphan*/ * inet6_protos ; 
 int ipv6_gso_pull_exthdrs (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 
 int stub2 (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ipv6_gso_send_check(struct sk_buff *skb)
{
	struct ipv6hdr *ipv6h;
	const struct net_offload *ops;
	const struct inet6_protocol *proto_ops;
	int proto;
	int err = -EINVAL;

	if (unlikely(!pskb_may_pull(skb, sizeof(*ipv6h))))
		goto out;

	ipv6h = ipv6_hdr(skb);
	__skb_pull(skb, sizeof(*ipv6h));
	err = -EPROTONOSUPPORT;

	rcu_read_lock();
	proto = ipv6_gso_pull_exthdrs(skb, ipv6h->nexthdr);
	ops = rcu_dereference(inet6_offloads[proto]);

	if (likely(ops && ops->gso_send_check)) {
		skb_reset_transport_header(skb);
		err = ops->gso_send_check(skb);
	} else {
		proto_ops = rcu_dereference(inet6_protos[proto]);
		if (proto_ops && proto_ops->gso_send_check) {
			skb_reset_transport_header(skb);
			err = ops->gso_send_check(skb);
		}
	}

	rcu_read_unlock();

out:
	return err;
}