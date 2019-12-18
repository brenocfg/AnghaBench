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
struct sockaddr_dn {int dummy; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct dn_scp {scalar_t__ accept_mode; int /*<<< orphan*/  addr; int /*<<< orphan*/  peer; } ;

/* Variables and functions */
 scalar_t__ ACC_IMMED ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 int ENOTCONN ; 
 scalar_t__ SS_CONNECTED ; 
 scalar_t__ SS_CONNECTING ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_dn*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int dn_getname(struct socket *sock, struct sockaddr *uaddr,int *uaddr_len,int peer)
{
	struct sockaddr_dn *sa = (struct sockaddr_dn *)uaddr;
	struct sock *sk = sock->sk;
	struct dn_scp *scp = DN_SK(sk);

	*uaddr_len = sizeof(struct sockaddr_dn);

	lock_sock(sk);

	if (peer) {
		if ((sock->state != SS_CONNECTED &&
		     sock->state != SS_CONNECTING) &&
		    scp->accept_mode == ACC_IMMED) {
			release_sock(sk);
			return -ENOTCONN;
		}

		memcpy(sa, &scp->peer, sizeof(struct sockaddr_dn));
	} else {
		memcpy(sa, &scp->addr, sizeof(struct sockaddr_dn));
	}

	release_sock(sk);

	return 0;
}