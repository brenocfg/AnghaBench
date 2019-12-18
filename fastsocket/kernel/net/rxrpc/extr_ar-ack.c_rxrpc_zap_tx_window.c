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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq; } ;
struct rxrpc_skb_priv {TYPE_1__ hdr; } ;
struct rxrpc_call {int acks_winsz; unsigned long* acks_window; int acks_tail; int /*<<< orphan*/  acks_head; } ;

/* Variables and functions */
 scalar_t__ CIRC_CNT (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_free_skb (struct sk_buff*) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_read_barrier_depends () ; 

__attribute__((used)) static void rxrpc_zap_tx_window(struct rxrpc_call *call)
{
	struct rxrpc_skb_priv *sp;
	struct sk_buff *skb;
	unsigned long _skb, *acks_window;
	u8 winsz = call->acks_winsz;
	int tail;

	acks_window = call->acks_window;
	call->acks_window = NULL;

	while (CIRC_CNT(call->acks_head, call->acks_tail, winsz) > 0) {
		tail = call->acks_tail;
		smp_read_barrier_depends();
		_skb = acks_window[tail] & ~1;
		smp_mb();
		call->acks_tail = (call->acks_tail + 1) & (winsz - 1);

		skb = (struct sk_buff *) _skb;
		sp = rxrpc_skb(skb);
		_debug("+++ clear Tx %u", ntohl(sp->hdr.seq));
		rxrpc_free_skb(skb);
	}

	kfree(acks_window);
}