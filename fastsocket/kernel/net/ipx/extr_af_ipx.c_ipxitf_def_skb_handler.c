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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static void ipxitf_def_skb_handler(struct sock *sock, struct sk_buff *skb)
{
	if (sock_queue_rcv_skb(sock, skb) < 0)
		kfree_skb(skb);
}