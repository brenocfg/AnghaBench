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
struct sk_buff {int /*<<< orphan*/  mark; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  seq; } ;
struct rxrpc_skb_priv {TYPE_1__ hdr; } ;
struct rxrpc_call {scalar_t__ rx_first_oos; int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_oos_queue; int /*<<< orphan*/  rx_data_post; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ECONNRESET ; 
 int /*<<< orphan*/  RXRPC_CALL_RELEASED ; 
 int RXRPC_CLIENT_INITIATED ; 
 int RXRPC_LAST_PACKET ; 
 int /*<<< orphan*/  RXRPC_SKB_MARK_DATA ; 
 int /*<<< orphan*/  _debug (char*,struct sk_buff*,...) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int rxrpc_queue_rcv_skb (struct rxrpc_call*,struct sk_buff*,int,int) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rxrpc_drain_rx_oos_queue(struct rxrpc_call *call)
{
	struct rxrpc_skb_priv *sp;
	struct sk_buff *skb;
	bool terminal;
	int ret;

	_enter("{%d,%d}", call->rx_data_post, call->rx_first_oos);

	spin_lock_bh(&call->lock);

	ret = -ECONNRESET;
	if (test_bit(RXRPC_CALL_RELEASED, &call->flags))
		goto socket_unavailable;

	skb = skb_dequeue(&call->rx_oos_queue);
	if (skb) {
		sp = rxrpc_skb(skb);

		_debug("drain OOS packet %d [%d]",
		       ntohl(sp->hdr.seq), call->rx_first_oos);

		if (ntohl(sp->hdr.seq) != call->rx_first_oos) {
			skb_queue_head(&call->rx_oos_queue, skb);
			call->rx_first_oos = ntohl(rxrpc_skb(skb)->hdr.seq);
			_debug("requeue %p {%u}", skb, call->rx_first_oos);
		} else {
			skb->mark = RXRPC_SKB_MARK_DATA;
			terminal = ((sp->hdr.flags & RXRPC_LAST_PACKET) &&
				!(sp->hdr.flags & RXRPC_CLIENT_INITIATED));
			ret = rxrpc_queue_rcv_skb(call, skb, true, terminal);
			BUG_ON(ret < 0);
			_debug("drain #%u", call->rx_data_post);
			call->rx_data_post++;

			/* find out what the next packet is */
			skb = skb_peek(&call->rx_oos_queue);
			if (skb)
				call->rx_first_oos =
					ntohl(rxrpc_skb(skb)->hdr.seq);
			else
				call->rx_first_oos = 0;
			_debug("peek %p {%u}", skb, call->rx_first_oos);
		}
	}

	ret = 0;
socket_unavailable:
	spin_unlock_bh(&call->lock);
	_leave(" = %d", ret);
	return ret;
}