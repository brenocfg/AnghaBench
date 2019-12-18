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
struct sock {int /*<<< orphan*/  sk_drops; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  raw_rcv_skb (struct sock*,struct sk_buff*) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  xfrm4_policy_check (struct sock*,int /*<<< orphan*/ ,struct sk_buff*) ; 

int raw_rcv(struct sock *sk, struct sk_buff *skb)
{
	if (!xfrm4_policy_check(sk, XFRM_POLICY_IN, skb)) {
		atomic_inc(&sk->sk_drops);
		kfree_skb(skb);
		return NET_RX_DROP;
	}
	nf_reset(skb);

	skb_push(skb, skb->data - skb_network_header(skb));

	raw_rcv_skb(sk, skb);
	return 0;
}