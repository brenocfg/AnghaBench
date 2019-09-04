#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
struct rtentry {struct ifaddr* rt_ifa; } ;
struct TYPE_2__ {int /*<<< orphan*/  sin6_addr; } ;
struct in6_ifaddr {TYPE_1__ ia_addr; } ;
struct ifaddr {int /*<<< orphan*/  ifa_addr; } ;
typedef  int /*<<< orphan*/  all1_sa ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int RTF_HOST ; 
 int RTF_LLINFO ; 
 int RTF_UP ; 
 int RTM_ADD ; 
 int RTM_DELETE ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_REMREF_LOCKED (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 int /*<<< orphan*/  in6mask128 ; 
 int /*<<< orphan*/  ip6_sprintf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rnh_lock ; 
 int /*<<< orphan*/  rt_newaddrmsg (int,struct ifaddr*,int,struct rtentry*) ; 
 int /*<<< orphan*/  rtfree_locked (struct rtentry*) ; 
 int rtrequest_locked (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int,struct rtentry**) ; 
 int /*<<< orphan*/  rtsetifa (struct rtentry*,struct ifaddr*) ; 

__attribute__((used)) static void
in6_ifloop_request(int cmd, struct ifaddr *ifa)
{
	struct sockaddr_in6 all1_sa;
	struct rtentry *nrt = NULL;
	int e;

	bzero(&all1_sa, sizeof (all1_sa));
	all1_sa.sin6_family = AF_INET6;
	all1_sa.sin6_len = sizeof (struct sockaddr_in6);
	all1_sa.sin6_addr = in6mask128;

	/*
	 * We specify the address itself as the gateway, and set the
	 * RTF_LLINFO flag, so that the corresponding host route would have
	 * the flag, and thus applications that assume traditional behavior
	 * would be happy.  Note that we assume the caller of the function
	 * (probably implicitly) set nd6_rtrequest() to ifa->ifa_rtrequest,
	 * which changes the outgoing interface to the loopback interface.
	 * ifa_addr for INET6 is set once during init; no need to hold lock.
	 */
	lck_mtx_lock(rnh_lock);
	e = rtrequest_locked(cmd, ifa->ifa_addr, ifa->ifa_addr,
	    (struct sockaddr *)&all1_sa, RTF_UP|RTF_HOST|RTF_LLINFO, &nrt);
	if (e != 0) {
		log(LOG_ERR, "in6_ifloop_request: "
		    "%s operation failed for %s (errno=%d)\n",
		    cmd == RTM_ADD ? "ADD" : "DELETE",
		    ip6_sprintf(&((struct in6_ifaddr *)ifa)->ia_addr.sin6_addr),
		    e);
	}

	if (nrt != NULL)
		RT_LOCK(nrt);
	/*
	 * Make sure rt_ifa be equal to IFA, the second argument of the
	 * function.
	 * We need this because when we refer to rt_ifa->ia6_flags in
	 * ip6_input, we assume that the rt_ifa points to the address instead
	 * of the loopback address.
	 */
	if (cmd == RTM_ADD && nrt && ifa != nrt->rt_ifa) {
		rtsetifa(nrt, ifa);
	}

	/*
	 * Report the addition/removal of the address to the routing socket.
	 * XXX: since we called rtinit for a p2p interface with a destination,
	 *   we end up reporting twice in such a case.  Should we rather
	 *   omit the second report?
	 */
	if (nrt != NULL) {
		rt_newaddrmsg(cmd, ifa, e, nrt);
		if (cmd == RTM_DELETE) {
			RT_UNLOCK(nrt);
			rtfree_locked(nrt);
		} else {
			/* the cmd must be RTM_ADD here */
			RT_REMREF_LOCKED(nrt);
			RT_UNLOCK(nrt);
		}
	}
	lck_mtx_unlock(rnh_lock);
}