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
typedef  int /*<<< orphan*/  u_int8_t ;
struct pf_rule {int /*<<< orphan*/  rtableid; } ;
struct pf_mtag {int /*<<< orphan*/  pftag_rtableid; int /*<<< orphan*/  pftag_flags; } ;
struct mbuf {int dummy; } ;
typedef  int sa_family_t ;
typedef  int /*<<< orphan*/  pbuf_t ;

/* Variables and functions */
 scalar_t__ PF_RTABLEID_IS_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_TAG_GENERATED ; 
 struct mbuf* pbuf_clone_to_mbuf (int /*<<< orphan*/ *) ; 
 struct pf_mtag* pf_get_mtag (struct mbuf*) ; 

__attribute__((used)) static void
pf_send_icmp(pbuf_t *pbuf, u_int8_t type, u_int8_t code, sa_family_t af,
    struct pf_rule *r)
{
	struct mbuf	*m0;
	struct pf_mtag	*pf_mtag;

	m0 = pbuf_clone_to_mbuf(pbuf);
	if (m0 == NULL)
		return;

	if ((pf_mtag = pf_get_mtag(m0)) == NULL)
		return;

	pf_mtag->pftag_flags |= PF_TAG_GENERATED;

	if (PF_RTABLEID_IS_VALID(r->rtableid))
		pf_mtag->pftag_rtableid = r->rtableid;

#if PF_ECN
	/* add hints for ecn */
	pf_mtag->pftag_hdr = mtod(m0, struct ip *);
	/* record address family */
	pf_mtag->pftag_flags &= ~(PF_TAG_HDR_INET | PF_TAG_HDR_INET6);
	switch (af) {
#if INET
	case AF_INET:
		pf_mtag->pftag_flags |= PF_TAG_HDR_INET;
		m0->m_pkthdr.pkt_proto = IPPROTO_ICMP;
		break;
#endif /* INET */
#if INET6
	case AF_INET6:
		pf_mtag->pftag_flags |= PF_TAG_HDR_INET6;
		m0->m_pkthdr.pkt_proto = IPPROTO_ICMPV6;
		break;
#endif /* INET6 */
	}
#endif /* PF_ECN */

	switch (af) {
#if INET
	case AF_INET:
		icmp_error(m0, type, code, 0, 0);
		break;
#endif /* INET */
#if INET6
	case AF_INET6:
		icmp6_error(m0, type, code, 0);
		break;
#endif /* INET6 */
	}
}