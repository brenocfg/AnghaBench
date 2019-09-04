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
struct rtentry {scalar_t__ rt_llinfo_purge; struct llinfo_nd6* rt_llinfo; } ;
struct llinfo_nd6 {scalar_t__ ln_lastused; int /*<<< orphan*/ * ln_llreach; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_CONVERT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_HELD (struct rtentry*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ifnet_llreach_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nd6_llinfo_purge(struct rtentry *rt)
{
	struct llinfo_nd6 *ln = rt->rt_llinfo;

	RT_LOCK_ASSERT_HELD(rt);
	VERIFY(rt->rt_llinfo_purge == nd6_llinfo_purge && ln != NULL);

	if (ln->ln_llreach != NULL) {
		RT_CONVERT_LOCK(rt);
		ifnet_llreach_free(ln->ln_llreach);
		ln->ln_llreach = NULL;
	}
	ln->ln_lastused = 0;
}