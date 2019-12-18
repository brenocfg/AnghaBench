#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * s6_addr16; } ;
struct TYPE_10__ {TYPE_3__ sin6_addr; } ;
struct nd_prefix {int ndpr_plen; TYPE_2__ ndpr_prefix; struct ifnet* ndpr_ifp; } ;
struct TYPE_12__ {struct ifnet* ifa_ifp; } ;
struct TYPE_9__ {int /*<<< orphan*/  sin6_addr; } ;
struct in6_ifaddr {struct in6_ifaddr* ia_next; TYPE_4__ ia_ifa; TYPE_1__ ia_addr; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  pr0 ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_ADDREF_LOCKED (TYPE_4__*) ; 
 int /*<<< orphan*/  IFA_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  IFA_REMREF (TYPE_4__*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (TYPE_4__*) ; 
 scalar_t__ IN6_IS_ADDR_LINKLOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPV6_ADDR_INT16_ULL ; 
 int /*<<< orphan*/  ND6_PREFIX_EXPIRY_UNSPEC ; 
 int /*<<< orphan*/  NDPR_LOCK (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_REMREF (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_UNLOCK (struct nd_prefix*) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct nd_prefix*,int) ; 
 int /*<<< orphan*/  in6_ifaddr_rwlock ; 
 struct in6_ifaddr* in6_ifaddrs ; 
 int /*<<< orphan*/  in6_purgeaddr (TYPE_4__*) ; 
 int /*<<< orphan*/  in6_setscope (TYPE_3__*,struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd6_mutex ; 
 struct nd_prefix* nd6_prefix_lookup (struct nd_prefix*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prelist_remove (struct nd_prefix*) ; 

__attribute__((used)) static __attribute__((noinline)) int
in6ctl_llstop(struct ifnet *ifp)
{
	struct in6_ifaddr *ia;
	struct nd_prefix pr0, *pr;

	VERIFY(ifp != NULL);

	/* Remove link local addresses from interface */
	lck_rw_lock_exclusive(&in6_ifaddr_rwlock);
	ia = in6_ifaddrs;
	while (ia != NULL) {
		if (ia->ia_ifa.ifa_ifp != ifp) {
			ia = ia->ia_next;
			continue;
		}
		IFA_LOCK(&ia->ia_ifa);
		if (IN6_IS_ADDR_LINKLOCAL(&ia->ia_addr.sin6_addr)) {
			IFA_ADDREF_LOCKED(&ia->ia_ifa);	/* for us */
			IFA_UNLOCK(&ia->ia_ifa);
			lck_rw_done(&in6_ifaddr_rwlock);
			in6_purgeaddr(&ia->ia_ifa);
			IFA_REMREF(&ia->ia_ifa);	/* for us */
			lck_rw_lock_exclusive(&in6_ifaddr_rwlock);
			/*
			 * Purging the address caused in6_ifaddr_rwlock
			 * to be dropped and reacquired;
			 * therefore search again from the beginning
			 * of in6_ifaddrs list.
			 */
			ia = in6_ifaddrs;
			continue;
		}
		IFA_UNLOCK(&ia->ia_ifa);
		ia = ia->ia_next;
	}
	lck_rw_done(&in6_ifaddr_rwlock);

	/* Delete the link local prefix */
	bzero(&pr0, sizeof(pr0));
	pr0.ndpr_plen = 64;
	pr0.ndpr_ifp = ifp;
	pr0.ndpr_prefix.sin6_addr.s6_addr16[0] = IPV6_ADDR_INT16_ULL;
	in6_setscope(&pr0.ndpr_prefix.sin6_addr, ifp, NULL);
	pr = nd6_prefix_lookup(&pr0, ND6_PREFIX_EXPIRY_UNSPEC);
	if (pr) {
		lck_mtx_lock(nd6_mutex);
		NDPR_LOCK(pr);
		prelist_remove(pr);
		NDPR_UNLOCK(pr);
		NDPR_REMREF(pr); /* Drop the reference from lookup */
		lck_mtx_unlock(nd6_mutex);
	}

	return (0);
}