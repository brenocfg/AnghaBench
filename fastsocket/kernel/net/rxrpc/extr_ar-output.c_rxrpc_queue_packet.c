#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  seq; int /*<<< orphan*/  serial; } ;
struct rxrpc_skb_priv {int need_resend; scalar_t__ resend_at; TYPE_1__ hdr; } ;
struct TYPE_6__ {scalar_t__ expires; } ;
struct rxrpc_call {size_t acks_head; unsigned long* acks_window; int acks_winsz; int state; TYPE_2__* conn; int /*<<< orphan*/  ack_timer; TYPE_3__ resend_timer; int /*<<< orphan*/  flags; int /*<<< orphan*/  state_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int HZ ; 
 int RXRPC_CALL_CLIENT_AWAIT_REPLY ; 
#define  RXRPC_CALL_CLIENT_SEND_REQUEST 130 
 int /*<<< orphan*/  RXRPC_CALL_RUN_RTIMER ; 
#define  RXRPC_CALL_SERVER_ACK_REQUEST 129 
 int RXRPC_CALL_SERVER_AWAIT_ACK ; 
#define  RXRPC_CALL_SERVER_SEND_REPLY 128 
 int /*<<< orphan*/  _debug (char*,...) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  _net (char*,struct sk_buff*,...) ; 
 int /*<<< orphan*/  _proto (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_instant_resend (struct rxrpc_call*) ; 
 int rxrpc_resend_timeout ; 
 int rxrpc_send_packet (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ try_to_del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_queue_packet(struct rxrpc_call *call, struct sk_buff *skb,
			       bool last)
{
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);
	int ret;

	_net("queue skb %p [%d]", skb, call->acks_head);

	ASSERT(call->acks_window != NULL);
	call->acks_window[call->acks_head] = (unsigned long) skb;
	smp_wmb();
	call->acks_head = (call->acks_head + 1) & (call->acks_winsz - 1);

	if (last || call->state == RXRPC_CALL_SERVER_ACK_REQUEST) {
		_debug("________awaiting reply/ACK__________");
		write_lock_bh(&call->state_lock);
		switch (call->state) {
		case RXRPC_CALL_CLIENT_SEND_REQUEST:
			call->state = RXRPC_CALL_CLIENT_AWAIT_REPLY;
			break;
		case RXRPC_CALL_SERVER_ACK_REQUEST:
			call->state = RXRPC_CALL_SERVER_SEND_REPLY;
			if (!last)
				break;
		case RXRPC_CALL_SERVER_SEND_REPLY:
			call->state = RXRPC_CALL_SERVER_AWAIT_ACK;
			break;
		default:
			break;
		}
		write_unlock_bh(&call->state_lock);
	}

	_proto("Tx DATA %%%u { #%u }",
	       ntohl(sp->hdr.serial), ntohl(sp->hdr.seq));

	sp->need_resend = 0;
	sp->resend_at = jiffies + rxrpc_resend_timeout * HZ;
	if (!test_and_set_bit(RXRPC_CALL_RUN_RTIMER, &call->flags)) {
		_debug("run timer");
		call->resend_timer.expires = sp->resend_at;
		add_timer(&call->resend_timer);
	}

	/* attempt to cancel the rx-ACK timer, deferring reply transmission if
	 * we're ACK'ing the request phase of an incoming call */
	ret = -EAGAIN;
	if (try_to_del_timer_sync(&call->ack_timer) >= 0) {
		/* the packet may be freed by rxrpc_process_call() before this
		 * returns */
		ret = rxrpc_send_packet(call->conn->trans, skb);
		_net("sent skb %p", skb);
	} else {
		_debug("failed to delete ACK timer");
	}

	if (ret < 0) {
		_debug("need instant resend %d", ret);
		sp->need_resend = 1;
		rxrpc_instant_resend(call);
	}

	_leave("");
}