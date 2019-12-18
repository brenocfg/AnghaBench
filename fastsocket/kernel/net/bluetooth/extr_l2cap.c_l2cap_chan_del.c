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
struct sock {int sk_err; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  (* sk_data_ready ) (struct sock*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sk_state; } ;
struct l2cap_conn {int /*<<< orphan*/  hcon; int /*<<< orphan*/  chan_list; } ;
struct TYPE_4__ {struct sock* parent; } ;
struct TYPE_3__ {struct l2cap_conn* conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CLOSED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,struct l2cap_conn*,int) ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  bt_accept_unlink (struct sock*) ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  hci_conn_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_unlink (int /*<<< orphan*/ *,struct sock*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_sock_clear_timer (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 

__attribute__((used)) static void l2cap_chan_del(struct sock *sk, int err)
{
	struct l2cap_conn *conn = l2cap_pi(sk)->conn;
	struct sock *parent = bt_sk(sk)->parent;

	l2cap_sock_clear_timer(sk);

	BT_DBG("sk %p, conn %p, err %d", sk, conn, err);

	if (conn) {
		/* Unlink from channel list */
		l2cap_chan_unlink(&conn->chan_list, sk);
		l2cap_pi(sk)->conn = NULL;
		hci_conn_put(conn->hcon);
	}

	sk->sk_state = BT_CLOSED;
	sock_set_flag(sk, SOCK_ZAPPED);

	if (err)
		sk->sk_err = err;

	if (parent) {
		bt_accept_unlink(sk);
		parent->sk_data_ready(parent, 0);
	} else
		sk->sk_state_change(sk);
}