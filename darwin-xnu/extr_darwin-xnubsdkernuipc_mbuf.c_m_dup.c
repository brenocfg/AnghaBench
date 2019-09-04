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
struct TYPE_2__ {scalar_t__ len; } ;
struct mbuf {int m_flags; scalar_t__ m_len; struct mbuf* m_next; int /*<<< orphan*/  m_pktdat; int /*<<< orphan*/  m_data; int /*<<< orphan*/  m_type; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCLGET (struct mbuf*,int) ; 
 int /*<<< orphan*/  MC_16KCL ; 
 int /*<<< orphan*/  MC_BIGCL ; 
 int /*<<< orphan*/  MC_CL ; 
 int /*<<< orphan*/  MDFail ; 
 scalar_t__ MHLEN ; 
 unsigned int MLEN ; 
 int /*<<< orphan*/  MTOD (struct mbuf*,int /*<<< orphan*/ ) ; 
 int M_EXT ; 
 int M_PKTHDR ; 
 struct mbuf* _M_GET (int,int /*<<< orphan*/ ) ; 
 struct mbuf* _M_GETHDR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  m_dup_pkthdr (struct mbuf*,struct mbuf*,int) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_m16kget (struct mbuf*,int) ; 
 unsigned int m_maxsize (int /*<<< orphan*/ ) ; 
 struct mbuf* m_mbigget (struct mbuf*,int) ; 
 scalar_t__ njcl ; 

struct mbuf *
m_dup(struct mbuf *m, int how)
{
	struct mbuf *n, **np;
	struct mbuf *top;
	int copyhdr = 0;

	np = &top;
	top = NULL;
	if (m->m_flags & M_PKTHDR)
		copyhdr = 1;

	/*
	 * Quick check: if we have one mbuf and its data fits in an
	 *  mbuf with packet header, just copy and go.
	 */
	if (m->m_next == NULL) {
		/* Then just move the data into an mbuf and be done... */
		if (copyhdr) {
			if (m->m_pkthdr.len <= MHLEN && m->m_len <= MHLEN) {
				if ((n = _M_GETHDR(how, m->m_type)) == NULL)
					return (NULL);
				n->m_len = m->m_len;
				m_dup_pkthdr(n, m, how);
				bcopy(m->m_data, n->m_data, m->m_len);
				return (n);
			}
		} else if (m->m_len <= MLEN) {
			if ((n = _M_GET(how, m->m_type)) == NULL)
				return (NULL);
			bcopy(m->m_data, n->m_data, m->m_len);
			n->m_len = m->m_len;
			return (n);
		}
	}
	while (m != NULL) {
#if BLUE_DEBUG
		printf("<%x: %x, %x, %x\n", m, m->m_flags, m->m_len,
		    m->m_data);
#endif
		if (copyhdr)
			n = _M_GETHDR(how, m->m_type);
		else
			n = _M_GET(how, m->m_type);
		if (n == NULL)
			goto nospace;
		if (m->m_flags & M_EXT) {
			if (m->m_len <= m_maxsize(MC_CL))
				MCLGET(n, how);
			else if (m->m_len <= m_maxsize(MC_BIGCL))
				n = m_mbigget(n, how);
			else if (m->m_len <= m_maxsize(MC_16KCL) && njcl > 0)
				n = m_m16kget(n, how);
			if (!(n->m_flags & M_EXT)) {
				(void) m_free(n);
				goto nospace;
			}
		}
		*np = n;
		if (copyhdr) {
			/* Don't use M_COPY_PKTHDR: preserve m_data */
			m_dup_pkthdr(n, m, how);
			copyhdr = 0;
			if (!(n->m_flags & M_EXT))
				n->m_data = n->m_pktdat;
		}
		n->m_len = m->m_len;
		/*
		 * Get the dup on the same bdry as the original
		 * Assume that the two mbufs have the same offset to data area
		 * (up to word boundaries)
		 */
		bcopy(MTOD(m, caddr_t), MTOD(n, caddr_t), (unsigned)n->m_len);
		m = m->m_next;
		np = &n->m_next;
#if BLUE_DEBUG
		printf(">%x: %x, %x, %x\n", n, n->m_flags, n->m_len,
		    n->m_data);
#endif
	}

	if (top == NULL)
		MDFail++;
	return (top);

nospace:
	m_freem(top);
	MDFail++;
	return (NULL);
}