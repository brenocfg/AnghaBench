#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  TYPE_2__* mbuf_t ;
typedef  int mbuf_pkthdr_aux_flags_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {int pkt_flags; } ;
struct TYPE_5__ {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int MBUF_PKTAUXF_INET6_RESOLVE_RTR ; 
 int MBUF_PKTAUXF_INET_RESOLVE_RTR ; 
 int M_PKTHDR ; 
 int PKTF_INET6_RESOLVE ; 
 int PKTF_INET_RESOLVE ; 
 int PKTF_RESOLVE_RTR ; 
 int /*<<< orphan*/  VERIFY (int) ; 

errno_t
mbuf_pkthdr_aux_flags(mbuf_t m, mbuf_pkthdr_aux_flags_t *flagsp)
{
	u_int32_t flags;

	if (m == NULL || !(m->m_flags & M_PKTHDR) || flagsp == NULL)
		return (EINVAL);

	*flagsp = 0;
	flags = m->m_pkthdr.pkt_flags;
	if ((flags & (PKTF_INET_RESOLVE|PKTF_RESOLVE_RTR)) ==
	    (PKTF_INET_RESOLVE|PKTF_RESOLVE_RTR))
		*flagsp |= MBUF_PKTAUXF_INET_RESOLVE_RTR;
	if ((flags & (PKTF_INET6_RESOLVE|PKTF_RESOLVE_RTR)) ==
	    (PKTF_INET6_RESOLVE|PKTF_RESOLVE_RTR))
		*flagsp |= MBUF_PKTAUXF_INET6_RESOLVE_RTR;

	/* These 2 flags are mutually exclusive */
	VERIFY((*flagsp &
	    (MBUF_PKTAUXF_INET_RESOLVE_RTR | MBUF_PKTAUXF_INET6_RESOLVE_RTR)) !=
	    (MBUF_PKTAUXF_INET_RESOLVE_RTR | MBUF_PKTAUXF_INET6_RESOLVE_RTR));

	return (0);
}