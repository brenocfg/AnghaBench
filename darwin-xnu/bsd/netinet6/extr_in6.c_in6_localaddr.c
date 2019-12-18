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
struct TYPE_4__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  sin6_addr; } ;
struct in6_ifaddr {int /*<<< orphan*/  ia_ifa; TYPE_2__ ia_prefixmask; TYPE_1__ ia_addr; struct in6_ifaddr* ia_next; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_LOCK_SPIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFA_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ IN6_ARE_MASKED_ADDR_EQUAL (struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IN6_IS_ADDR_LINKLOCAL (struct in6_addr*) ; 
 scalar_t__ IN6_IS_ADDR_LOOPBACK (struct in6_addr*) ; 
 int /*<<< orphan*/  in6_ifaddr_rwlock ; 
 struct in6_ifaddr* in6_ifaddrs ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 

int
in6_localaddr(struct in6_addr *in6)
{
	struct in6_ifaddr *ia;

	if (IN6_IS_ADDR_LOOPBACK(in6) || IN6_IS_ADDR_LINKLOCAL(in6))
		return (1);

	lck_rw_lock_shared(&in6_ifaddr_rwlock);
	for (ia = in6_ifaddrs; ia; ia = ia->ia_next) {
		IFA_LOCK_SPIN(&ia->ia_ifa);
		if (IN6_ARE_MASKED_ADDR_EQUAL(in6, &ia->ia_addr.sin6_addr,
		    &ia->ia_prefixmask.sin6_addr)) {
			IFA_UNLOCK(&ia->ia_ifa);
			lck_rw_done(&in6_ifaddr_rwlock);
			return (1);
		}
		IFA_UNLOCK(&ia->ia_ifa);
	}
	lck_rw_done(&in6_ifaddr_rwlock);
	return (0);
}