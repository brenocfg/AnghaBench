#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int32_t ;
typedef  scalar_t__ time_t ;
struct nd_prefix {scalar_t__ ndpr_addrcnt; } ;
struct TYPE_17__ {struct ifnet* ifa_ifp; } ;
struct TYPE_15__ {scalar_t__ ia6ti_vltime; scalar_t__ ia6ti_pltime; } ;
struct in6_addr {int* s6_addr32; int /*<<< orphan*/ * s6_addr; } ;
struct TYPE_14__ {struct in6_addr sin6_addr; } ;
struct TYPE_12__ {int* s6_addr32; } ;
struct TYPE_13__ {TYPE_1__ sin6_addr; } ;
struct in6_ifaddr {scalar_t__ ia6_updatetime; int ia6_flags; TYPE_6__ ia_ifa; struct nd_prefix* ia6_ndpr; TYPE_4__ ia6_lifetime; TYPE_3__ ia_addr; TYPE_2__ ia_prefixmask; } ;
struct TYPE_16__ {scalar_t__ ia6t_pltime; scalar_t__ ia6t_vltime; } ;
struct in6_aliasreq {int ifra_flags; TYPE_5__ ifra_lifetime; TYPE_3__ ifra_addr; TYPE_2__ ifra_prefixmask; int /*<<< orphan*/  ifra_name; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  ifra ;
struct TYPE_11__ {TYPE_6__ ia_ifa; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EEXIST ; 
 TYPE_10__* IA6_NONCONST (struct in6_ifaddr const*) ; 
 scalar_t__ IFA6_IS_DEPRECATED (struct in6_ifaddr const*,scalar_t__) ; 
 scalar_t__ IFA6_IS_INVALID (struct in6_ifaddr const*,scalar_t__) ; 
 int /*<<< orphan*/  IFA_LOCK (TYPE_6__*) ; 
 int /*<<< orphan*/  IFA_REMREF (TYPE_6__*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (TYPE_6__*) ; 
 int IN6_IFAUPDATE_DADDELAY ; 
 int IN6_IFAUPDATE_NOWAIT ; 
 int IN6_IFF_AUTOCONF ; 
 int IN6_IFF_TEMPORARY ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 scalar_t__ ND6_INFINITE_LIFETIME ; 
 int /*<<< orphan*/  NDPR_ADDREF (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_ADDREF_LOCKED (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_LOCK (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_REMREF (struct nd_prefix*) ; 
 int /*<<< orphan*/  NDPR_UNLOCK (struct nd_prefix*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (struct in6_aliasreq*,int) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  in6_iid_mktmp (struct ifnet*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  in6_purgeaddr (TYPE_6__*) ; 
 int in6_update_ifa (struct ifnet*,struct in6_aliasreq*,int,struct in6_ifaddr**) ; 
 struct in6_ifaddr* in6ifa_ifpwithaddr (struct ifnet*,struct in6_addr*) ; 
 scalar_t__ ip6_desync_factor ; 
 scalar_t__ ip6_temp_preferred_lifetime ; 
 scalar_t__ ip6_temp_regen_advance ; 
 scalar_t__ ip6_temp_valid_lifetime ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd6_mutex ; 
 int /*<<< orphan*/  nd6log (int /*<<< orphan*/ ) ; 
 scalar_t__ net_uptime () ; 
 int /*<<< orphan*/  pfxlist_onlink_check () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
in6_tmpifadd(const struct in6_ifaddr *ia0, int forcegen)
{
	struct ifnet *ifp = ia0->ia_ifa.ifa_ifp;
	struct in6_ifaddr *ia, *newia;
	struct in6_aliasreq ifra;
	int i, error, ifaupdate;
	int trylimit = 3;	/* XXX: adhoc value */
	u_int32_t randid[2];
	time_t vltime0, pltime0;
	uint64_t timenow = net_uptime();
	struct in6_addr addr;
	struct nd_prefix *ndpr;

	bzero(&ifra, sizeof (ifra));
	strlcpy(ifra.ifra_name, if_name(ifp), sizeof (ifra.ifra_name));
	IFA_LOCK(&IA6_NONCONST(ia0)->ia_ifa);
	ifra.ifra_addr = ia0->ia_addr;
	/* copy prefix mask */
	ifra.ifra_prefixmask = ia0->ia_prefixmask;
	/* clear the old IFID */
	for (i = 0; i < 4; i++) {
		ifra.ifra_addr.sin6_addr.s6_addr32[i]
			&= ifra.ifra_prefixmask.sin6_addr.s6_addr32[i];
	}
	addr = ia0->ia_addr.sin6_addr;
	IFA_UNLOCK(&IA6_NONCONST(ia0)->ia_ifa);

again:
	in6_iid_mktmp(ifp, (u_int8_t *)randid,
	    (const u_int8_t *)&addr.s6_addr[8], forcegen);

	ifra.ifra_addr.sin6_addr.s6_addr32[2] |=
	    (randid[0] & ~(ifra.ifra_prefixmask.sin6_addr.s6_addr32[2]));
	ifra.ifra_addr.sin6_addr.s6_addr32[3] |=
	    (randid[1] & ~(ifra.ifra_prefixmask.sin6_addr.s6_addr32[3]));

	/*
	 * in6_iid_mktmp() quite likely provided a unique interface ID.
	 * However, we may still have a chance to see collision, because
	 * there may be a time lag between generation of the ID and generation
	 * of the address.  So, we'll do one more sanity check.
	 */
	if ((ia = in6ifa_ifpwithaddr(ifp, &ifra.ifra_addr.sin6_addr)) != NULL) {
		IFA_REMREF(&ia->ia_ifa);
		if (trylimit-- == 0) {
			nd6log((LOG_NOTICE, "in6_tmpifadd: failed to find "
			    "a unique random IFID\n"));
			return (EEXIST);
		}
		forcegen = 1;
		goto again;
	}

	/*
	 * The Valid Lifetime is the lower of the Valid Lifetime of the
	 * public address or TEMP_VALID_LIFETIME.
	 * The Preferred Lifetime is the lower of the Preferred Lifetime
	 * of the public address or TEMP_PREFERRED_LIFETIME -
	 * DESYNC_FACTOR.
	 */
	IFA_LOCK(&IA6_NONCONST(ia0)->ia_ifa);
	if (ia0->ia6_lifetime.ia6ti_vltime != ND6_INFINITE_LIFETIME) {
		vltime0 = IFA6_IS_INVALID(ia0, timenow) ? 0 :
		    (ia0->ia6_lifetime.ia6ti_vltime -
		    (timenow - ia0->ia6_updatetime));
		if (vltime0 > ip6_temp_valid_lifetime)
			vltime0 = ip6_temp_valid_lifetime;
	} else {
		vltime0 = ip6_temp_valid_lifetime;
	}
	if (ia0->ia6_lifetime.ia6ti_pltime != ND6_INFINITE_LIFETIME) {
		pltime0 = IFA6_IS_DEPRECATED(ia0, timenow) ? 0 :
		    (ia0->ia6_lifetime.ia6ti_pltime -
		    (timenow - ia0->ia6_updatetime));
		if (pltime0 > ip6_temp_preferred_lifetime - ip6_desync_factor)
			pltime0 = ip6_temp_preferred_lifetime -
			    ip6_desync_factor;
	} else {
		pltime0 = ip6_temp_preferred_lifetime - ip6_desync_factor;
	}
	ifra.ifra_lifetime.ia6t_vltime = vltime0;
	ifra.ifra_lifetime.ia6t_pltime = pltime0;
	IFA_UNLOCK(&IA6_NONCONST(ia0)->ia_ifa);
	/*
	 * A temporary address is created only if this calculated Preferred
	 * Lifetime is greater than REGEN_ADVANCE time units.
	 */
	if (ifra.ifra_lifetime.ia6t_pltime <= ip6_temp_regen_advance)
		return (0);

	/* XXX: scope zone ID? */

	ifra.ifra_flags |= (IN6_IFF_AUTOCONF|IN6_IFF_TEMPORARY);

	/* allocate ifaddr structure, link into chain, etc. */
	ifaupdate = IN6_IFAUPDATE_NOWAIT | IN6_IFAUPDATE_DADDELAY;
	error = in6_update_ifa(ifp, &ifra, ifaupdate, &newia);
	if (error != 0) {
		nd6log((LOG_ERR, "in6_tmpifadd: failed to add address.\n"));
		return (error);
	}
	VERIFY(newia != NULL);

	IFA_LOCK(&IA6_NONCONST(ia0)->ia_ifa);
	ndpr = ia0->ia6_ndpr;
	if (ndpr == NULL) {
		/*
		 * We lost the race with another thread that has purged
		 * ia0 address; in this case, purge the tmp addr as well.
		 */
		nd6log((LOG_ERR, "in6_tmpifadd: no public address\n"));
		VERIFY(!(ia0->ia6_flags & IN6_IFF_AUTOCONF));
		IFA_UNLOCK(&IA6_NONCONST(ia0)->ia_ifa);
		in6_purgeaddr(&newia->ia_ifa);
		IFA_REMREF(&newia->ia_ifa);
		return (EADDRNOTAVAIL);
	}
	NDPR_ADDREF(ndpr);	/* for us */
	IFA_UNLOCK(&IA6_NONCONST(ia0)->ia_ifa);
	IFA_LOCK(&newia->ia_ifa);
	if (newia->ia6_ndpr != NULL) {
		NDPR_LOCK(newia->ia6_ndpr);
		VERIFY(newia->ia6_ndpr->ndpr_addrcnt != 0);
		newia->ia6_ndpr->ndpr_addrcnt--;
		NDPR_UNLOCK(newia->ia6_ndpr);
		NDPR_REMREF(newia->ia6_ndpr);	/* release addr reference */
	}
	newia->ia6_ndpr = ndpr;
	NDPR_LOCK(newia->ia6_ndpr);
	newia->ia6_ndpr->ndpr_addrcnt++;
	VERIFY(newia->ia6_ndpr->ndpr_addrcnt != 0);
	NDPR_ADDREF_LOCKED(newia->ia6_ndpr);	/* for addr reference */
	NDPR_UNLOCK(newia->ia6_ndpr);
	IFA_UNLOCK(&newia->ia_ifa);
	/*
	 * A newly added address might affect the status of other addresses.
	 * XXX: when the temporary address is generated with a new public
	 * address, the onlink check is redundant.  However, it would be safe
	 * to do the check explicitly everywhere a new address is generated,
	 * and, in fact, we surely need the check when we create a new
	 * temporary address due to deprecation of an old temporary address.
	 */
	lck_mtx_lock(nd6_mutex);
	pfxlist_onlink_check();
	lck_mtx_unlock(nd6_mutex);
	IFA_REMREF(&newia->ia_ifa);

	/* remove our reference */
	NDPR_REMREF(ndpr);

	return (0);
}