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
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*,int) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int) ; 

int netlink_sendskb(struct sock *sk, struct sk_buff *skb)
{
	int len = skb->len;

	skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_data_ready(sk, len);
	sock_put(sk);
	return len;
}