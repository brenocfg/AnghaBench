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
struct nd_defrouter {int /*<<< orphan*/  rtaddr; struct ifnet* ifp; } ;
struct in6_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ IN6_ARE_ADDR_EQUAL (struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  NDDR_ADDREF_LOCKED (struct nd_defrouter*) ; 
 int /*<<< orphan*/  NDDR_LOCK (struct nd_defrouter*) ; 
 int /*<<< orphan*/  NDDR_UNLOCK (struct nd_defrouter*) ; 
 struct nd_defrouter* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct nd_defrouter* TAILQ_NEXT (struct nd_defrouter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr_entry ; 
 int /*<<< orphan*/  nd6_mutex ; 
 int /*<<< orphan*/  nd_defrouter ; 

struct nd_defrouter *
defrouter_lookup(
	struct in6_addr *addr,
	struct ifnet *ifp)
{
	struct nd_defrouter *dr;

	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_OWNED);

	for (dr = TAILQ_FIRST(&nd_defrouter); dr;
	    dr = TAILQ_NEXT(dr, dr_entry)) {
		NDDR_LOCK(dr);
		if (dr->ifp == ifp && IN6_ARE_ADDR_EQUAL(addr, &dr->rtaddr)) {
			NDDR_ADDREF_LOCKED(dr);
			NDDR_UNLOCK(dr);
			return (dr);
		}
		NDDR_UNLOCK(dr);
	}

	return (NULL);		/* search failed */
}