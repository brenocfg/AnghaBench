#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  a6; int /*<<< orphan*/  a4; } ;
typedef  TYPE_2__ xfrm_address_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
int pfkey_sockaddr_extract(const struct sockaddr *sa, xfrm_address_t *xaddr)
{
	switch (sa->sa_family) {
	case AF_INET:
		xaddr->a4 =
			((struct sockaddr_in *)sa)->sin_addr.s_addr;
		return AF_INET;
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	case AF_INET6:
		memcpy(xaddr->a6,
		       &((struct sockaddr_in6 *)sa)->sin6_addr,
		       sizeof(struct in6_addr));
		return AF_INET6;
#endif
	}
	return 0;
}