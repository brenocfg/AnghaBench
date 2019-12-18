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
struct sockaddr_in6 {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ifnet {int dummy; } ;
struct ifaddr {int ifa_debug; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EHOSTUNREACH ; 
 int ENETUNREACH ; 
 int /*<<< orphan*/  IFA_REMREF (struct ifaddr*) ; 
 int IFD_DETACHING ; 
 int /*<<< orphan*/  IPV6_SRCSEL_HINT_PREFER_TMPADDR ; 
 int /*<<< orphan*/  SASEL_LOG (char*,int) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_release (struct ifnet*) ; 
 struct in6_addr* in6_selectsrc_core (struct sockaddr_in6*,int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ ,struct in6_addr*,struct ifnet**,int*,struct ifaddr**) ; 
 scalar_t__ ip6_prefer_tempaddr ; 

struct ifaddr *
in6_selectsrc_core_ifa(struct sockaddr_in6 *addr, struct ifnet *ifp, int srcsel_debug) {
	int err = 0;
	struct ifnet *src_ifp = NULL;
	struct in6_addr src_storage = {};
	struct in6_addr *in6 = NULL;
	struct ifaddr *ifa = NULL;

	if((in6 = in6_selectsrc_core(addr,
	    (ip6_prefer_tempaddr ? IPV6_SRCSEL_HINT_PREFER_TMPADDR : 0),
	    ifp, 0, &src_storage, &src_ifp, &err, &ifa)) == NULL) {
		if (err == 0)
			err = EADDRNOTAVAIL;
		VERIFY(src_ifp == NULL);
		if (ifa != NULL) {
			IFA_REMREF(ifa);
			ifa = NULL;
		}
		goto done;
	}

	if (src_ifp != ifp) {
		if (err == 0)
			err = ENETUNREACH;
		if (ifa != NULL) {
			IFA_REMREF(ifa);
			ifa = NULL;
		}
		goto done;
	}

	VERIFY(ifa != NULL);
	ifnet_lock_shared(ifp);
	if ((ifa->ifa_debug & IFD_DETACHING) != 0) {
		err = EHOSTUNREACH;
		ifnet_lock_done(ifp);
		if (ifa != NULL) {
			IFA_REMREF(ifa);
			ifa = NULL;
		}
		goto done;
	}
	ifnet_lock_done(ifp);

done:
	SASEL_LOG("Returned with error: %d", err);
	if (src_ifp != NULL)
		ifnet_release(src_ifp);
	return (ifa);
}