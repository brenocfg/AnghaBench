#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int winsize_out; } ;
struct x25_sock {scalar_t__ state; int intflag; int condition; unsigned short vs; unsigned short va; int /*<<< orphan*/  vr; int /*<<< orphan*/  vl; int /*<<< orphan*/  ack_queue; TYPE_1__ facilities; TYPE_2__* neighbour; int /*<<< orphan*/  interrupt_out_queue; } ;
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {scalar_t__ extended; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int X25_COND_ACK_PENDING ; 
 int X25_COND_PEER_RX_BUSY ; 
 int X25_EMODULUS ; 
 int X25_SMODULUS ; 
 scalar_t__ X25_STATE_3 ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  x25_send_iframe (struct sock*,struct sk_buff*) ; 
 struct x25_sock* x25_sk (struct sock*) ; 
 int /*<<< orphan*/  x25_stop_timer (struct sock*) ; 
 int /*<<< orphan*/  x25_transmit_link (struct sk_buff*,TYPE_2__*) ; 

void x25_kick(struct sock *sk)
{
	struct sk_buff *skb, *skbn;
	unsigned short start, end;
	int modulus;
	struct x25_sock *x25 = x25_sk(sk);

	if (x25->state != X25_STATE_3)
		return;

	/*
	 *	Transmit interrupt data.
	 */
	if (!x25->intflag && skb_peek(&x25->interrupt_out_queue) != NULL) {
		x25->intflag = 1;
		skb = skb_dequeue(&x25->interrupt_out_queue);
		x25_transmit_link(skb, x25->neighbour);
	}

	if (x25->condition & X25_COND_PEER_RX_BUSY)
		return;

	if (!skb_peek(&sk->sk_write_queue))
		return;

	modulus = x25->neighbour->extended ? X25_EMODULUS : X25_SMODULUS;

	start   = skb_peek(&x25->ack_queue) ? x25->vs : x25->va;
	end     = (x25->va + x25->facilities.winsize_out) % modulus;

	if (start == end)
		return;

	x25->vs = start;

	/*
	 * Transmit data until either we're out of data to send or
	 * the window is full.
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
		x25_send_iframe(sk, skbn);

		x25->vs = (x25->vs + 1) % modulus;

		/*
		 * Requeue the original data frame.
		 */
		skb_queue_tail(&x25->ack_queue, skb);

	} while (x25->vs != end &&
		 (skb = skb_dequeue(&sk->sk_write_queue)) != NULL);

	x25->vl         = x25->vr;
	x25->condition &= ~X25_COND_ACK_PENDING;

	x25_stop_timer(sk);
}