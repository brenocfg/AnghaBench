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
struct in6_addr {int /*<<< orphan*/ * s6_addr32; } ;

/* Variables and functions */
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
iprange_ipv6_sub(const struct in6_addr *a, const struct in6_addr *b)
{
	unsigned int i;
	int r;

	for (i = 0; i < 4; ++i) {
		r = ntohl(a->s6_addr32[i]) - ntohl(b->s6_addr32[i]);
		if (r != 0)
			return r;
	}

	return 0;
}