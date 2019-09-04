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
struct TYPE_2__ {int len; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;
struct ip6_hdr {int ip6_nxt; } ;
struct ip6_frag {int ip6f_offlg; int ip6f_nxt; } ;
struct ip6_ext {int ip6e_nxt; int /*<<< orphan*/  ip6e_len; } ;
typedef  int /*<<< orphan*/  ip6e ;
typedef  int /*<<< orphan*/  ip6 ;
typedef  int /*<<< orphan*/  fh ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int IP6F_OFF_MASK ; 
#define  IPPROTO_AH 136 
#define  IPPROTO_DSTOPTS 135 
#define  IPPROTO_ESP 134 
#define  IPPROTO_FRAGMENT 133 
#define  IPPROTO_HOPOPTS 132 
#define  IPPROTO_IPCOMP 131 
#define  IPPROTO_IPV6 130 
#define  IPPROTO_NONE 129 
#define  IPPROTO_ROUTING 128 
 int M_PKTHDR ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int,int,int /*<<< orphan*/ ) ; 

int
ip6_nexthdr(struct mbuf *m, int off, int proto, int *nxtp)
{
	struct ip6_hdr ip6;
	struct ip6_ext ip6e;
	struct ip6_frag fh;

	/* just in case */
	VERIFY(m != NULL);
	if ((m->m_flags & M_PKTHDR) == 0 || m->m_pkthdr.len < off)
		return (-1);

	switch (proto) {
	case IPPROTO_IPV6:
		if (m->m_pkthdr.len < off + sizeof (ip6))
			return (-1);
		m_copydata(m, off, sizeof (ip6), (caddr_t)&ip6);
		if (nxtp)
			*nxtp = ip6.ip6_nxt;
		off += sizeof (ip6);
		return (off);

	case IPPROTO_FRAGMENT:
		/*
		 * terminate parsing if it is not the first fragment,
		 * it does not make sense to parse through it.
		 */
		if (m->m_pkthdr.len < off + sizeof (fh))
			return (-1);
		m_copydata(m, off, sizeof (fh), (caddr_t)&fh);
		/* IP6F_OFF_MASK = 0xfff8(BigEndian), 0xf8ff(LittleEndian) */
		if (fh.ip6f_offlg & IP6F_OFF_MASK)
			return (-1);
		if (nxtp)
			*nxtp = fh.ip6f_nxt;
		off += sizeof (struct ip6_frag);
		return (off);

	case IPPROTO_AH:
		if (m->m_pkthdr.len < off + sizeof (ip6e))
			return (-1);
		m_copydata(m, off, sizeof (ip6e), (caddr_t)&ip6e);
		if (nxtp)
			*nxtp = ip6e.ip6e_nxt;
		off += (ip6e.ip6e_len + 2) << 2;
		return (off);

	case IPPROTO_HOPOPTS:
	case IPPROTO_ROUTING:
	case IPPROTO_DSTOPTS:
		if (m->m_pkthdr.len < off + sizeof (ip6e))
			return (-1);
		m_copydata(m, off, sizeof (ip6e), (caddr_t)&ip6e);
		if (nxtp)
			*nxtp = ip6e.ip6e_nxt;
		off += (ip6e.ip6e_len + 1) << 3;
		return (off);

	case IPPROTO_NONE:
	case IPPROTO_ESP:
	case IPPROTO_IPCOMP:
		/* give up */
		return (-1);

	default:
		return (-1);
	}
}