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
struct TYPE_5__ {scalar_t__ a6; int /*<<< orphan*/  a4; } ;
typedef  TYPE_2__ xfrm_address_t ;
struct sockaddr_in6 {int sin6_family; int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_flowinfo; void* sin6_port; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_family; int /*<<< orphan*/  sin_zero; TYPE_1__ sin_addr; void* sin_port; } ;
struct sockaddr {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  void* __be16 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,struct in6_addr*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int pfkey_sockaddr_fill(xfrm_address_t *xaddr, __be16 port,
				       struct sockaddr *sa,
				       unsigned short family)
{
	switch (family) {
	case AF_INET:
	    {
		struct sockaddr_in *sin = (struct sockaddr_in *)sa;
		sin->sin_family = AF_INET;
		sin->sin_port = port;
		sin->sin_addr.s_addr = xaddr->a4;
		memset(sin->sin_zero, 0, sizeof(sin->sin_zero));
		return 32;
	    }
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	case AF_INET6:
	    {
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
		sin6->sin6_family = AF_INET6;
		sin6->sin6_port = port;
		sin6->sin6_flowinfo = 0;
		ipv6_addr_copy(&sin6->sin6_addr, (struct in6_addr *)xaddr->a6);
		sin6->sin6_scope_id = 0;
		return 128;
	    }
#endif
	}
	return 0;
}