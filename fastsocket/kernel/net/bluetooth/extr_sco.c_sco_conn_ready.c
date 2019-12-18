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
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*,int) ;void* sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct sco_conn {int /*<<< orphan*/  hcon; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; struct sock* sk; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTPROTO_SCO ; 
 void* BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct sco_conn*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  __sco_chan_add (struct sco_conn*,struct sock*,struct sock*) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 TYPE_1__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  hci_conn_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sco_conn_lock (struct sco_conn*) ; 
 int /*<<< orphan*/  sco_conn_unlock (struct sco_conn*) ; 
 struct sock* sco_get_sock_listen (int /*<<< orphan*/ ) ; 
 struct sock* sco_sock_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sco_sock_clear_timer (struct sock*) ; 
 int /*<<< orphan*/  sco_sock_init (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*,int) ; 

__attribute__((used)) static void sco_conn_ready(struct sco_conn *conn)
{
	struct sock *parent, *sk;

	BT_DBG("conn %p", conn);

	sco_conn_lock(conn);

	if ((sk = conn->sk)) {
		sco_sock_clear_timer(sk);
		bh_lock_sock(sk);
		sk->sk_state = BT_CONNECTED;
		sk->sk_state_change(sk);
		bh_unlock_sock(sk);
	} else {
		parent = sco_get_sock_listen(conn->src);
		if (!parent)
			goto done;

		bh_lock_sock(parent);

		sk = sco_sock_alloc(sock_net(parent), NULL, BTPROTO_SCO, GFP_ATOMIC);
		if (!sk) {
			bh_unlock_sock(parent);
			goto done;
		}

		sco_sock_init(sk, parent);

		bacpy(&bt_sk(sk)->src, conn->src);
		bacpy(&bt_sk(sk)->dst, conn->dst);

		hci_conn_hold(conn->hcon);
		__sco_chan_add(conn, sk, parent);

		sk->sk_state = BT_CONNECTED;

		/* Wake up parent */
		parent->sk_data_ready(parent, 1);

		bh_unlock_sock(parent);
	}

done:
	sco_conn_unlock(conn);
}