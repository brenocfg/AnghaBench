#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mbuf {int dummy; } ;
struct TYPE_3__ {int pktsched_ptype; void* pktsched_pkt; int /*<<< orphan*/  pktsched_plen; } ;
typedef  TYPE_1__ pktsched_pkt_t ;
typedef  int classq_pkt_type_t ;

/* Variables and functions */
#define  QP_MBUF 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_pktlen (struct mbuf*) ; 

void
pktsched_pkt_encap(pktsched_pkt_t *pkt, classq_pkt_type_t ptype, void *pp)
{
	pkt->pktsched_ptype = ptype;
	pkt->pktsched_pkt = pp;

	switch (ptype) {
	case QP_MBUF:
		pkt->pktsched_plen =
		    (uint32_t)m_pktlen((struct mbuf *)pkt->pktsched_pkt);
		break;


	default:
		VERIFY(0);
		/* NOTREACHED */
	}
}