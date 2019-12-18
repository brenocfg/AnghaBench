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
struct sock {int sk_socket; int /*<<< orphan*/  sk_wmem_alloc; int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _enter (char*,struct sock*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,struct sock*) ; 
 int /*<<< orphan*/  rxrpc_purge_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_unhashed (struct sock*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxrpc_sock_destructor(struct sock *sk)
{
	_enter("%p", sk);

	rxrpc_purge_queue(&sk->sk_receive_queue);

	WARN_ON(atomic_read(&sk->sk_wmem_alloc));
	WARN_ON(!sk_unhashed(sk));
	WARN_ON(sk->sk_socket);

	if (!sock_flag(sk, SOCK_DEAD)) {
		printk("Attempt to release alive rxrpc socket: %p\n", sk);
		return;
	}
}