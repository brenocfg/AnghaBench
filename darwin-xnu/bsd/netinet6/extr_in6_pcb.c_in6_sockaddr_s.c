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
struct in6_addr {scalar_t__* s6_addr16; } ;
struct sockaddr_in6 {int sin6_len; struct in6_addr sin6_addr; scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
typedef  int /*<<< orphan*/  in_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ IN6_IS_SCOPE_LINKLOCAL (struct in6_addr*) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 scalar_t__ ntohs (scalar_t__) ; 

void
in6_sockaddr_s(in_port_t port, struct in6_addr *addr_p,
    struct sockaddr_in6 *sin6)
{
	bzero(sin6, sizeof (*sin6));
	sin6->sin6_family = AF_INET6;
	sin6->sin6_len = sizeof (*sin6);
	sin6->sin6_port = port;
	sin6->sin6_addr = *addr_p;

	/* would be good to use sa6_recoverscope(), except for locking  */
	if (IN6_IS_SCOPE_LINKLOCAL(&sin6->sin6_addr))
		sin6->sin6_scope_id = ntohs(sin6->sin6_addr.s6_addr16[1]);
	else
		sin6->sin6_scope_id = 0;	/* XXX */
	if (IN6_IS_SCOPE_LINKLOCAL(&sin6->sin6_addr))
		sin6->sin6_addr.s6_addr16[1] = 0;
}