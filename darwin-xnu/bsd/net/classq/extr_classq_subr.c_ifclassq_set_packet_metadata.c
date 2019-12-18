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
struct TYPE_2__ {int /*<<< orphan*/  bufstatus_sndbuf; int /*<<< orphan*/  bufstatus_if; int /*<<< orphan*/  pkt_flags; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int /*<<< orphan*/  if_sndbyte_unsent; } ;
struct ifclassq {int dummy; } ;
typedef  int classq_pkt_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_BYTES (struct ifclassq*) ; 
 int /*<<< orphan*/  IFNET_IS_CELLULAR (struct ifnet*) ; 
 int /*<<< orphan*/  PKTF_VALID_UNSENT_DATA ; 
#define  QP_MBUF 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 

inline void
ifclassq_set_packet_metadata(struct ifclassq *ifq, struct ifnet *ifp,
    void *p, classq_pkt_type_t ptype)
{
	if (!IFNET_IS_CELLULAR(ifp))
		return;

	switch (ptype) {
	case QP_MBUF: {
		struct mbuf *m = p;
		m->m_pkthdr.pkt_flags |= PKTF_VALID_UNSENT_DATA;
		m->m_pkthdr.bufstatus_if = IFCQ_BYTES(ifq);
		m->m_pkthdr.bufstatus_sndbuf = ifp->if_sndbyte_unsent;
		break;
	}


	default:
		VERIFY(0);
		/* NOTREACHED */
	}
}