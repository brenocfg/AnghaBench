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
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int dummy; } ;
struct nr_sock {scalar_t__ state; int condition; unsigned short va; unsigned short vs; int window; int /*<<< orphan*/  vr; int /*<<< orphan*/  vl; int /*<<< orphan*/  ack_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NR_COND_ACK_PENDING ; 
 int NR_COND_PEER_RX_BUSY ; 
 int NR_MODULUS ; 
 scalar_t__ NR_STATE_3 ; 
 int /*<<< orphan*/  nr_send_iframe (struct sock*,struct sk_buff*) ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 int /*<<< orphan*/  nr_start_t1timer (struct sock*) ; 
 int /*<<< orphan*/  nr_t1timer_running (struct sock*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 

void nr_kick(struct sock *sk)
{
	struct nr_sock *nr = nr_sk(sk);
	struct sk_buff *skb, *skbn;
	unsigned short start, end;

	if (nr->state != NR_STATE_3)
		return;

	if (nr->condition & NR_COND_PEER_RX_BUSY)
		return;

	if (!skb_peek(&sk->sk_write_queue))
		return;

	start = (skb_peek(&nr->ack_queue) == NULL) ? nr->va : nr->vs;
	end   = (nr->va + nr->window) % NR_MODULUS;

	if (start == end)
		return;

	nr->vs = start;

	/*
	 * Transmit data until either we're out of data to send or
	 * the window is full.
	 */

	/*
	 * Dequeue the frame and copy it.
	 */
	skb = skb_dequeue(&sk->sk_write_queue);

	do {
		if ((skbn = skb_clone(skb, GFP_ATOMIC)) == NULL) {
			skb_queue_head(&sk->sk_write_queue, skb);
			break;
		}

		skb_set_owner_w(skbn, sk);

		/*
		 * Transmit the frame copy.
		 */
		nr_send_iframe(sk, skbn);

		nr->vs = (nr->vs + 1) % NR_MODULUS;

		/*
		 * Requeue the original data frame.
		 */
		skb_queue_tail(&nr->ack_queue, skb);

	} while (nr->vs != end &&
		 (skb = skb_dequeue(&sk->sk_write_queue)) != NULL);

	nr->vl         = nr->vr;
	nr->condition &= ~NR_COND_ACK_PENDING;

	if (!nr_t1timer_running(sk))
		nr_start_t1timer(sk);
}