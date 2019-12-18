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
struct socket {struct sock* sk; } ;
struct sock {int sk_route_caps; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int NETIF_F_ALL_CSUM ; 
 int NETIF_F_SG ; 
 int /*<<< orphan*/  TCP_CHECK_TIMER (struct sock*) ; 
 int /*<<< orphan*/  do_tcp_sendpages (struct sock*,struct page**,int,size_t,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_no_sendpage (struct socket*,struct page*,int,size_t,int) ; 

ssize_t tcp_sendpage(struct socket *sock, struct page *page, int offset,
		     size_t size, int flags)
{
	ssize_t res;
	struct sock *sk = sock->sk;

	if (!(sk->sk_route_caps & NETIF_F_SG) ||
	    !(sk->sk_route_caps & NETIF_F_ALL_CSUM))
		return sock_no_sendpage(sock, page, offset, size, flags);

	lock_sock(sk);
	TCP_CHECK_TIMER(sk);
	res = do_tcp_sendpages(sk, &page, offset, size, flags);
	TCP_CHECK_TIMER(sk);
	release_sock(sk);
	return res;
}