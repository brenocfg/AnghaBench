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
struct sock {int /*<<< orphan*/ * sk_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  release_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_net_set (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  sock_release (int /*<<< orphan*/ *) ; 

void sk_release_kernel(struct sock *sk)
{
	if (sk == NULL || sk->sk_socket == NULL)
		return;

	sock_hold(sk);
	sock_release(sk->sk_socket);
	release_net(sock_net(sk));
	sock_net_set(sk, get_net(&init_net));
	sock_put(sk);
}