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
struct socket {scalar_t__ state; struct sock* sk; } ;
struct sock {int sk_shutdown; } ;
struct dn_scp {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ DN_O ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 int EINVAL ; 
 int ENOTCONN ; 
 int SHUTDOWN_MASK ; 
 scalar_t__ SS_DISCONNECTING ; 
 scalar_t__ SS_UNCONNECTED ; 
 int /*<<< orphan*/  dn_destroy_sock (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int dn_shutdown(struct socket *sock, int how)
{
	struct sock *sk = sock->sk;
	struct dn_scp *scp = DN_SK(sk);
	int err = -ENOTCONN;

	lock_sock(sk);

	if (sock->state == SS_UNCONNECTED)
		goto out;

	err = 0;
	if (sock->state == SS_DISCONNECTING)
		goto out;

	err = -EINVAL;
	if (scp->state == DN_O)
		goto out;

	if (how != SHUTDOWN_MASK)
		goto out;

	sk->sk_shutdown = how;
	dn_destroy_sock(sk);
	err = 0;

out:
	release_sock(sk);

	return err;
}