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

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int rxrpc_reject_call (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_sk (int /*<<< orphan*/ ) ; 

int rxrpc_kernel_reject_call(struct socket *sock)
{
	int ret;

	_enter("");
	ret = rxrpc_reject_call(rxrpc_sk(sock->sk));
	_leave(" = %d", ret);
	return ret;
}