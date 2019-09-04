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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {struct mbuf* sb_mb; } ;
struct socket {TYPE_1__ so_snd; } ;
struct TYPE_4__ {scalar_t__ mp_dsn; int pkt_flags; scalar_t__ mp_rlen; } ;
struct mbuf {int m_flags; struct mbuf* m_next; TYPE_2__ m_pkthdr; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int M_PKTHDR ; 
 int PKTF_MPTCP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 

__attribute__((used)) static boolean_t
mptcp_search_seq_in_sub(struct mbuf *m, struct socket *so)
{
	struct mbuf *so_m = so->so_snd.sb_mb;
	uint64_t dsn = m->m_pkthdr.mp_dsn;

	while (so_m) {
		VERIFY(so_m->m_flags & M_PKTHDR);
		VERIFY(so_m->m_pkthdr.pkt_flags & PKTF_MPTCP);

		/* Part of the segment is covered, don't reinject here */
		if (so_m->m_pkthdr.mp_dsn <= dsn &&
		    so_m->m_pkthdr.mp_dsn + so_m->m_pkthdr.mp_rlen > dsn)
			return TRUE;

		so_m = so_m->m_next;
	}

	return FALSE;
}