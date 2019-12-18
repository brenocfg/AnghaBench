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
struct pkthdr {int /*<<< orphan*/  pkt_mpriv_hash; int /*<<< orphan*/  pkt_mpriv_flags; } ;
struct mbuf {struct pkthdr m_pkthdr; } ;
struct TYPE_3__ {int pktsched_ptype; scalar_t__ pktsched_pkt; } ;
typedef  TYPE_1__ pktsched_pkt_t ;

/* Variables and functions */
#define  QP_MBUF 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CASSERT (int) ; 

uint32_t *
pktsched_get_pkt_sfb_vars(pktsched_pkt_t *pkt, uint32_t **sfb_flags)
{
	uint32_t *hashp = NULL;

	switch (pkt->pktsched_ptype) {
	case QP_MBUF: {
		struct mbuf *m = (struct mbuf *)pkt->pktsched_pkt;
		struct pkthdr *pkth = &m->m_pkthdr;

		_CASSERT(sizeof (pkth->pkt_mpriv_hash) == sizeof (uint32_t));
		_CASSERT(sizeof (pkth->pkt_mpriv_flags) == sizeof (uint32_t));

		*sfb_flags = &pkth->pkt_mpriv_flags;
		hashp = &pkth->pkt_mpriv_hash;
		break;
	}


	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (hashp);
}