#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct ifnet* ifa_ifp; } ;
struct in6_ifaddr {TYPE_1__ ia_ifa; struct in6_ifaddr* ia_next; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_ADDREF (TYPE_1__*) ; 
 int /*<<< orphan*/  IFA_REMREF (TYPE_1__*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  in6_ifaddr_rwlock ; 
 struct in6_ifaddr* in6_ifaddrs ; 
 int /*<<< orphan*/  in6_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  in6_purgeaddr (TYPE_1__*) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd6_mutex ; 

void
in6_purgeif(struct ifnet *ifp)
{
	struct in6_ifaddr *ia;

	if (ifp == NULL)
		return;

	LCK_MTX_ASSERT(nd6_mutex, LCK_MTX_ASSERT_NOTOWNED);

	lck_rw_lock_exclusive(&in6_ifaddr_rwlock);
	ia = in6_ifaddrs;
	while (ia != NULL) {
		if (ia->ia_ifa.ifa_ifp != ifp) {
			ia = ia->ia_next;
			continue;
		}
		IFA_ADDREF(&ia->ia_ifa);	/* for us */
		lck_rw_done(&in6_ifaddr_rwlock);
		in6_purgeaddr(&ia->ia_ifa);
		IFA_REMREF(&ia->ia_ifa);	/* for us */
		lck_rw_lock_exclusive(&in6_ifaddr_rwlock);
		/*
		 * Purging the address would have caused
		 * in6_ifaddr_rwlock to be dropped and reacquired;
		 * therefore search again from the beginning
		 * of in6_ifaddrs list.
		 */
		ia = in6_ifaddrs;
	}
	lck_rw_done(&in6_ifaddr_rwlock);

	in6_ifdetach(ifp);
}