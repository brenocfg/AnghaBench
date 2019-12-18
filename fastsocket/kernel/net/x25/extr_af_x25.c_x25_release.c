#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct x25_sock {int state; } ;
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_shutdown; int /*<<< orphan*/  sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  SOCK_DESTROY ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 int /*<<< orphan*/  X25_CLEAR_REQUEST ; 
#define  X25_STATE_0 132 
#define  X25_STATE_1 131 
#define  X25_STATE_2 130 
#define  X25_STATE_3 129 
#define  X25_STATE_4 128 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  x25_clear_queues (struct sock*) ; 
 int /*<<< orphan*/  x25_destroy_socket (struct sock*) ; 
 int /*<<< orphan*/  x25_disconnect (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct x25_sock* x25_sk (struct sock*) ; 
 int /*<<< orphan*/  x25_start_t23timer (struct sock*) ; 
 int /*<<< orphan*/  x25_write_internal (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int x25_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct x25_sock *x25;

	if (!sk)
		goto out;

	x25 = x25_sk(sk);

	switch (x25->state) {

		case X25_STATE_0:
		case X25_STATE_2:
			x25_disconnect(sk, 0, 0, 0);
			x25_destroy_socket(sk);
			goto out;

		case X25_STATE_1:
		case X25_STATE_3:
		case X25_STATE_4:
			x25_clear_queues(sk);
			x25_write_internal(sk, X25_CLEAR_REQUEST);
			x25_start_t23timer(sk);
			x25->state = X25_STATE_2;
			sk->sk_state	= TCP_CLOSE;
			sk->sk_shutdown	|= SEND_SHUTDOWN;
			sk->sk_state_change(sk);
			sock_set_flag(sk, SOCK_DEAD);
			sock_set_flag(sk, SOCK_DESTROY);
			break;
	}

	sock_orphan(sk);
out:
	return 0;
}