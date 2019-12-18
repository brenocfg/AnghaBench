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
struct net_protocol {int (* gso_send_check ) (struct sk_buff*) ;} ;
struct net_offload {int (* gso_send_check ) (struct sk_buff*) ;} ;
struct iphdr {int ihl; int protocol; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int MAX_INET_PROTOS ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/ * inet_offloads ; 
 int /*<<< orphan*/ * inet_protos ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 
 int stub2 (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int inet_gso_send_check(struct sk_buff *skb)
{
	struct iphdr *iph;
	const struct net_offload *ops;
	const struct net_protocol *proto_ops;
	int proto;
	int ihl;
	int err = -EINVAL;

	if (unlikely(!pskb_may_pull(skb, sizeof(*iph))))
		goto out;

	iph = ip_hdr(skb);
	ihl = iph->ihl * 4;
	if (ihl < sizeof(*iph))
		goto out;

	if (unlikely(!pskb_may_pull(skb, ihl)))
		goto out;

	__skb_pull(skb, ihl);
	skb_reset_transport_header(skb);
	iph = ip_hdr(skb);
	proto = iph->protocol & (MAX_INET_PROTOS - 1);
	err = -EPROTONOSUPPORT;

	rcu_read_lock();
	ops = rcu_dereference(inet_offloads[proto]);
	if (likely(ops && ops->gso_send_check))
		err = ops->gso_send_check(skb);
	else {
		/* Check protocols array for any protocols
		 * using old API.
		 */
		proto_ops = rcu_dereference(inet_protos[proto]);
		if (proto_ops && proto_ops->gso_send_check)
			err = proto_ops->gso_send_check(skb);
	}

	rcu_read_unlock();

out:
	return err;
}