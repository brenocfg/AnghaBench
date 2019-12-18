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
struct socket {scalar_t__ fasync_list; int /*<<< orphan*/  flags; } ;
struct sock {int sk_shutdown; scalar_t__ sk_sleep; struct socket* sk_socket; } ;

/* Variables and functions */
 int POLLOUT ; 
 int POLLWRBAND ; 
 int POLLWRNORM ; 
 int /*<<< orphan*/  POLL_OUT ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int /*<<< orphan*/  SOCK_WAKE_SPACE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sk_stream_min_wspace (struct sock*) ; 
 scalar_t__ sk_stream_wspace (struct sock*) ; 
 int /*<<< orphan*/  sock_wake_async (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ waitqueue_active (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (scalar_t__,int) ; 

void sk_stream_write_space(struct sock *sk)
{
	struct socket *sock = sk->sk_socket;

	if (sk_stream_wspace(sk) >= sk_stream_min_wspace(sk) && sock) {
		clear_bit(SOCK_NOSPACE, &sock->flags);

		if (sk->sk_sleep && waitqueue_active(sk->sk_sleep))
			wake_up_interruptible_poll(sk->sk_sleep, POLLOUT |
						POLLWRNORM | POLLWRBAND);
		if (sock->fasync_list && !(sk->sk_shutdown & SEND_SHUTDOWN))
			sock_wake_async(sock, SOCK_WAKE_SPACE, POLL_OUT);
	}
}