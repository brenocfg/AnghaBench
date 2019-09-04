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
typedef  int u_int ;
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {struct in6_addr sin6_addr; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {struct in6_addr addr6; } ;
struct llentry {int la_flags; TYPE_1__ r_l3addr; } ;

/* Variables and functions */
 scalar_t__ IN6_ARE_ADDR_EQUAL (struct in6_addr const*,struct in6_addr const*) ; 
 scalar_t__ IN6_ARE_MASKED_ADDR_EQUAL (struct in6_addr const*,struct in6_addr const*,struct in6_addr const*) ; 
 int LLE_IFADDR ; 
 int LLE_STATIC ; 

__attribute__((used)) static int
in6_lltable_match_prefix(const struct sockaddr *saddr,
		const struct sockaddr *smask, u_int flags, struct llentry *lle)
{
	const struct in6_addr *addr, *mask, *lle_addr;

	addr = &((const struct sockaddr_in6 *)(const void *)saddr)->sin6_addr;
	mask = &((const struct sockaddr_in6 *)(const void *)smask)->sin6_addr;
	lle_addr = &lle->r_l3addr.addr6;

	if (IN6_ARE_MASKED_ADDR_EQUAL(lle_addr, addr, mask) == 0)
		return (0);

	if (lle->la_flags & LLE_IFADDR) {
		/*
		 * Delete LLE_IFADDR records IFF address & flag matches.
		 * Note that addr is the interface address within prefix
		 * being matched.
		 */
		if (IN6_ARE_ADDR_EQUAL(addr, lle_addr) &&
				(flags & LLE_STATIC) != 0)
			return (1);
		return (0);
	}

	/* flags & LLE_STATIC means deleting both dynamic and static entries */
	if ((flags & LLE_STATIC) || !(lle->la_flags & LLE_STATIC))
		return (1);

	return (0);
}