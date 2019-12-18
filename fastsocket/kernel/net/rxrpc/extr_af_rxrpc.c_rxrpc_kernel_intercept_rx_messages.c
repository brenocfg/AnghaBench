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
struct socket {int /*<<< orphan*/  sk; } ;
struct rxrpc_sock {int /*<<< orphan*/  interceptor; } ;
typedef  int /*<<< orphan*/  rxrpc_interceptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*) ; 
 struct rxrpc_sock* rxrpc_sk (int /*<<< orphan*/ ) ; 

void rxrpc_kernel_intercept_rx_messages(struct socket *sock,
					rxrpc_interceptor_t interceptor)
{
	struct rxrpc_sock *rx = rxrpc_sk(sock->sk);

	_enter("");
	rx->interceptor = interceptor;
}