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
struct sock {scalar_t__ sk_type; scalar_t__ sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct l2cap_chan_list {int /*<<< orphan*/  lock; struct sock* head; } ;
struct l2cap_conn {struct l2cap_chan_list chan_list; } ;
struct TYPE_2__ {struct sock* next_c; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECT ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_conn*) ; 
 scalar_t__ SOCK_SEQPACKET ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  l2cap_do_start (struct sock*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_sock_clear_timer (struct sock*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void l2cap_conn_ready(struct l2cap_conn *conn)
{
	struct l2cap_chan_list *l = &conn->chan_list;
	struct sock *sk;

	BT_DBG("conn %p", conn);

	read_lock(&l->lock);

	for (sk = l->head; sk; sk = l2cap_pi(sk)->next_c) {
		bh_lock_sock(sk);

		if (sk->sk_type != SOCK_SEQPACKET) {
			l2cap_sock_clear_timer(sk);
			sk->sk_state = BT_CONNECTED;
			sk->sk_state_change(sk);
		} else if (sk->sk_state == BT_CONNECT)
			l2cap_do_start(sk);

		bh_unlock_sock(sk);
	}

	read_unlock(&l->lock);
}