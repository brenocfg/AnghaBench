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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct pkthdr {int /*<<< orphan*/  tx_start_seq; int /*<<< orphan*/  pkt_proto; int /*<<< orphan*/  pkt_flowsrc; int /*<<< orphan*/  pkt_flowid; int /*<<< orphan*/  pkt_timestamp; int /*<<< orphan*/  pkt_flags; } ;
struct mbuf {struct pkthdr m_pkthdr; } ;
struct TYPE_3__ {int pktsched_ptype; scalar_t__ pktsched_pkt; } ;
typedef  TYPE_1__ pktsched_pkt_t ;

/* Variables and functions */
#define  QP_MBUF 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 

void
pktsched_get_pkt_vars(pktsched_pkt_t *pkt, uint32_t **flags,
    uint64_t **timestamp, uint32_t *flowid, uint8_t *flowsrc, uint8_t *proto,
    uint32_t *tcp_start_seq)
{
	switch (pkt->pktsched_ptype) {
	case QP_MBUF: {
		struct mbuf *m = (struct mbuf *)pkt->pktsched_pkt;
		struct pkthdr *pkth = &m->m_pkthdr;

		if (flags != NULL)
			*flags = &pkth->pkt_flags;
		if (timestamp != NULL)
			*timestamp = &pkth->pkt_timestamp;
		if (flowid != NULL)
			*flowid = pkth->pkt_flowid;
		if (flowsrc != NULL)
			*flowsrc = pkth->pkt_flowsrc;
		if (proto != NULL)
			*proto = pkth->pkt_proto;
		/*
		 * caller should use this value only if PKTF_START_SEQ
		 * is set in the mbuf packet flags
		 */
		if (tcp_start_seq != NULL)
			*tcp_start_seq = pkth->tx_start_seq;

		break;
	}


	default:
		VERIFY(0);
		/* NOTREACHED */
	}
}