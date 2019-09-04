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
struct in6_addr {int* s6_addr; } ;

/* Variables and functions */
 scalar_t__ IN6_IS_ADDR_LINKLOCAL (struct in6_addr const*) ; 
 scalar_t__ IN6_IS_ADDR_LOOPBACK (struct in6_addr const*) ; 
 scalar_t__ IN6_IS_ADDR_MULTICAST (struct in6_addr const*) ; 
 scalar_t__ IN6_IS_ADDR_SITELOCAL (struct in6_addr const*) ; 

__attribute__((used)) static int scopeof(const struct in6_addr *a)
{
	if (IN6_IS_ADDR_MULTICAST(a)) return a->s6_addr[1] & 15;
	if (IN6_IS_ADDR_LINKLOCAL(a)) return 2;
	if (IN6_IS_ADDR_LOOPBACK(a)) return 2;
	if (IN6_IS_ADDR_SITELOCAL(a)) return 5;
	return 14;
}