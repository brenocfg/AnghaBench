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
struct sock {int sk_err; scalar_t__ sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  (* sk_data_ready ) (struct sock*,int /*<<< orphan*/ ) ;} ;
struct rfcomm_dlc {scalar_t__ state; int /*<<< orphan*/  session; struct sock* owner; } ;
struct TYPE_2__ {int /*<<< orphan*/  src; struct sock* parent; } ;

/* Variables and functions */
 scalar_t__ BT_CLOSED ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,scalar_t__,int) ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  bt_accept_unlink (struct sock*) ; 
 TYPE_1__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_session_getaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_sock_kill (struct sock*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 

__attribute__((used)) static void rfcomm_sk_state_change(struct rfcomm_dlc *d, int err)
{
	struct sock *sk = d->owner, *parent;
	if (!sk)
		return;

	BT_DBG("dlc %p state %ld err %d", d, d->state, err);

	bh_lock_sock(sk);

	if (err)
		sk->sk_err = err;

	sk->sk_state = d->state;

	parent = bt_sk(sk)->parent;
	if (parent) {
		if (d->state == BT_CLOSED) {
			sock_set_flag(sk, SOCK_ZAPPED);
			bt_accept_unlink(sk);
		}
		parent->sk_data_ready(parent, 0);
	} else {
		if (d->state == BT_CONNECTED)
			rfcomm_session_getaddr(d->session, &bt_sk(sk)->src, NULL);
		sk->sk_state_change(sk);
	}

	bh_unlock_sock(sk);

	if (parent && sock_flag(sk, SOCK_ZAPPED)) {
		/* We have to drop DLC lock here, otherwise
		 * rfcomm_sock_destruct() will dead lock. */
		rfcomm_dlc_unlock(d);
		rfcomm_sock_kill(sk);
		rfcomm_dlc_lock(d);
	}
}