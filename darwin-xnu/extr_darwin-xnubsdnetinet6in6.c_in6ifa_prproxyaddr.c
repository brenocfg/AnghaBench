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
struct in6_ifaddr {int /*<<< orphan*/  ia_ifa; struct in6_ifaddr* ia_next; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_ADDREF_LOCKED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFA_IN6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFA_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFA_REMREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFA_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ IN6_ARE_ADDR_EQUAL (struct in6_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_ifaddr_rwlock ; 
 struct in6_ifaddr* in6_ifaddrs ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd6_prproxy_ifaddr (struct in6_ifaddr*) ; 

struct in6_ifaddr *
in6ifa_prproxyaddr(struct in6_addr *addr)
{
	struct in6_ifaddr *ia;

	lck_rw_lock_shared(&in6_ifaddr_rwlock);
	for (ia = in6_ifaddrs; ia; ia = ia->ia_next) {
		IFA_LOCK(&ia->ia_ifa);
		if (IN6_ARE_ADDR_EQUAL(addr, IFA_IN6(&ia->ia_ifa))) {
			IFA_ADDREF_LOCKED(&ia->ia_ifa);	/* for caller */
			IFA_UNLOCK(&ia->ia_ifa);
			break;
		}
		IFA_UNLOCK(&ia->ia_ifa);
	}
	lck_rw_done(&in6_ifaddr_rwlock);

	if (ia != NULL && !nd6_prproxy_ifaddr(ia)) {
		IFA_REMREF(&ia->ia_ifa);
		ia = NULL;
	}

	return (ia);
}