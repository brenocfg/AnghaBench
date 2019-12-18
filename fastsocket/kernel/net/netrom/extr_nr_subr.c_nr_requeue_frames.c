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
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ack_queue; } ;

/* Variables and functions */
 TYPE_1__* nr_sk (struct sock*) ; 
 int /*<<< orphan*/  skb_append (struct sk_buff*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 

void nr_requeue_frames(struct sock *sk)
{
	struct sk_buff *skb, *skb_prev = NULL;

	while ((skb = skb_dequeue(&nr_sk(sk)->ack_queue)) != NULL) {
		if (skb_prev == NULL)
			skb_queue_head(&sk->sk_write_queue, skb);
		else
			skb_append(skb_prev, skb, &sk->sk_write_queue);
		skb_prev = skb;
	}
}