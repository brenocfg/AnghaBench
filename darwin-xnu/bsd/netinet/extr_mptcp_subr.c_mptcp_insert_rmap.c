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
struct tcphdr {int th_flags; } ;
struct TYPE_3__ {scalar_t__ mpt_dfin; int /*<<< orphan*/  mpt_csum; int /*<<< orphan*/  mpt_len; int /*<<< orphan*/  mpt_sseq; int /*<<< orphan*/  mpt_dsn; } ;
struct tcpcb {int t_mpflags; TYPE_1__ t_rcv_map; } ;
struct TYPE_4__ {int pkt_flags; int /*<<< orphan*/  mp_csum; int /*<<< orphan*/  mp_rlen; int /*<<< orphan*/  mp_rseq; int /*<<< orphan*/  mp_dsn; } ;
struct mbuf {int m_flags; TYPE_2__ m_pkthdr; } ;

/* Variables and functions */
 int M_PKTHDR ; 
 int PKTF_MPTCP ; 
 int PKTF_MPTCP_DFIN ; 
 int TH_FIN ; 
 int TMPF_EMBED_DSN ; 
 int TMPF_MPTCP_ACKNOW ; 
 int TMPF_TCP_FALLBACK ; 
 int /*<<< orphan*/  VERIFY (int) ; 

void
mptcp_insert_rmap(struct tcpcb *tp, struct mbuf *m, struct tcphdr *th)
{
	VERIFY(m->m_flags & M_PKTHDR);
	VERIFY(!(m->m_pkthdr.pkt_flags & PKTF_MPTCP));

	if (tp->t_mpflags & TMPF_EMBED_DSN) {
		m->m_pkthdr.mp_dsn = tp->t_rcv_map.mpt_dsn;
		m->m_pkthdr.mp_rseq = tp->t_rcv_map.mpt_sseq;
		m->m_pkthdr.mp_rlen = tp->t_rcv_map.mpt_len;
		m->m_pkthdr.mp_csum = tp->t_rcv_map.mpt_csum;
		if (tp->t_rcv_map.mpt_dfin)
			m->m_pkthdr.pkt_flags |= PKTF_MPTCP_DFIN;

		m->m_pkthdr.pkt_flags |= PKTF_MPTCP;

		tp->t_mpflags &= ~TMPF_EMBED_DSN;
		tp->t_mpflags |= TMPF_MPTCP_ACKNOW;
	} else if (tp->t_mpflags & TMPF_TCP_FALLBACK) {
		if (th->th_flags & TH_FIN)
			m->m_pkthdr.pkt_flags |= PKTF_MPTCP_DFIN;
	}
}