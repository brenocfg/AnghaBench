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
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_2__ {int len; struct ifnet* rcvif; } ;
struct mbuf {int m_len; int m_flags; int m_data; struct mbuf* m_next; TYPE_1__ m_pkthdr; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCLGET (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MC_CL ; 
 int MHLEN ; 
 int MIN (int,int) ; 
 int MINCLSIZE ; 
 int MLEN ; 
 int /*<<< orphan*/  MTOD (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_DONTWAIT ; 
 int M_EXT ; 
 int /*<<< orphan*/  _MGET (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MGETHDR (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int m_maxsize (int /*<<< orphan*/ ) ; 
 int max_linkhdr ; 

struct mbuf *
m_devget(char *buf, int totlen, int off0, struct ifnet *ifp,
    void (*copy)(const void *, void *, size_t))
{
	struct mbuf *m;
	struct mbuf *top = NULL, **mp = &top;
	int off = off0, len;
	char *cp;
	char *epkt;

	cp = buf;
	epkt = cp + totlen;
	if (off) {
		/*
		 * If 'off' is non-zero, packet is trailer-encapsulated,
		 * so we have to skip the type and length fields.
		 */
		cp += off + 2 * sizeof (u_int16_t);
		totlen -= 2 * sizeof (u_int16_t);
	}
	_MGETHDR(m, M_DONTWAIT, MT_DATA);
	if (m == NULL)
		return (NULL);
	m->m_pkthdr.rcvif = ifp;
	m->m_pkthdr.len = totlen;
	m->m_len = MHLEN;

	while (totlen > 0) {
		if (top != NULL) {
			_MGET(m, M_DONTWAIT, MT_DATA);
			if (m == NULL) {
				m_freem(top);
				return (NULL);
			}
			m->m_len = MLEN;
		}
		len = MIN(totlen, epkt - cp);
		if (len >= MINCLSIZE) {
			MCLGET(m, M_DONTWAIT);
			if (m->m_flags & M_EXT) {
				m->m_len = len = MIN(len, m_maxsize(MC_CL));
			} else {
				/* give up when it's out of cluster mbufs */
				if (top != NULL)
					m_freem(top);
				m_freem(m);
				return (NULL);
			}
		} else {
			/*
			 * Place initial small packet/header at end of mbuf.
			 */
			if (len < m->m_len) {
				if (top == NULL &&
				    len + max_linkhdr <= m->m_len)
					m->m_data += max_linkhdr;
				m->m_len = len;
			} else {
				len = m->m_len;
			}
		}
		if (copy)
			copy(cp, MTOD(m, caddr_t), (unsigned)len);
		else
			bcopy(cp, MTOD(m, caddr_t), (unsigned)len);
		cp += len;
		*mp = m;
		mp = &m->m_next;
		totlen -= len;
		if (cp == epkt)
			cp = buf;
	}
	return (top);
}