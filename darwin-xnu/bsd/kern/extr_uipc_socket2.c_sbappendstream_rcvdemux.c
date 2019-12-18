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
struct socket {int so_flags; int /*<<< orphan*/  so_rcv; } ;
struct TYPE_2__ {int pkt_flags; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int M_PKTHDR ; 
 int PKTF_MPTCP_DFIN ; 
 int SOF_ENABLE_MSGS ; 
 int SOF_MP_SUBFLOW ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ m_pktlen (struct mbuf*) ; 
 int sbappendmptcpstream_rcv (int /*<<< orphan*/ *,struct mbuf*) ; 
 int sbappendmsgstream_rcv (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ,int) ; 
 int sbappendstream (int /*<<< orphan*/ *,struct mbuf*) ; 

int
sbappendstream_rcvdemux(struct socket *so, struct mbuf *m, uint32_t seqnum,
	int unordered)
{
	int ret = 0;

	if ((m != NULL) &&
	    m_pktlen(m) <= 0 &&
	    !((so->so_flags & SOF_MP_SUBFLOW) &&
	      (m->m_flags & M_PKTHDR) &&
	      (m->m_pkthdr.pkt_flags & PKTF_MPTCP_DFIN))) {
		m_freem(m);
		return (ret);
	}

	if (so->so_flags & SOF_ENABLE_MSGS) {
		ret = sbappendmsgstream_rcv(&so->so_rcv, m, seqnum, unordered);
	}
#if MPTCP
	else if (so->so_flags & SOF_MP_SUBFLOW) {
		ret = sbappendmptcpstream_rcv(&so->so_rcv, m);
	}
#endif /* MPTCP */
	else {
		ret = sbappendstream(&so->so_rcv, m);
	}
	return (ret);
}