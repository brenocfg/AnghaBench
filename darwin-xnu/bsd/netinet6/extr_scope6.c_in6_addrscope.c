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
struct in6_addr {int* s6_addr8; } ;

/* Variables and functions */
 int IPV6_ADDR_SCOPE_GLOBAL ; 
#define  IPV6_ADDR_SCOPE_INTFACELOCAL 130 
#define  IPV6_ADDR_SCOPE_LINKLOCAL 129 
#define  IPV6_ADDR_SCOPE_SITELOCAL 128 
 scalar_t__ bcmp (int /*<<< orphan*/ *,struct in6_addr*,int) ; 
 int /*<<< orphan*/  in6addr_loopback ; 

int
in6_addrscope(struct in6_addr *addr)
{
	int scope;

	if (addr->s6_addr8[0] == 0xfe) {
		scope = addr->s6_addr8[1] & 0xc0;

		switch (scope) {
		case 0x80:
			return (IPV6_ADDR_SCOPE_LINKLOCAL);
		case 0xc0:
			return (IPV6_ADDR_SCOPE_SITELOCAL);
		default:
			return (IPV6_ADDR_SCOPE_GLOBAL); /* just in case */
		}
	}

	if (addr->s6_addr8[0] == 0xff) {
		scope = addr->s6_addr8[1] & 0x0f;

		/*
		 * due to other scope such as reserved,
		 * return scope doesn't work.
		 */
		switch (scope) {
		case IPV6_ADDR_SCOPE_INTFACELOCAL:
			return (IPV6_ADDR_SCOPE_INTFACELOCAL);
		case IPV6_ADDR_SCOPE_LINKLOCAL:
			return (IPV6_ADDR_SCOPE_LINKLOCAL);
		case IPV6_ADDR_SCOPE_SITELOCAL:
			return (IPV6_ADDR_SCOPE_SITELOCAL);
		default:
			return (IPV6_ADDR_SCOPE_GLOBAL);
		}
	}

	/*
	 * Regard loopback and unspecified addresses as global, since
	 * they have no ambiguity.
	 */
	if (bcmp(&in6addr_loopback, addr, sizeof (*addr) - 1) == 0) {
		if (addr->s6_addr8[15] == 1) /* loopback */
			return (IPV6_ADDR_SCOPE_LINKLOCAL);
		if (addr->s6_addr8[15] == 0) /* unspecified */
			return (IPV6_ADDR_SCOPE_GLOBAL); /* XXX: correct? */
	}

	return (IPV6_ADDR_SCOPE_GLOBAL);
}