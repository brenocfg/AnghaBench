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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr_ib {int /*<<< orphan*/  sib_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_IB 130 
#define  AF_INET 129 
#define  AF_INET6 128 
 int ib_addr_loopback (int /*<<< orphan*/ *) ; 
 int ipv4_is_loopback (int /*<<< orphan*/ ) ; 
 int ipv6_addr_loopback (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int cma_loopback_addr(struct sockaddr *addr)
{
	switch (addr->sa_family) {
	case AF_INET:
		return ipv4_is_loopback(((struct sockaddr_in *) addr)->sin_addr.s_addr);
	case AF_INET6:
		return ipv6_addr_loopback(&((struct sockaddr_in6 *) addr)->sin6_addr);
	case AF_IB:
		return ib_addr_loopback(&((struct sockaddr_ib *) addr)->sib_addr);
	default:
		return 0;
	}
}