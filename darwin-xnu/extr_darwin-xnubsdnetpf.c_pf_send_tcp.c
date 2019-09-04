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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  void* u_int16_t ;
struct tcphdr {int th_off; int /*<<< orphan*/  th_win; int /*<<< orphan*/  th_flags; void* th_ack; void* th_seq; void* th_dport; void* th_sport; } ;
struct pf_rule {int /*<<< orphan*/  rtableid; } ;
struct pf_mtag {int /*<<< orphan*/  pftag_rtableid; void* pftag_tag; int /*<<< orphan*/  pftag_flags; } ;
struct pf_addr {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/ * rcvif; int /*<<< orphan*/  pkt_proto; } ;
struct mbuf {int m_len; int /*<<< orphan*/  m_data; TYPE_1__ m_pkthdr; } ;
struct ifnet {int dummy; } ;
struct ether_header {int dummy; } ;
typedef  int sa_family_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  MT_HEADER ; 
 int /*<<< orphan*/  M_DONTWAIT ; 
 scalar_t__ PF_RTABLEID_IS_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_TAG_GENERATED ; 
 char TCPOPT_MAXSEG ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (void*) ; 
 struct mbuf* m_gethdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ max_linkhdr ; 
 int /*<<< orphan*/  panic (char*) ; 
 struct pf_mtag* pf_get_mtag (struct mbuf*) ; 

__attribute__((used)) static void
pf_send_tcp(const struct pf_rule *r, sa_family_t af,
    const struct pf_addr *saddr, const struct pf_addr *daddr,
    u_int16_t sport, u_int16_t dport, u_int32_t seq, u_int32_t ack,
    u_int8_t flags, u_int16_t win, u_int16_t mss, u_int8_t ttl, int tag,
    u_int16_t rtag, struct ether_header *eh, struct ifnet *ifp)
{
#pragma unused(eh, ifp)
	struct mbuf	*m;
	int		 len, tlen;
#if INET
	struct ip	*h = NULL;
#endif /* INET */
#if INET6
	struct ip6_hdr	*h6 = NULL;
#endif /* INET6 */
	struct tcphdr	*th = NULL;
	char		*opt;
	struct pf_mtag	*pf_mtag;

	/* maximum segment size tcp option */
	tlen = sizeof (struct tcphdr);
	if (mss)
		tlen += 4;

	switch (af) {
#if INET
	case AF_INET:
		len = sizeof (struct ip) + tlen;
		break;
#endif /* INET */
#if INET6
	case AF_INET6:
		len = sizeof (struct ip6_hdr) + tlen;
		break;
#endif /* INET6 */
	default:
		panic("pf_send_tcp: not AF_INET or AF_INET6!");
		return;
	}

	/* create outgoing mbuf */
	m = m_gethdr(M_DONTWAIT, MT_HEADER);
	if (m == NULL)
		return;

	if ((pf_mtag = pf_get_mtag(m)) == NULL)
		return;

	if (tag)
		pf_mtag->pftag_flags |= PF_TAG_GENERATED;
	pf_mtag->pftag_tag = rtag;

	if (r != NULL && PF_RTABLEID_IS_VALID(r->rtableid))
		pf_mtag->pftag_rtableid = r->rtableid;

#if PF_ECN
	/* add hints for ecn */
	pf_mtag->pftag_hdr = mtod(m, struct ip *);
	/* record address family */
	pf_mtag->pftag_flags &= ~(PF_TAG_HDR_INET | PF_TAG_HDR_INET6);
	switch (af) {
#if INET
	case AF_INET:
		pf_mtag->pftag_flags |= PF_TAG_HDR_INET;
		break;
#endif /* INET */
#if INET6
	case AF_INET6:
		pf_mtag->pftag_flags |= PF_TAG_HDR_INET6;
		break;
#endif /* INET6 */
	}
#endif /* PF_ECN */

	/* indicate this is TCP */
	m->m_pkthdr.pkt_proto = IPPROTO_TCP;

	/* Make sure headers are 32-bit aligned */
	m->m_data += max_linkhdr;
	m->m_pkthdr.len = m->m_len = len;
	m->m_pkthdr.rcvif = NULL;
	bzero(m->m_data, len);
	switch (af) {
#if INET
	case AF_INET:
		h = mtod(m, struct ip *);

		/* IP header fields included in the TCP checksum */
		h->ip_p = IPPROTO_TCP;
		h->ip_len = htons(tlen);
		h->ip_src.s_addr = saddr->v4addr.s_addr;
		h->ip_dst.s_addr = daddr->v4addr.s_addr;

		th = (struct tcphdr *)(void *)((caddr_t)h + sizeof (struct ip));
		break;
#endif /* INET */
#if INET6
	case AF_INET6:
		h6 = mtod(m, struct ip6_hdr *);

		/* IP header fields included in the TCP checksum */
		h6->ip6_nxt = IPPROTO_TCP;
		h6->ip6_plen = htons(tlen);
		memcpy(&h6->ip6_src, &saddr->v6addr, sizeof (struct in6_addr));
		memcpy(&h6->ip6_dst, &daddr->v6addr, sizeof (struct in6_addr));

		th = (struct tcphdr *)(void *)
		    ((caddr_t)h6 + sizeof (struct ip6_hdr));
		break;
#endif /* INET6 */
	}

	/* TCP header */
	th->th_sport = sport;
	th->th_dport = dport;
	th->th_seq = htonl(seq);
	th->th_ack = htonl(ack);
	th->th_off = tlen >> 2;
	th->th_flags = flags;
	th->th_win = htons(win);

	if (mss) {
		opt = (char *)(th + 1);
		opt[0] = TCPOPT_MAXSEG;
		opt[1] = 4;
#if BYTE_ORDER != BIG_ENDIAN
		HTONS(mss);
#endif
		bcopy((caddr_t)&mss, (caddr_t)(opt + 2), 2);
	}

	switch (af) {
#if INET
	case AF_INET: {
		struct route ro;

		/* TCP checksum */
		th->th_sum = in_cksum(m, len);

		/* Finish the IP header */
		h->ip_v = 4;
		h->ip_hl = sizeof (*h) >> 2;
		h->ip_tos = IPTOS_LOWDELAY;
		/*
		 * ip_output() expects ip_len and ip_off to be in host order.
		 */
		h->ip_len = len;
		h->ip_off = (path_mtu_discovery ? IP_DF : 0);
		h->ip_ttl = ttl ? ttl : ip_defttl;
		h->ip_sum = 0;

		bzero(&ro, sizeof (ro));
		ip_output(m, NULL, &ro, 0, NULL, NULL);
		ROUTE_RELEASE(&ro);
		break;
	}
#endif /* INET */
#if INET6
	case AF_INET6: {
		struct route_in6 ro6;

		/* TCP checksum */
		th->th_sum = in6_cksum(m, IPPROTO_TCP,
		    sizeof (struct ip6_hdr), tlen);

		h6->ip6_vfc |= IPV6_VERSION;
		h6->ip6_hlim = IPV6_DEFHLIM;

		bzero(&ro6, sizeof (ro6));
		ip6_output(m, NULL, &ro6, 0, NULL, NULL, NULL);
		ROUTE_RELEASE(&ro6);
		break;
	}
#endif /* INET6 */
	}
}