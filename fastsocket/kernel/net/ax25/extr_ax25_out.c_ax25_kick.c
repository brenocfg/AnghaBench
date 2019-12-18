#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/ * sk; } ;
struct TYPE_10__ {scalar_t__ state; int condition; unsigned short va; unsigned short vs; unsigned short window; unsigned short modulus; int /*<<< orphan*/  ack_queue; TYPE_1__* ax25_dev; int /*<<< orphan*/  write_queue; } ;
typedef  TYPE_2__ ax25_cb ;
struct TYPE_9__ {int* values; } ;

/* Variables and functions */
 int AX25_COND_ACK_PENDING ; 
 int AX25_COND_PEER_RX_BUSY ; 
 int /*<<< orphan*/  AX25_POLLOFF ; 
 int /*<<< orphan*/  AX25_POLLON ; 
#define  AX25_PROTO_DAMA_SLAVE 130 
#define  AX25_PROTO_STD_DUPLEX 129 
#define  AX25_PROTO_STD_SIMPLEX 128 
 scalar_t__ AX25_STATE_3 ; 
 scalar_t__ AX25_STATE_4 ; 
 size_t AX25_VALUES_PROTOCOL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ax25_calculate_t1 (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_send_iframe (TYPE_2__*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax25_start_t1timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_stop_t3timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_t1timer_running (TYPE_2__*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,int /*<<< orphan*/ *) ; 

void ax25_kick(ax25_cb *ax25)
{
	struct sk_buff *skb, *skbn;
	int last = 1;
	unsigned short start, end, next;

	if (ax25->state != AX25_STATE_3 && ax25->state != AX25_STATE_4)
		return;

	if (ax25->condition & AX25_COND_PEER_RX_BUSY)
		return;

	if (skb_peek(&ax25->write_queue) == NULL)
		return;

	start = (skb_peek(&ax25->ack_queue) == NULL) ? ax25->va : ax25->vs;
	end   = (ax25->va + ax25->window) % ax25->modulus;

	if (start == end)
		return;

	/*
	 * Transmit data until either we're out of data to send or
	 * the window is full. Send a poll on the final I frame if
	 * the window is filled.
	 */

	/*
	 * Dequeue the frame and copy it.
	 * Check for race with ax25_clear_queues().
	 */
	skb  = skb_dequeue(&ax25->write_queue);
	if (!skb)
		return;

	ax25->vs = start;

	do {
		if ((skbn = skb_clone(skb, GFP_ATOMIC)) == NULL) {
			skb_queue_head(&ax25->write_queue, skb);
			break;
		}

		if (skb->sk != NULL)
			skb_set_owner_w(skbn, skb->sk);

		next = (ax25->vs + 1) % ax25->modulus;
		last = (next == end);

		/*
		 * Transmit the frame copy.
		 * bke 960114: do not set the Poll bit on the last frame
		 * in DAMA mode.
		 */
		switch (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) {
		case AX25_PROTO_STD_SIMPLEX:
		case AX25_PROTO_STD_DUPLEX:
			ax25_send_iframe(ax25, skbn, (last) ? AX25_POLLON : AX25_POLLOFF);
			break;

#ifdef CONFIG_AX25_DAMA_SLAVE
		case AX25_PROTO_DAMA_SLAVE:
			ax25_send_iframe(ax25, skbn, AX25_POLLOFF);
			break;
#endif
		}

		ax25->vs = next;

		/*
		 * Requeue the original data frame.
		 */
		skb_queue_tail(&ax25->ack_queue, skb);

	} while (!last && (skb = skb_dequeue(&ax25->write_queue)) != NULL);

	ax25->condition &= ~AX25_COND_ACK_PENDING;

	if (!ax25_t1timer_running(ax25)) {
		ax25_stop_t3timer(ax25);
		ax25_calculate_t1(ax25);
		ax25_start_t1timer(ax25);
	}
}