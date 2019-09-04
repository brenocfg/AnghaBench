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
struct sockaddr_in6 {int sin6_len; struct in6_addr sin6_addr; int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
union sockaddr_in_4_6 {struct sockaddr_in6 sin6; } ;
typedef  int /*<<< orphan*/  u_int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ IN6_IS_SCOPE_EMBED (struct in6_addr*) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 

__attribute__((used)) static void
fill_ip6_sockaddr_4_6(union sockaddr_in_4_6 *sin46,
	struct in6_addr *ip6, u_int16_t port)
{
	struct sockaddr_in6 *sin6 = &sin46->sin6;

	sin6->sin6_family = AF_INET6;
	sin6->sin6_len = sizeof(*sin6);
	sin6->sin6_port = port;
	sin6->sin6_addr = *ip6;
	if (IN6_IS_SCOPE_EMBED(&sin6->sin6_addr)) {
		sin6->sin6_scope_id = ntohs(sin6->sin6_addr.s6_addr16[1]);
		sin6->sin6_addr.s6_addr16[1] = 0;
	}
}