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
struct rose_sock {unsigned short va; int /*<<< orphan*/  ack_queue; } ;

/* Variables and functions */
 int ROSE_MODULUS ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct rose_sock* rose_sk (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_peek (int /*<<< orphan*/ *) ; 

void rose_frames_acked(struct sock *sk, unsigned short nr)
{
	struct sk_buff *skb;
	struct rose_sock *rose = rose_sk(sk);

	/*
	 * Remove all the ack-ed frames from the ack queue.
	 */
	if (rose->va != nr) {
		while (skb_peek(&rose->ack_queue) != NULL && rose->va != nr) {
			skb = skb_dequeue(&rose->ack_queue);
			kfree_skb(skb);
			rose->va = (rose->va + 1) % ROSE_MODULUS;
		}
	}
}