#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mbuf {unsigned int m_len; int m_flags; int /*<<< orphan*/  m_ext; struct mbuf* m_next; void* m_data; } ;

/* Variables and functions */
 scalar_t__ IS_P2ALIGNED (uintptr_t,unsigned int) ; 
 int MBUF_MULTIPAGES (struct mbuf*) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_DONTWAIT ; 
 int M_EXT ; 
 uintptr_t P2ROUNDUP (uintptr_t,unsigned int) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 struct mbuf* _M_RETRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  m_incref (struct mbuf*) ; 

__attribute__((used)) static struct mbuf *
m_expand(struct mbuf *m, struct mbuf **last)
{
	struct mbuf *top = NULL;
	struct mbuf **nm = &top;
	uintptr_t data0, data;
	unsigned int len0, len;

	VERIFY(MBUF_MULTIPAGES(m));
	VERIFY(m->m_next == NULL);
	data0 = (uintptr_t)m->m_data;
	len0 = m->m_len;
	*last = top;

	for (;;) {
		struct mbuf *n;

		data = data0;
		if (IS_P2ALIGNED(data, PAGE_SIZE) && len0 > PAGE_SIZE)
			len = PAGE_SIZE;
		else if (!IS_P2ALIGNED(data, PAGE_SIZE) &&
		    P2ROUNDUP(data, PAGE_SIZE) < (data + len0))
			len = P2ROUNDUP(data, PAGE_SIZE) - data;
		else
			len = len0;

		VERIFY(len > 0);
		VERIFY(m->m_flags & M_EXT);
		m->m_data = (void *)data;
		m->m_len = len;

		*nm = *last = m;
		nm = &m->m_next;
		m->m_next = NULL;

		data0 += len;
		len0 -= len;
		if (len0 == 0)
			break;

		n = _M_RETRY(M_DONTWAIT, MT_DATA);
		if (n == NULL) {
			m_freem(top);
			top = *last = NULL;
			break;
		}

		n->m_ext = m->m_ext;
		m_incref(m);
		n->m_flags |= M_EXT;
		m = n;
	}
	return (top);
}