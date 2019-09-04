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
typedef  scalar_t__ u_int8_t ;
struct pf_addr {int dummy; } ;
typedef  int sa_family_t ;

/* Variables and functions */

int
pf_match_addr(u_int8_t n, struct pf_addr *a, struct pf_addr *m,
    struct pf_addr *b, sa_family_t af)
{
	int	match = 0;

	switch (af) {
#if INET
	case AF_INET:
		if ((a->addr32[0] & m->addr32[0]) ==
		    (b->addr32[0] & m->addr32[0]))
			match++;
		break;
#endif /* INET */
#if INET6
	case AF_INET6:
		if (((a->addr32[0] & m->addr32[0]) ==
		     (b->addr32[0] & m->addr32[0])) &&
		    ((a->addr32[1] & m->addr32[1]) ==
		     (b->addr32[1] & m->addr32[1])) &&
		    ((a->addr32[2] & m->addr32[2]) ==
		     (b->addr32[2] & m->addr32[2])) &&
		    ((a->addr32[3] & m->addr32[3]) ==
		     (b->addr32[3] & m->addr32[3])))
			match++;
		break;
#endif /* INET6 */
	}
	if (match) {
		if (n)
			return (0);
		else
			return (1);
	} else {
		if (n)
			return (1);
		else
			return (0);
	}
}