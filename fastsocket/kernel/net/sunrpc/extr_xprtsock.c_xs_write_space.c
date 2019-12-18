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
struct rpc_xprt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct rpc_xprt* xprt_from_sock (struct sock*) ; 
 int /*<<< orphan*/  xprt_write_space (struct rpc_xprt*) ; 

__attribute__((used)) static void xs_write_space(struct sock *sk)
{
	struct socket *sock;
	struct rpc_xprt *xprt;

	if (unlikely(!(sock = sk->sk_socket)))
		return;
	clear_bit(SOCK_NOSPACE, &sock->flags);

	if (unlikely(!(xprt = xprt_from_sock(sk))))
		return;
	if (test_and_clear_bit(SOCK_ASYNC_NOSPACE, &sock->flags) == 0)
		return;

	xprt_write_space(xprt);
}