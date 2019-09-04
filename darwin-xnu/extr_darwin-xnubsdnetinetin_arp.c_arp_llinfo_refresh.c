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
struct rtentry {scalar_t__ rt_expire; int rt_flags; } ;

/* Variables and functions */
 int RTF_LLINFO ; 
 int RTF_STATIC ; 
 scalar_t__ net_uptime () ; 

__attribute__((used)) static void
arp_llinfo_refresh(struct rtentry *rt)
{
	uint64_t timenow = net_uptime();
	/*
	 * If route entry is permanent or if expiry is less
	 * than timenow and extra time taken for unicast probe
	 * we can't expedite the refresh
	 */
	if ((rt->rt_expire == 0) ||
	    (rt->rt_flags & RTF_STATIC) ||
	    !(rt->rt_flags & RTF_LLINFO)) {
		return;
	}

	if (rt->rt_expire > timenow)
		rt->rt_expire = timenow;
	return;
}