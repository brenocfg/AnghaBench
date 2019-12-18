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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data_len; } ;
struct TYPE_2__ {int flags; void* serial; int /*<<< orphan*/  _rsvd; void* seq; } ;
struct rxrpc_skb_priv {TYPE_1__ hdr; } ;
struct rxrpc_jumbo_header {int flags; int /*<<< orphan*/  _rsvd; } ;
struct rxrpc_call {scalar_t__ state; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  events; int /*<<< orphan*/  abort_code; } ;
typedef  int /*<<< orphan*/  jhdr ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RXRPC_CALL_ABORT ; 
 scalar_t__ RXRPC_CALL_COMPLETE ; 
 scalar_t__ RXRPC_CALL_LOCALLY_ABORTED ; 
 int RXRPC_JUMBO_DATALEN ; 
 int RXRPC_JUMBO_PACKET ; 
 int /*<<< orphan*/  RX_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  _proto (char*,scalar_t__) ; 
 void* htonl (scalar_t__) ; 
 scalar_t__ ntohl (void*) ; 
 int /*<<< orphan*/  pskb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  pskb_trim (struct sk_buff*,int) ; 
 int /*<<< orphan*/  rxrpc_fast_process_packet (struct rxrpc_call*,struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_free_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_new_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_queue_call (struct rxrpc_call*) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,struct rxrpc_jumbo_header*,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_process_jumbo_packet(struct rxrpc_call *call,
				       struct sk_buff *jumbo)
{
	struct rxrpc_jumbo_header jhdr;
	struct rxrpc_skb_priv *sp;
	struct sk_buff *part;

	_enter(",{%u,%u}", jumbo->data_len, jumbo->len);

	sp = rxrpc_skb(jumbo);

	do {
		sp->hdr.flags &= ~RXRPC_JUMBO_PACKET;

		/* make a clone to represent the first subpacket in what's left
		 * of the jumbo packet */
		part = skb_clone(jumbo, GFP_ATOMIC);
		if (!part) {
			/* simply ditch the tail in the event of ENOMEM */
			pskb_trim(jumbo, RXRPC_JUMBO_DATALEN);
			break;
		}
		rxrpc_new_skb(part);

		pskb_trim(part, RXRPC_JUMBO_DATALEN);

		if (!pskb_pull(jumbo, RXRPC_JUMBO_DATALEN))
			goto protocol_error;

		if (skb_copy_bits(jumbo, 0, &jhdr, sizeof(jhdr)) < 0)
			goto protocol_error;
		if (!pskb_pull(jumbo, sizeof(jhdr)))
			BUG();

		sp->hdr.seq	= htonl(ntohl(sp->hdr.seq) + 1);
		sp->hdr.serial	= htonl(ntohl(sp->hdr.serial) + 1);
		sp->hdr.flags	= jhdr.flags;
		sp->hdr._rsvd	= jhdr._rsvd;

		_proto("Rx DATA Jumbo %%%u", ntohl(sp->hdr.serial) - 1);

		rxrpc_fast_process_packet(call, part);
		part = NULL;

	} while (sp->hdr.flags & RXRPC_JUMBO_PACKET);

	rxrpc_fast_process_packet(call, jumbo);
	_leave("");
	return;

protocol_error:
	_debug("protocol error");
	rxrpc_free_skb(part);
	rxrpc_free_skb(jumbo);
	write_lock_bh(&call->state_lock);
	if (call->state <= RXRPC_CALL_COMPLETE) {
		call->state = RXRPC_CALL_LOCALLY_ABORTED;
		call->abort_code = RX_PROTOCOL_ERROR;
		set_bit(RXRPC_CALL_ABORT, &call->events);
		rxrpc_queue_call(call);
	}
	write_unlock_bh(&call->state_lock);
	_leave("");
}