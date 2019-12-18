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
struct sk_buff {scalar_t__ sk; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct rxrpc_skb_priv {struct rxrpc_call* call; TYPE_1__ hdr; } ;
struct rxrpc_call {int dummy; } ;

/* Variables and functions */
 scalar_t__ RXRPC_PACKET_TYPE_DATA ; 
 int /*<<< orphan*/  _enter (char*,struct sk_buff*,struct rxrpc_call*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  rxrpc_hard_ACK_data (struct rxrpc_call*,struct rxrpc_skb_priv*) ; 
 int /*<<< orphan*/  rxrpc_put_call (struct rxrpc_call*) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_rfree (struct sk_buff*) ; 

void rxrpc_packet_destructor(struct sk_buff *skb)
{
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);
	struct rxrpc_call *call = sp->call;

	_enter("%p{%p}", skb, call);

	if (call) {
		/* send the final ACK on a client call */
		if (sp->hdr.type == RXRPC_PACKET_TYPE_DATA)
			rxrpc_hard_ACK_data(call, sp);
		rxrpc_put_call(call);
		sp->call = NULL;
	}

	if (skb->sk)
		sock_rfree(skb);
	_leave("");
}