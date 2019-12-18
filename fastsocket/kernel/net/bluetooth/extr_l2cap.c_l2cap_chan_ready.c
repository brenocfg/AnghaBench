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
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_state; } ;
struct TYPE_4__ {struct sock* parent; } ;
struct TYPE_3__ {scalar_t__ conf_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,struct sock*) ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_sock_clear_timer (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_chan_ready(struct sock *sk)
{
	struct sock *parent = bt_sk(sk)->parent;

	BT_DBG("sk %p, parent %p", sk, parent);

	l2cap_pi(sk)->conf_state = 0;
	l2cap_sock_clear_timer(sk);

	if (!parent) {
		/* Outgoing channel.
		 * Wake up socket sleeping on connect.
		 */
		sk->sk_state = BT_CONNECTED;
		sk->sk_state_change(sk);
	} else {
		/* Incoming channel.
		 * Wake up socket sleeping on accept.
		 */
		parent->sk_data_ready(parent, 0);
	}
}