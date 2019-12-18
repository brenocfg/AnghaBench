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
struct sockopt {int dummy; } ;
struct ip6_pktopts {int ip6po_flags; int /*<<< orphan*/  ip6po_prefer_tempaddr; int /*<<< orphan*/  ip6po_minmtu; TYPE_1__* ip6po_nexthop; scalar_t__ ip6po_dest2; scalar_t__ ip6po_dest1; scalar_t__ ip6po_rthdr; scalar_t__ ip6po_hbh; int /*<<< orphan*/  ip6po_tclass; scalar_t__ ip6po_pktinfo; } ;
struct ip6_ext {int /*<<< orphan*/  ip6e_len; } ;
struct in6_pktinfo {int dummy; } ;
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  null_pktinfo ;
struct TYPE_2__ {int sa_len; } ;

/* Variables and functions */
 int ENOPROTOOPT ; 
 int IP6PO_DONTFRAG ; 
 int IP6PO_MINMTU_MCASTONLY ; 
 int IP6PO_TEMPADDR_SYSTEM ; 
#define  IPV6_DONTFRAG 137 
#define  IPV6_DSTOPTS 136 
#define  IPV6_HOPOPTS 135 
#define  IPV6_NEXTHOP 134 
#define  IPV6_PKTINFO 133 
#define  IPV6_PREFER_TEMPADDR 132 
#define  IPV6_RTHDR 131 
#define  IPV6_RTHDRDSTOPTS 130 
#define  IPV6_TCLASS 129 
#define  IPV6_USE_MIN_MTU 128 
 int /*<<< orphan*/  bzero (struct in6_pktinfo*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int sooptcopyout (struct sockopt*,void*,int) ; 

__attribute__((used)) static int
ip6_getpcbopt(struct ip6_pktopts *pktopt, int optname, struct sockopt *sopt)
{
	void *optdata = NULL;
	int optdatalen = 0;
	struct ip6_ext *ip6e;
	struct in6_pktinfo null_pktinfo;
	int deftclass = 0, on;
	int defminmtu = IP6PO_MINMTU_MCASTONLY;
	int defpreftemp = IP6PO_TEMPADDR_SYSTEM;


	switch (optname) {
	case IPV6_PKTINFO:
		if (pktopt && pktopt->ip6po_pktinfo)
			optdata = (void *)pktopt->ip6po_pktinfo;
		else {
			/* XXX: we don't have to do this every time... */
			bzero(&null_pktinfo, sizeof (null_pktinfo));
			optdata = (void *)&null_pktinfo;
		}
		optdatalen = sizeof (struct in6_pktinfo);
		break;

	case IPV6_TCLASS:
		if (pktopt && pktopt->ip6po_tclass >= 0)
			optdata = (void *)&pktopt->ip6po_tclass;
		else
			optdata = (void *)&deftclass;
		optdatalen = sizeof (int);
		break;

	case IPV6_HOPOPTS:
		if (pktopt && pktopt->ip6po_hbh) {
			optdata = (void *)pktopt->ip6po_hbh;
			ip6e = (struct ip6_ext *)pktopt->ip6po_hbh;
			optdatalen = (ip6e->ip6e_len + 1) << 3;
		}
		break;

	case IPV6_RTHDR:
		if (pktopt && pktopt->ip6po_rthdr) {
			optdata = (void *)pktopt->ip6po_rthdr;
			ip6e = (struct ip6_ext *)pktopt->ip6po_rthdr;
			optdatalen = (ip6e->ip6e_len + 1) << 3;
		}
		break;

	case IPV6_RTHDRDSTOPTS:
		if (pktopt && pktopt->ip6po_dest1) {
			optdata = (void *)pktopt->ip6po_dest1;
			ip6e = (struct ip6_ext *)pktopt->ip6po_dest1;
			optdatalen = (ip6e->ip6e_len + 1) << 3;
		}
		break;

	case IPV6_DSTOPTS:
		if (pktopt && pktopt->ip6po_dest2) {
			optdata = (void *)pktopt->ip6po_dest2;
			ip6e = (struct ip6_ext *)pktopt->ip6po_dest2;
			optdatalen = (ip6e->ip6e_len + 1) << 3;
		}
		break;

	case IPV6_NEXTHOP:
		if (pktopt && pktopt->ip6po_nexthop) {
			optdata = (void *)pktopt->ip6po_nexthop;
			optdatalen = pktopt->ip6po_nexthop->sa_len;
		}
		break;

	case IPV6_USE_MIN_MTU:
		if (pktopt)
			optdata = (void *)&pktopt->ip6po_minmtu;
		else
			optdata = (void *)&defminmtu;
		optdatalen = sizeof (int);
		break;

	case IPV6_DONTFRAG:
		if (pktopt && ((pktopt->ip6po_flags) & IP6PO_DONTFRAG))
			on = 1;
		else
			on = 0;
		optdata = (void *)&on;
		optdatalen = sizeof (on);
		break;

	case IPV6_PREFER_TEMPADDR:
		if (pktopt)
			optdata = (void *)&pktopt->ip6po_prefer_tempaddr;
		else
			optdata = (void *)&defpreftemp;
		optdatalen = sizeof (int);
		break;

	default:		/* should not happen */
#ifdef DIAGNOSTIC
		panic("ip6_getpcbopt: unexpected option\n");
#endif
		return (ENOPROTOOPT);
	}

	return (sooptcopyout(sopt, optdata, optdatalen));
}