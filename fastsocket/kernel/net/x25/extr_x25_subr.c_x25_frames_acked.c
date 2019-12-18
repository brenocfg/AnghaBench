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
struct x25_sock {unsigned short va; int /*<<< orphan*/  ack_queue; TYPE_1__* neighbour; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ extended; } ;

/* Variables and functions */
 int X25_EMODULUS ; 
 int X25_SMODULUS ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_peek (int /*<<< orphan*/ *) ; 
 struct x25_sock* x25_sk (struct sock*) ; 

void x25_frames_acked(struct sock *sk, unsigned short nr)
{
	struct sk_buff *skb;
	struct x25_sock *x25 = x25_sk(sk);
	int modulus = x25->neighbour->extended ? X25_EMODULUS : X25_SMODULUS;

	/*
	 * Remove all the ack-ed frames from the ack queue.
	 */
	if (x25->va != nr)
		while (skb_peek(&x25->ack_queue) && x25->va != nr) {
			skb = skb_dequeue(&x25->ack_queue);
			kfree_skb(skb);
			x25->va = (x25->va + 1) % modulus;
		}
}