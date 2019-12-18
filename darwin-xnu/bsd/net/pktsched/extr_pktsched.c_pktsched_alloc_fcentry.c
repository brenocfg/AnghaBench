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
struct TYPE_4__ {int /*<<< orphan*/  pkt_flowid; int /*<<< orphan*/  pkt_flowsrc; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int dummy; } ;
struct flowadv_fcentry {int /*<<< orphan*/  fce_flowid; int /*<<< orphan*/  fce_flowsrc_type; } ;
struct TYPE_5__ {int pktsched_ptype; scalar_t__ pktsched_pkt; } ;
typedef  TYPE_2__ pktsched_pkt_t ;

/* Variables and functions */
#define  QP_MBUF 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CASSERT (int) ; 
 struct flowadv_fcentry* flowadv_alloc_entry (int) ; 

struct flowadv_fcentry *
pktsched_alloc_fcentry(pktsched_pkt_t *pkt, struct ifnet *ifp, int how)
{
#pragma unused(ifp)
	struct flowadv_fcentry *fce = NULL;

	switch (pkt->pktsched_ptype) {
	case QP_MBUF: {
		struct mbuf *m = (struct mbuf *)pkt->pktsched_pkt;

		fce = flowadv_alloc_entry(how);
		if (fce == NULL)
			break;

		_CASSERT(sizeof (m->m_pkthdr.pkt_flowid) ==
		    sizeof (fce->fce_flowid));

		fce->fce_flowsrc_type = m->m_pkthdr.pkt_flowsrc;
		fce->fce_flowid = m->m_pkthdr.pkt_flowid;
		break;
	}


	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (fce);
}