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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_TCPRCVCOLLAPSED ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_is_last (struct sk_buff_head*,struct sk_buff*) ; 
 struct sk_buff* skb_queue_next (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static struct sk_buff *tcp_collapse_one(struct sock *sk, struct sk_buff *skb,
					struct sk_buff_head *list)
{
	struct sk_buff *next = NULL;

	if (!skb_queue_is_last(list, skb))
		next = skb_queue_next(list, skb);

	__skb_unlink(skb, list);
	__kfree_skb(skb);
	NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPRCVCOLLAPSED);

	return next;
}