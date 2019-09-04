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
struct nd_defrouter {int /*<<< orphan*/ * ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 struct nd_defrouter* defrtrlist_update_common (struct nd_defrouter*,int) ; 
 int /*<<< orphan*/ * nd6_defifp ; 
 int /*<<< orphan*/  nd6_mutex ; 

__attribute__((used)) static struct nd_defrouter *
defrtrlist_update(struct nd_defrouter *new)
{
	struct nd_defrouter *dr;

	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_OWNED);
	dr = defrtrlist_update_common(new,
	    (nd6_defifp != NULL && new->ifp != nd6_defifp));

	return (dr);
}