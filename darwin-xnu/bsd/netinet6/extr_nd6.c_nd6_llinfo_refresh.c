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
typedef  scalar_t__ uint64_t ;
struct rtentry {int rt_flags; struct llinfo_nd6* rt_llinfo; } ;
struct llinfo_nd6 {scalar_t__ ln_expire; scalar_t__ ln_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND6_CACHE_STATE_TRANSITION (struct llinfo_nd6*,scalar_t__) ; 
 scalar_t__ ND6_LLINFO_INCOMPLETE ; 
 scalar_t__ ND6_LLINFO_PROBE ; 
 int RTF_LLINFO ; 
 int RTF_STATIC ; 
 int /*<<< orphan*/  ln_setexpire (struct llinfo_nd6*,scalar_t__) ; 
 scalar_t__ net_uptime () ; 

__attribute__((used)) static void
nd6_llinfo_refresh(struct rtentry *rt)
{
	struct llinfo_nd6 *ln = rt->rt_llinfo;
	uint64_t timenow = net_uptime();
	/*
	 * Can't refresh permanent, static or entries that are
	 * not direct host entries
	 */
	if (!ln || ln->ln_expire == 0 ||
	    (rt->rt_flags & RTF_STATIC) ||
	    !(rt->rt_flags & RTF_LLINFO)) {
		return;
	}

	if ((ln->ln_state > ND6_LLINFO_INCOMPLETE) &&
	    (ln->ln_state < ND6_LLINFO_PROBE)) {
		if (ln->ln_expire > timenow) {
			ln_setexpire(ln, timenow);
			ND6_CACHE_STATE_TRANSITION(ln, ND6_LLINFO_PROBE);
		}
	}
	return;
}