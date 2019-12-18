#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sock {int sk_max_ack_backlog; } ;
struct TYPE_3__ {int sk_state; } ;
struct rxrpc_sock {TYPE_1__ sk; int /*<<< orphan*/ * local; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EADDRNOTAVAIL ; 
 int EBUSY ; 
#define  RXRPC_CLIENT_BOUND 131 
#define  RXRPC_CLIENT_CONNECTED 130 
#define  RXRPC_SERVER_BOUND 129 
 int RXRPC_SERVER_LISTENING ; 
#define  RXRPC_UNCONNECTED 128 
 int /*<<< orphan*/  _enter (char*,struct rxrpc_sock*,int) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  lock_sock (TYPE_1__*) ; 
 int /*<<< orphan*/  release_sock (TYPE_1__*) ; 
 struct rxrpc_sock* rxrpc_sk (struct sock*) ; 

__attribute__((used)) static int rxrpc_listen(struct socket *sock, int backlog)
{
	struct sock *sk = sock->sk;
	struct rxrpc_sock *rx = rxrpc_sk(sk);
	int ret;

	_enter("%p,%d", rx, backlog);

	lock_sock(&rx->sk);

	switch (rx->sk.sk_state) {
	case RXRPC_UNCONNECTED:
		ret = -EADDRNOTAVAIL;
		break;
	case RXRPC_CLIENT_BOUND:
	case RXRPC_CLIENT_CONNECTED:
	default:
		ret = -EBUSY;
		break;
	case RXRPC_SERVER_BOUND:
		ASSERT(rx->local != NULL);
		sk->sk_max_ack_backlog = backlog;
		rx->sk.sk_state = RXRPC_SERVER_LISTENING;
		ret = 0;
		break;
	}

	release_sock(&rx->sk);
	_leave(" = %d", ret);
	return ret;
}