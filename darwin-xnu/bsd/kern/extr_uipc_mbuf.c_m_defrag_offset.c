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
typedef  int u_int32_t ;
struct TYPE_2__ {int len; int /*<<< orphan*/ * pkt_hdr; } ;
struct mbuf {int m_flags; int m_data; int m_len; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int MCLBYTES ; 
 int MHLEN ; 
 int MLEN ; 
 int /*<<< orphan*/  MT_DATA ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  m_cat (struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ m_dup_pkthdr (struct mbuf*,struct mbuf*,int) ; 
 int /*<<< orphan*/  m_fixhdr (struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_get (int,int /*<<< orphan*/ ) ; 
 struct mbuf* m_getcl (int,int /*<<< orphan*/ ,int) ; 
 struct mbuf* m_gethdr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 

struct mbuf *
m_defrag_offset(struct mbuf *m0, u_int32_t off, int how)
{
	struct mbuf *m_new = NULL, *m_final = NULL;
	int progress = 0, length, pktlen;

	if (!(m0->m_flags & M_PKTHDR))
		return (m0);

	VERIFY(off < MHLEN);
	m_fixhdr(m0); /* Needed sanity check */

	pktlen = m0->m_pkthdr.len + off;
	if (pktlen > MHLEN)
		m_final = m_getcl(how, MT_DATA, M_PKTHDR);
	else
		m_final = m_gethdr(how, MT_DATA);

	if (m_final == NULL)
		goto nospace;

	if (off > 0) {
		pktlen -= off;
		m_final->m_data += off;
	}

	/*
	 * Caller must have handled the contents pointed to by this
	 * pointer before coming here, as otherwise it will point to
	 * the original mbuf which will get freed upon success.
	 */
	VERIFY(m0->m_pkthdr.pkt_hdr == NULL);

	if (m_dup_pkthdr(m_final, m0, how) == 0)
		goto nospace;

	m_new = m_final;

	while (progress < pktlen) {
		length = pktlen - progress;
		if (length > MCLBYTES)
			length = MCLBYTES;
		length -= ((m_new == m_final) ? off : 0);
		if (length < 0)
			goto nospace;

		if (m_new == NULL) {
			if (length > MLEN)
				m_new = m_getcl(how, MT_DATA, 0);
			else
				m_new = m_get(how, MT_DATA);
			if (m_new == NULL)
				goto nospace;
		}

		m_copydata(m0, progress, length, mtod(m_new, caddr_t));
		progress += length;
		m_new->m_len = length;
		if (m_new != m_final)
			m_cat(m_final, m_new);
		m_new = NULL;
	}
	m_freem(m0);
	m0 = m_final;
	return (m0);
nospace:
	if (m_final)
		m_freem(m_final);
	return (NULL);
}