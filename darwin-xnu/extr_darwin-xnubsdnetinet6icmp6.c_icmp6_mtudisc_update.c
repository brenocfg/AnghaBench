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
typedef  int u_int ;
struct in6_addr {int /*<<< orphan*/ * s6_addr16; } ;
struct sockaddr_in6 {int sin6_len; struct in6_addr sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_7__ {int rmx_locks; int rmx_mtu; } ;
struct rtentry {int rt_flags; TYPE_3__ rt_rmx; int /*<<< orphan*/  rt_ifp; } ;
struct TYPE_6__ {TYPE_1__* rcvif; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct ip6ctlparam {struct mbuf* ip6c_m; struct icmp6_hdr* ip6c_icmp6; struct in6_addr* ip6c_finaldst; } ;
struct ip6_hdr {int dummy; } ;
struct ip6_frag {int dummy; } ;
struct icmp6_hdr {int /*<<< orphan*/  icmp6_mtu; } ;
typedef  int /*<<< orphan*/  sin6 ;
struct TYPE_8__ {int /*<<< orphan*/  icp6s_pmtuchg; } ;
struct TYPE_5__ {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 scalar_t__ IN6_IS_ADDR_LINKLOCAL (struct in6_addr*) ; 
 int IN6_LINKMTU (int /*<<< orphan*/ ) ; 
 int IPV6_MMTU ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int RTF_CLONING ; 
 int RTF_HOST ; 
 int RTF_PRCLONING ; 
 int RTV_MTU ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 TYPE_4__ icmp6stat ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 struct rtentry* rtalloc1_scoped (struct sockaddr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtfree (struct rtentry*) ; 

void
icmp6_mtudisc_update(struct ip6ctlparam *ip6cp, int validated)
{
	struct in6_addr *dst = ip6cp->ip6c_finaldst;
	struct icmp6_hdr *icmp6 = ip6cp->ip6c_icmp6;
	struct mbuf *m = ip6cp->ip6c_m;	/* will be necessary for scope issue */
	u_int mtu = ntohl(icmp6->icmp6_mtu);
	struct rtentry *rt = NULL;
	struct sockaddr_in6 sin6;
	/*
	 * we reject ICMPv6 too big with abnormally small value.
	 * XXX what is the good definition of "abnormally small"?
	 */
	if (mtu < sizeof(struct ip6_hdr) + sizeof(struct ip6_frag) + 8)
		return;

	if (!validated)
		return;

	/*
	 * In case the suggested mtu is less than IPV6_MMTU, we
	 * only need to remember that it was for above mentioned
	 * "alwaysfrag" case.
	 * Try to be as close to the spec as possible.
	 */
	if (mtu < IPV6_MMTU)
		mtu = IPV6_MMTU - 8;

	bzero(&sin6, sizeof(sin6));
	sin6.sin6_family = PF_INET6;
	sin6.sin6_len = sizeof(struct sockaddr_in6);
	sin6.sin6_addr = *dst;
	/* XXX normally, this won't happen */
	if (IN6_IS_ADDR_LINKLOCAL(dst)) {
		sin6.sin6_addr.s6_addr16[1] =
		    htons(m->m_pkthdr.rcvif->if_index);
	}
	/* sin6.sin6_scope_id = XXX: should be set if DST is a scoped addr */
	/*
	 * XXX On a side note, for asymmetric data-path
	 * the lookup on receive interace is probably not
	 * what we want to do.
	 * That requires looking at the cached route for the
	 * protocol control block.
	 */
	rt = rtalloc1_scoped((struct sockaddr *)&sin6, 0,
	    RTF_CLONING | RTF_PRCLONING, m->m_pkthdr.rcvif->if_index);
	if (rt != NULL) {
		RT_LOCK(rt);
		if ((rt->rt_flags & RTF_HOST) &&
		    !(rt->rt_rmx.rmx_locks & RTV_MTU) &&
		    mtu < IN6_LINKMTU(rt->rt_ifp) &&
		    rt->rt_rmx.rmx_mtu > mtu) {
			icmp6stat.icp6s_pmtuchg++;
			rt->rt_rmx.rmx_mtu = mtu;
		}
		RT_UNLOCK(rt);
		rtfree(rt);
	}
}