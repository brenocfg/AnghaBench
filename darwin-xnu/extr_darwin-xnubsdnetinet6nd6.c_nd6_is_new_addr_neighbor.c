#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct sockaddr_in6 {scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  sin6_addr; } ;
struct nd_prefix {int ndpr_stateflags; int /*<<< orphan*/  ndpr_mask; TYPE_1__ ndpr_prefix; struct ifnet* ndpr_ifp; struct nd_prefix* ndpr_next; } ;
struct ifnet {int dummy; } ;
struct ifaddr {struct ifnet* ifa_ifp; } ;
struct TYPE_4__ {struct nd_prefix* lh_first; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IFA_REMREF (struct ifaddr*) ; 
 scalar_t__ IN6_ARE_MASKED_ADDR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IN6_IS_ADDR_LINKLOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int NDPRF_ONLINK ; 
 int /*<<< orphan*/  NDPR_LOCK (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_UNLOCK (struct nd_prefix*) ; 
 int /*<<< orphan*/  SA (struct sockaddr_in6*) ; 
 struct ifaddr* ifa_ifwithdstaddr (int /*<<< orphan*/ ) ; 
 scalar_t__ in6_setscope (int /*<<< orphan*/ *,struct ifnet*,scalar_t__*) ; 
 int /*<<< orphan*/  nd6_mutex ; 
 TYPE_2__ nd_prefix ; 
 scalar_t__ sa6_recoverscope (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nd6_is_new_addr_neighbor(struct sockaddr_in6 *addr, struct ifnet *ifp)
{
	struct nd_prefix *pr;
	struct ifaddr *dstaddr;

	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_OWNED);

	/*
	 * A link-local address is always a neighbor.
	 * XXX: a link does not necessarily specify a single interface.
	 */
	if (IN6_IS_ADDR_LINKLOCAL(&addr->sin6_addr)) {
		struct sockaddr_in6 sin6_copy;
		u_int32_t zone;

		/*
		 * We need sin6_copy since sa6_recoverscope() may modify the
		 * content (XXX).
		 */
		sin6_copy = *addr;
		if (sa6_recoverscope(&sin6_copy, FALSE))
			return (0); /* XXX: should be impossible */
		if (in6_setscope(&sin6_copy.sin6_addr, ifp, &zone))
			return (0);
		if (sin6_copy.sin6_scope_id == zone)
			return (1);
		else
			return (0);
	}

	/*
	 * If the address matches one of our addresses,
	 * it should be a neighbor.
	 * If the address matches one of our on-link prefixes, it should be a
	 * neighbor.
	 */
	for (pr = nd_prefix.lh_first; pr; pr = pr->ndpr_next) {
		NDPR_LOCK(pr);
		if (pr->ndpr_ifp != ifp) {
			NDPR_UNLOCK(pr);
			continue;
		}
		if (!(pr->ndpr_stateflags & NDPRF_ONLINK)) {
			NDPR_UNLOCK(pr);
			continue;
		}
		if (IN6_ARE_MASKED_ADDR_EQUAL(&pr->ndpr_prefix.sin6_addr,
		    &addr->sin6_addr, &pr->ndpr_mask)) {
			NDPR_UNLOCK(pr);
			return (1);
		}
		NDPR_UNLOCK(pr);
	}

	/*
	 * If the address is assigned on the node of the other side of
	 * a p2p interface, the address should be a neighbor.
	 */
	dstaddr = ifa_ifwithdstaddr(SA(addr));
	if (dstaddr != NULL) {
		if (dstaddr->ifa_ifp == ifp) {
			IFA_REMREF(dstaddr);
			return (1);
		}
		IFA_REMREF(dstaddr);
		dstaddr = NULL;
	}

	return (0);
}