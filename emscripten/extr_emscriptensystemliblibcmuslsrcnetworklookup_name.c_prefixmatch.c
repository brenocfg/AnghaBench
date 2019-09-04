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

__attribute__((used)) static int prefixmatch(const struct in6_addr *s, const struct in6_addr *d)
{
	/* FIXME: The common prefix length should be limited to no greater
	 * than the nominal length of the prefix portion of the source
	 * address. However the definition of the source prefix length is
	 * not clear and thus this limiting is not yet implemented. */
	unsigned i;
	for (i=0; i<128 && !((s->s6_addr[i/8]^d->s6_addr[i/8])&(128>>(i%8))); i++);
	return i;
}