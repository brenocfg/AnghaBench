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
struct unix_sock {struct unix_address* addr; } ;
struct unix_address {int len; int /*<<< orphan*/  name; } ;
struct socket {struct sock* sk; } ;
struct sockaddr_un {scalar_t__* sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 struct sock* unix_peer_get (struct sock*) ; 
 struct unix_sock* unix_sk (struct sock*) ; 
 int /*<<< orphan*/  unix_state_lock (struct sock*) ; 
 int /*<<< orphan*/  unix_state_unlock (struct sock*) ; 

__attribute__((used)) static int unix_getname(struct socket *sock, struct sockaddr *uaddr, int *uaddr_len, int peer)
{
	struct sock *sk = sock->sk;
	struct unix_sock *u;
	struct sockaddr_un *sunaddr = (struct sockaddr_un *)uaddr;
	int err = 0;

	if (peer) {
		sk = unix_peer_get(sk);

		err = -ENOTCONN;
		if (!sk)
			goto out;
		err = 0;
	} else {
		sock_hold(sk);
	}

	u = unix_sk(sk);
	unix_state_lock(sk);
	if (!u->addr) {
		sunaddr->sun_family = AF_UNIX;
		sunaddr->sun_path[0] = 0;
		*uaddr_len = sizeof(short);
	} else {
		struct unix_address *addr = u->addr;

		*uaddr_len = addr->len;
		memcpy(sunaddr, addr->name, *uaddr_len);
	}
	unix_state_unlock(sk);
	sock_put(sk);
out:
	return err;
}