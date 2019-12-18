#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int dst_iff; int /*<<< orphan*/  pkt_flags; scalar_t__ dst_ifindex; } ;
struct mbuf {int m_flags; TYPE_2__ m_pkthdr; } ;
struct in6_ifaddr {int ia6_flags; TYPE_1__* ia_ifp; } ;
struct TYPE_3__ {scalar_t__ if_index; } ;

/* Variables and functions */
 int M_PKTHDR ; 
 int /*<<< orphan*/  PKTF_IFAINFO ; 
 int /*<<< orphan*/  VERIFY (int) ; 

void
ip6_setdstifaddr_info(struct mbuf *m, uint32_t dst_idx, struct in6_ifaddr *ia6)
{
	VERIFY(m->m_flags & M_PKTHDR);

	/*
	 * If the destination ifaddr is specified, pick up the information
	 * from there; otherwise just grab the passed-in ifindex as the
	 * caller may not have the ifaddr available.
	 */
	if (ia6 != NULL) {
		m->m_pkthdr.pkt_flags |= PKTF_IFAINFO;
		m->m_pkthdr.dst_ifindex = ia6->ia_ifp->if_index;

		/* See IN6_IFF comments in in6_var.h */
		m->m_pkthdr.dst_iff = (ia6->ia6_flags & 0xffff);
	} else {
		m->m_pkthdr.dst_iff = 0;
		m->m_pkthdr.dst_ifindex = dst_idx;
		if (dst_idx != 0)
			m->m_pkthdr.pkt_flags |= PKTF_IFAINFO;
	}
}