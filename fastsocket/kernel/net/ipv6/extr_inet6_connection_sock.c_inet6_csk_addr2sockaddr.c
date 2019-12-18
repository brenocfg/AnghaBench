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
struct sockaddr_in6 {scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_flowinfo; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_bound_dev_if; } ;
struct ipv6_pinfo {int /*<<< orphan*/  daddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dport; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int IPV6_ADDR_LINKLOCAL ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 

void inet6_csk_addr2sockaddr(struct sock *sk, struct sockaddr * uaddr)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *) uaddr;

	sin6->sin6_family = AF_INET6;
	ipv6_addr_copy(&sin6->sin6_addr, &np->daddr);
	sin6->sin6_port	= inet_sk(sk)->dport;
	/* We do not store received flowlabel for TCP */
	sin6->sin6_flowinfo = 0;
	sin6->sin6_scope_id = 0;
	if (sk->sk_bound_dev_if &&
	    ipv6_addr_type(&sin6->sin6_addr) & IPV6_ADDR_LINKLOCAL)
		sin6->sin6_scope_id = sk->sk_bound_dev_if;
}