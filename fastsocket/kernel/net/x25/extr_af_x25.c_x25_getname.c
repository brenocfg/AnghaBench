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
struct x25_sock {int /*<<< orphan*/  source_addr; int /*<<< orphan*/  dest_addr; } ;
struct socket {struct sock* sk; } ;
struct sockaddr_x25 {int /*<<< orphan*/  sx25_family; int /*<<< orphan*/  sx25_addr; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_X25 ; 
 int ENOTCONN ; 
 scalar_t__ TCP_ESTABLISHED ; 
 struct x25_sock* x25_sk (struct sock*) ; 

__attribute__((used)) static int x25_getname(struct socket *sock, struct sockaddr *uaddr,
		       int *uaddr_len, int peer)
{
	struct sockaddr_x25 *sx25 = (struct sockaddr_x25 *)uaddr;
	struct sock *sk = sock->sk;
	struct x25_sock *x25 = x25_sk(sk);

	if (peer) {
		if (sk->sk_state != TCP_ESTABLISHED)
			return -ENOTCONN;
		sx25->sx25_addr = x25->dest_addr;
	} else
		sx25->sx25_addr = x25->source_addr;

	sx25->sx25_family = AF_X25;
	*uaddr_len = sizeof(*sx25);

	return 0;
}