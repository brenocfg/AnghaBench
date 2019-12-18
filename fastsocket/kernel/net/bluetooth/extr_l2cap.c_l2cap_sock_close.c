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
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  __l2cap_sock_close (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_sock_clear_timer (struct sock*) ; 
 int /*<<< orphan*/  l2cap_sock_kill (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static void l2cap_sock_close(struct sock *sk)
{
	l2cap_sock_clear_timer(sk);
	lock_sock(sk);
	__l2cap_sock_close(sk, ECONNRESET);
	release_sock(sk);
	l2cap_sock_kill(sk);
}