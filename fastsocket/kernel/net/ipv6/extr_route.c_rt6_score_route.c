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
struct rt6_info {int /*<<< orphan*/  rt6i_flags; } ;

/* Variables and functions */
 int IPV6_DECODE_PREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPV6_EXTRACT_PREF (int /*<<< orphan*/ ) ; 
 int RT6_LOOKUP_F_IFACE ; 
 int RT6_LOOKUP_F_REACHABLE ; 
 int RT6_NUD_FAIL_HARD ; 
 int rt6_check_dev (struct rt6_info*,int) ; 
 int rt6_check_neigh (struct rt6_info*) ; 

__attribute__((used)) static int rt6_score_route(struct rt6_info *rt, int oif,
			   int strict)
{
	int m;

	m = rt6_check_dev(rt, oif);
	if (!m && (strict & RT6_LOOKUP_F_IFACE))
		return RT6_NUD_FAIL_HARD;
#ifdef CONFIG_IPV6_ROUTER_PREF
	m |= IPV6_DECODE_PREF(IPV6_EXTRACT_PREF(rt->rt6i_flags)) << 2;
#endif
	if (strict & RT6_LOOKUP_F_REACHABLE) {
		int n = rt6_check_neigh(rt);
		if (n < 0)
			return n;
	}
	return m;
}