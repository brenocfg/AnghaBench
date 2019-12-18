#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sockaddr_x25 {scalar_t__ sx25_family; int /*<<< orphan*/  sx25_addr; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  source_addr; } ;

/* Variables and functions */
 scalar_t__ AF_X25 ; 
 int EINVAL ; 
 int /*<<< orphan*/  SOCK_DEBUG (struct sock*,char*) ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x25_insert_socket (struct sock*) ; 
 TYPE_1__* x25_sk (struct sock*) ; 

__attribute__((used)) static int x25_bind(struct socket *sock, struct sockaddr *uaddr, int addr_len)
{
	struct sock *sk = sock->sk;
	struct sockaddr_x25 *addr = (struct sockaddr_x25 *)uaddr;

	if (!sock_flag(sk, SOCK_ZAPPED) ||
	    addr_len != sizeof(struct sockaddr_x25) ||
	    addr->sx25_family != AF_X25)
		return -EINVAL;

	x25_sk(sk)->source_addr = addr->sx25_addr;
	x25_insert_socket(sk);
	sock_reset_flag(sk, SOCK_ZAPPED);
	SOCK_DEBUG(sk, "x25_bind: socket is bound\n");

	return 0;
}