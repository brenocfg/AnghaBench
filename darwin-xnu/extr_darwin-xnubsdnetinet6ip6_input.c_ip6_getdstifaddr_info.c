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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int pkt_flags; int /*<<< orphan*/  dst_iff; int /*<<< orphan*/  dst_ifindex; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int M_PKTHDR ; 
 int PKTF_IFAINFO ; 
 int /*<<< orphan*/  VERIFY (int) ; 

int
ip6_getdstifaddr_info(struct mbuf *m, uint32_t *dst_idx, uint32_t *ia6f)
{
	VERIFY(m->m_flags & M_PKTHDR);

	if (!(m->m_pkthdr.pkt_flags & PKTF_IFAINFO))
		return (-1);

	if (dst_idx != NULL)
		*dst_idx = m->m_pkthdr.dst_ifindex;

	if (ia6f != NULL)
		*ia6f = m->m_pkthdr.dst_iff;

	return (0);
}