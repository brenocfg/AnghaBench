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
struct rtentry {scalar_t__ rt_llinfo_purge; struct llinfo_arp* rt_llinfo; } ;
struct llinfo_arp {scalar_t__ la_lastused; int /*<<< orphan*/ * la_llreach; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_CONVERT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_HELD (struct rtentry*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ifnet_llreach_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arp_llinfo_purge(struct rtentry *rt)
{
	struct llinfo_arp *la = rt->rt_llinfo;

	RT_LOCK_ASSERT_HELD(rt);
	VERIFY(rt->rt_llinfo_purge == arp_llinfo_purge && la != NULL);

	if (la->la_llreach != NULL) {
		RT_CONVERT_LOCK(rt);
		ifnet_llreach_free(la->la_llreach);
		la->la_llreach = NULL;
	}
	la->la_lastused = 0;
}