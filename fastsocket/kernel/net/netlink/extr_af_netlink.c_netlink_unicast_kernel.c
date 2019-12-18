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
struct sock {int dummy; } ;
struct sk_buff {int len; } ;
struct netlink_sock {int /*<<< orphan*/  (* netlink_rcv ) (struct sk_buff*) ;} ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*) ; 

__attribute__((used)) static inline int netlink_unicast_kernel(struct sock *sk, struct sk_buff *skb)
{
	int ret;
	struct netlink_sock *nlk = nlk_sk(sk);

	ret = -ECONNREFUSED;
	if (nlk->netlink_rcv != NULL) {
		ret = skb->len;
		skb_set_owner_r(skb, sk);
		nlk->netlink_rcv(skb);
		consume_skb(skb);
	} else {
		kfree_skb(skb);
	}
	sock_put(sk);
	return ret;
}