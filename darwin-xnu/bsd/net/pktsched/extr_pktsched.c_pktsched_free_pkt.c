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
struct TYPE_3__ {int pktsched_ptype; scalar_t__ pktsched_plen; int /*<<< orphan*/ * pktsched_pkt; } ;
typedef  TYPE_1__ pktsched_pkt_t ;

/* Variables and functions */
#define  QP_MBUF 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

void
pktsched_free_pkt(pktsched_pkt_t *pkt)
{
	switch (pkt->pktsched_ptype) {
	case QP_MBUF:
		m_freem(pkt->pktsched_pkt);
		break;


	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	pkt->pktsched_pkt = NULL;
	pkt->pktsched_plen = 0;
	pkt->pktsched_ptype = 0;
}