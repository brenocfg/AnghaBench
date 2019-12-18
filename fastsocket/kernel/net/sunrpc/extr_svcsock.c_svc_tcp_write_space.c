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
struct socket {int /*<<< orphan*/  flags; } ;
struct sock {struct socket* sk_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sk_stream_min_wspace (struct sock*) ; 
 scalar_t__ sk_stream_wspace (struct sock*) ; 
 int /*<<< orphan*/  svc_write_space (struct sock*) ; 

__attribute__((used)) static void svc_tcp_write_space(struct sock *sk)
{
	struct socket *sock = sk->sk_socket;

	if (sk_stream_wspace(sk) >= sk_stream_min_wspace(sk) && sock)
		clear_bit(SOCK_NOSPACE, &sock->flags);
	svc_write_space(sk);
}