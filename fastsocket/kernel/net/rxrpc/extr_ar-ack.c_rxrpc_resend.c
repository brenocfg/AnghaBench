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
typedef  int u8 ;
struct sk_buff {scalar_t__ head; } ;
struct TYPE_3__ {int /*<<< orphan*/  seq; int /*<<< orphan*/  serial; } ;
struct rxrpc_skb_priv {int need_resend; unsigned long resend_at; TYPE_1__ hdr; } ;
struct rxrpc_header {int /*<<< orphan*/  serial; } ;
struct rxrpc_call {int acks_head; int acks_tail; int acks_winsz; unsigned long* acks_window; TYPE_2__* conn; int /*<<< orphan*/  sequence; int /*<<< orphan*/  acks_unacked; int /*<<< orphan*/  acks_hard; } ;
struct TYPE_4__ {int /*<<< orphan*/  trans; int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRC_CNT (int,int,int) ; 
 int HZ ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  _proto (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int rxrpc_resend_timeout ; 
 scalar_t__ rxrpc_send_packet (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_set_resend (struct rxrpc_call*,int,unsigned long) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_read_barrier_depends () ; 
 scalar_t__ time_after_eq (void*,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void rxrpc_resend(struct rxrpc_call *call)
{
	struct rxrpc_skb_priv *sp;
	struct rxrpc_header *hdr;
	struct sk_buff *txb;
	unsigned long *p_txb, resend_at;
	int loop, stop;
	u8 resend;

	_enter("{%d,%d,%d,%d},",
	       call->acks_hard, call->acks_unacked,
	       atomic_read(&call->sequence),
	       CIRC_CNT(call->acks_head, call->acks_tail, call->acks_winsz));

	stop = 0;
	resend = 0;
	resend_at = 0;

	for (loop = call->acks_tail;
	     loop != call->acks_head || stop;
	     loop = (loop + 1) &  (call->acks_winsz - 1)
	     ) {
		p_txb = call->acks_window + loop;
		smp_read_barrier_depends();
		if (*p_txb & 1)
			continue;

		txb = (struct sk_buff *) *p_txb;
		sp = rxrpc_skb(txb);

		if (sp->need_resend) {
			sp->need_resend = 0;

			/* each Tx packet has a new serial number */
			sp->hdr.serial =
				htonl(atomic_inc_return(&call->conn->serial));

			hdr = (struct rxrpc_header *) txb->head;
			hdr->serial = sp->hdr.serial;

			_proto("Tx DATA %%%u { #%d }",
			       ntohl(sp->hdr.serial), ntohl(sp->hdr.seq));
			if (rxrpc_send_packet(call->conn->trans, txb) < 0) {
				stop = 0;
				sp->resend_at = jiffies + 3;
			} else {
				sp->resend_at =
					jiffies + rxrpc_resend_timeout * HZ;
			}
		}

		if (time_after_eq(jiffies + 1, sp->resend_at)) {
			sp->need_resend = 1;
			resend |= 1;
		} else if (resend & 2) {
			if (time_before(sp->resend_at, resend_at))
				resend_at = sp->resend_at;
		} else {
			resend_at = sp->resend_at;
			resend |= 2;
		}
	}

	rxrpc_set_resend(call, resend, resend_at);
	_leave("");
}