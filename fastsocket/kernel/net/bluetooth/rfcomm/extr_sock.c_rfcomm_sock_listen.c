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
typedef  int u8 ;
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; scalar_t__ sk_type; int sk_max_ack_backlog; scalar_t__ sk_ack_backlog; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  src; } ;
struct TYPE_5__ {int channel; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ BT_BOUND ; 
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int) ; 
 scalar_t__ BT_LISTEN ; 
 int EBADFD ; 
 int EINVAL ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  __rfcomm_get_sock_by_addr (int,int /*<<< orphan*/ *) ; 
 TYPE_3__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 TYPE_2__* rfcomm_pi (struct sock*) ; 
 TYPE_1__ rfcomm_sk_list ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rfcomm_sock_listen(struct socket *sock, int backlog)
{
	struct sock *sk = sock->sk;
	int err = 0;

	BT_DBG("sk %p backlog %d", sk, backlog);

	lock_sock(sk);

	if (sk->sk_state != BT_BOUND) {
		err = -EBADFD;
		goto done;
	}

	if (sk->sk_type != SOCK_STREAM) {
		err = -EINVAL;
		goto done;
	}

	if (!rfcomm_pi(sk)->channel) {
		bdaddr_t *src = &bt_sk(sk)->src;
		u8 channel;

		err = -EINVAL;

		write_lock_bh(&rfcomm_sk_list.lock);

		for (channel = 1; channel < 31; channel++)
			if (!__rfcomm_get_sock_by_addr(channel, src)) {
				rfcomm_pi(sk)->channel = channel;
				err = 0;
				break;
			}

		write_unlock_bh(&rfcomm_sk_list.lock);

		if (err < 0)
			goto done;
	}

	sk->sk_max_ack_backlog = backlog;
	sk->sk_ack_backlog = 0;
	sk->sk_state = BT_LISTEN;

done:
	release_sock(sk);
	return err;
}