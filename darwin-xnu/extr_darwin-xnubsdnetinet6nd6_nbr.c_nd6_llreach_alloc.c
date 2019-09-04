#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct rtentry {int /*<<< orphan*/  (* rt_llinfo_purge ) (struct rtentry*) ;TYPE_1__* rt_ifp; struct llinfo_nd6* rt_llinfo; } ;
struct llinfo_nd6 {scalar_t__ ln_expire; struct if_llreach* ln_llreach; } ;
struct ifnet {int if_eflags; unsigned int if_addrlen; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct if_llreach {scalar_t__ lr_probes; TYPE_2__ lr_key; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_4__ {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  ETHERTYPE_IPV6 ; 
 int IFEF_IPV6_ND6ALT ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  IFLR_LOCK (struct if_llreach*) ; 
 int /*<<< orphan*/  IFLR_UNLOCK (struct if_llreach*) ; 
 unsigned int IF_LLREACH_MAXLEN ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int MAX_IPv6_STR_LEN ; 
 int /*<<< orphan*/  RT_CONVERT_LOCK (struct rtentry*) ; 
 TYPE_3__* SIN6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 scalar_t__ bcmp (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 struct if_llreach* ifnet_llreach_alloc (struct ifnet*,int /*<<< orphan*/ ,void*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ nd6_debug ; 
 scalar_t__ nd6_llreach_base ; 
 int /*<<< orphan*/  nd6log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  stub1 (struct rtentry*) ; 

void
nd6_llreach_alloc(struct rtentry *rt, struct ifnet *ifp, void *addr,
    unsigned int alen, boolean_t solicited)
{
	struct llinfo_nd6 *ln = rt->rt_llinfo;

	if (nd6_llreach_base != 0 &&
	    (ln->ln_expire != 0 || (ifp->if_eflags & IFEF_IPV6_ND6ALT) != 0) &&
	    !(rt->rt_ifp->if_flags & IFF_LOOPBACK) &&
	    ifp->if_addrlen == IF_LLREACH_MAXLEN &&	/* Ethernet */
	    alen == ifp->if_addrlen) {
		struct if_llreach *lr;
		const char *why = NULL, *type = "";

		/* Become a regular mutex, just in case */
		RT_CONVERT_LOCK(rt);

		if ((lr = ln->ln_llreach) != NULL) {
			type = (solicited ? "ND6 advertisement" :
			    "ND6 unsolicited announcement");
			/*
			 * If target has changed, create a new record;
			 * otherwise keep existing record.
			 */
			IFLR_LOCK(lr);
			if (bcmp(addr, lr->lr_key.addr, alen) != 0) {
				IFLR_UNLOCK(lr);
				/* Purge any link-layer info caching */
				VERIFY(rt->rt_llinfo_purge != NULL);
				rt->rt_llinfo_purge(rt);
				lr = NULL;
				why = " for different target HW address; "
				    "using new llreach record";
			} else {
				lr->lr_probes = 0;	/* reset probe count */
				IFLR_UNLOCK(lr);
				if (solicited) {
					why = " for same target HW address; "
					    "keeping existing llreach record";
				}
			}
		}

		if (lr == NULL) {
			lr = ln->ln_llreach = ifnet_llreach_alloc(ifp,
			    ETHERTYPE_IPV6, addr, alen, nd6_llreach_base);
			if (lr != NULL) {
				lr->lr_probes = 0;	/* reset probe count */
				if (why == NULL)
					why = "creating new llreach record";
			}
		}

		if (nd6_debug && lr != NULL && why != NULL) {
			char tmp[MAX_IPv6_STR_LEN];

			nd6log((LOG_DEBUG, "%s: %s%s for %s\n", if_name(ifp),
			    type, why, inet_ntop(AF_INET6,
			    &SIN6(rt_key(rt))->sin6_addr, tmp, sizeof (tmp))));
		}
	}
}