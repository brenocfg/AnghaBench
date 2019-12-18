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
struct rxrpc_call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,unsigned long) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_call*) ; 
 struct rxrpc_call* rxrpc_accept_call (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  rxrpc_sk (int /*<<< orphan*/ ) ; 

struct rxrpc_call *rxrpc_kernel_accept_call(struct socket *sock,
					    unsigned long user_call_ID)
{
	struct rxrpc_call *call;

	_enter(",%lx", user_call_ID);
	call = rxrpc_accept_call(rxrpc_sk(sock->sk), user_call_ID);
	_leave(" = %p", call);
	return call;
}