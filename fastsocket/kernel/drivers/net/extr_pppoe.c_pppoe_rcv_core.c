#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_state; } ;
struct sk_buff {int dummy; } ;
struct pppox_sock {int /*<<< orphan*/  pppoe_relay; int /*<<< orphan*/  chan; } ;
struct TYPE_4__ {int sk_state; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int PPPOX_BOUND ; 
 int PPPOX_CONNECTED ; 
 int PPPOX_RELAY ; 
 int /*<<< orphan*/  __pppoe_xmit (TYPE_1__*,struct sk_buff*) ; 
 struct pppox_sock* get_item_by_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ppp_input (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct pppox_sock* pppox_sk (struct sock*) ; 
 TYPE_1__* sk_pppox (struct pppox_sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_put (TYPE_1__*) ; 
 scalar_t__ sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static int pppoe_rcv_core(struct sock *sk, struct sk_buff *skb)
{
	struct pppox_sock *po = pppox_sk(sk);
	struct pppox_sock *relay_po;

	/* Backlog receive. Semantics of backlog rcv preclude any code from
	 * executing in lock_sock()/release_sock() bounds; meaning sk->sk_state
	 * can't change.
	 */

	if (sk->sk_state & PPPOX_BOUND) {
		ppp_input(&po->chan, skb);
	} else if (sk->sk_state & PPPOX_RELAY) {
		relay_po = get_item_by_addr(sock_net(sk),
					    &po->pppoe_relay);
		if (relay_po == NULL)
			goto abort_kfree;

		if ((sk_pppox(relay_po)->sk_state & PPPOX_CONNECTED) == 0)
			goto abort_put;

		if (!__pppoe_xmit(sk_pppox(relay_po), skb))
			goto abort_put;
	} else {
		if (sock_queue_rcv_skb(sk, skb))
			goto abort_kfree;
	}

	return NET_RX_SUCCESS;

abort_put:
	sock_put(sk_pppox(relay_po));

abort_kfree:
	kfree_skb(skb);
	return NET_RX_DROP;
}