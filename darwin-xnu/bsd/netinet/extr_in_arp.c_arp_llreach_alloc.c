#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_5__ {scalar_t__ rmx_expire; } ;
struct rtentry {scalar_t__ rt_expire; int /*<<< orphan*/  (* rt_llinfo_purge ) (struct rtentry*) ;struct llinfo_arp* rt_llinfo; TYPE_2__* rt_ifp; TYPE_1__ rt_rmx; } ;
struct llinfo_arp {struct if_llreach* la_llreach; } ;
struct ifnet {unsigned int if_addrlen; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct if_llreach {scalar_t__ lr_probes; TYPE_3__ lr_key; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_6__ {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ETHERTYPE_IP ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  IFLR_LOCK (struct if_llreach*) ; 
 int /*<<< orphan*/  IFLR_UNLOCK (struct if_llreach*) ; 
 unsigned int IF_LLREACH_MAXLEN ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int MAX_IPv4_STR_LEN ; 
 int /*<<< orphan*/  ROUTE_LLENTRY_CHANGED ; 
 int /*<<< orphan*/  ROUTE_LLENTRY_RESOLVED ; 
 int /*<<< orphan*/  RT_CONVERT_LOCK (struct rtentry*) ; 
 TYPE_4__* SIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ arp_llreach_base ; 
 int arp_verbose ; 
 scalar_t__ bcmp (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 struct if_llreach* ifnet_llreach_alloc (struct ifnet*,int /*<<< orphan*/ ,void*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  stub1 (struct rtentry*) ; 

__attribute__((used)) static void
arp_llreach_alloc(struct rtentry *rt, struct ifnet *ifp, void *addr,
    unsigned int alen, boolean_t solicited, uint32_t *p_rt_event_code)
{
	VERIFY(rt->rt_expire == 0 || rt->rt_rmx.rmx_expire != 0);
	VERIFY(rt->rt_expire != 0 || rt->rt_rmx.rmx_expire == 0);

	if (arp_llreach_base != 0 && rt->rt_expire != 0 &&
	    !(rt->rt_ifp->if_flags & IFF_LOOPBACK) &&
	    ifp->if_addrlen == IF_LLREACH_MAXLEN &&	/* Ethernet */
	    alen == ifp->if_addrlen) {
		struct llinfo_arp *la = rt->rt_llinfo;
		struct if_llreach *lr;
		const char *why = NULL, *type = "";

		/* Become a regular mutex, just in case */
		RT_CONVERT_LOCK(rt);

		if ((lr = la->la_llreach) != NULL) {
			type = (solicited ? "ARP reply" : "ARP announcement");
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
				*p_rt_event_code = ROUTE_LLENTRY_CHANGED;
			} else {
				/*
				 * If we were doing unicast probing, we need to
				 * deliver an event for neighbor cache resolution
				 */
				if (lr->lr_probes != 0)
					*p_rt_event_code = ROUTE_LLENTRY_RESOLVED;

				lr->lr_probes = 0;	/* reset probe count */
				IFLR_UNLOCK(lr);
				if (solicited) {
					why = " for same target HW address; "
					    "keeping existing llreach record";
				}
			}
		}

		if (lr == NULL) {
			lr = la->la_llreach = ifnet_llreach_alloc(ifp,
			    ETHERTYPE_IP, addr, alen, arp_llreach_base);
			if (lr != NULL) {
				lr->lr_probes = 0;	/* reset probe count */
				if (why == NULL)
					why = "creating new llreach record";
			}
			*p_rt_event_code = ROUTE_LLENTRY_RESOLVED;
		}

		if (arp_verbose > 1 && lr != NULL && why != NULL) {
			char tmp[MAX_IPv4_STR_LEN];

			log(LOG_DEBUG, "%s: %s%s for %s\n", if_name(ifp),
			    type, why, inet_ntop(AF_INET,
			    &SIN(rt_key(rt))->sin_addr, tmp, sizeof (tmp)));
		}
	}
}