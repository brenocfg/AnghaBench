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
struct mbuf {int m_len; int m_data; int /*<<< orphan*/ * m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCLGET (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGET (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLEN ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_DONTWAIT ; 
 int M_TRAILINGSPACE (struct mbuf*) ; 
 int /*<<< orphan*/  m_cat (struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static struct mbuf *
key_alloc_mbuf(
			   int l)
{
	struct mbuf *m = NULL, *n;
	int len, t;
	
	len = l;
	while (len > 0) {
		MGET(n, M_DONTWAIT, MT_DATA);
		if (n && len > MLEN)
			MCLGET(n, M_DONTWAIT);
		if (!n) {
			m_freem(m);
			return NULL;
		}
		
		n->m_next = NULL;
		n->m_len = 0;
		n->m_len = M_TRAILINGSPACE(n);
		/* use the bottom of mbuf, hoping we can prepend afterwards */
		if (n->m_len > len) {
			t = (n->m_len - len) & ~(sizeof(long) - 1);
			n->m_data += t;
			n->m_len = len;
		}
		
		len -= n->m_len;
		
		if (m)
			m_cat(m, n);
		else
			m = n;
	}
	
	return m;
}