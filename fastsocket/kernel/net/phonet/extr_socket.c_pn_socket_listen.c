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
struct socket {scalar_t__ state; struct sock* sk; } ;
struct sock {scalar_t__ sk_state; int sk_max_ack_backlog; scalar_t__ sk_ack_backlog; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 scalar_t__ SS_UNCONNECTED ; 
 scalar_t__ TCP_CLOSE ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 scalar_t__ pn_socket_autobind (struct socket*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int pn_socket_listen(struct socket *sock, int backlog)
{
	struct sock *sk = sock->sk;
	int err = 0;

	if (sock->state != SS_UNCONNECTED)
		return -EINVAL;
	if (pn_socket_autobind(sock))
		return -ENOBUFS;

	lock_sock(sk);
	if (sk->sk_state != TCP_CLOSE) {
		err = -EINVAL;
		goto out;
	}

	sk->sk_state = TCP_LISTEN;
	sk->sk_ack_backlog = 0;
	sk->sk_max_ack_backlog = backlog;
out:
	release_sock(sk);
	return err;
}