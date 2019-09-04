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
struct pf_addr {int dummy; } ;
typedef  int sa_family_t ;

/* Variables and functions */

int
pf_match_addr_range(struct pf_addr *b, struct pf_addr *e,
    struct pf_addr *a, sa_family_t af)
{
	switch (af) {
#if INET
	case AF_INET:
		if ((a->addr32[0] < b->addr32[0]) ||
		    (a->addr32[0] > e->addr32[0]))
			return (0);
		break;
#endif /* INET */
#if INET6
	case AF_INET6: {
		int	i;

		/* check a >= b */
		for (i = 0; i < 4; ++i)
			if (a->addr32[i] > b->addr32[i])
				break;
			else if (a->addr32[i] < b->addr32[i])
				return (0);
		/* check a <= e */
		for (i = 0; i < 4; ++i)
			if (a->addr32[i] < e->addr32[i])
				break;
			else if (a->addr32[i] > e->addr32[i])
				return (0);
		break;
	}
#endif /* INET6 */
	}
	return (1);
}