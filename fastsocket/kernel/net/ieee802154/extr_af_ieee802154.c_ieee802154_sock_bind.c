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
struct sockaddr {int dummy; } ;
struct sock {TYPE_1__* sk_prot; } ;
struct TYPE_2__ {int (* bind ) (struct sock*,struct sockaddr*,int) ;} ;

/* Variables and functions */
 int sock_no_bind (struct socket*,struct sockaddr*,int) ; 
 int stub1 (struct sock*,struct sockaddr*,int) ; 

__attribute__((used)) static int ieee802154_sock_bind(struct socket *sock, struct sockaddr *uaddr,
		int addr_len)
{
	struct sock *sk = sock->sk;

	if (sk->sk_prot->bind)
		return sk->sk_prot->bind(sk, uaddr, addr_len);

	return sock_no_bind(sock, uaddr, addr_len);
}