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
struct mbuf {int m_flags; int m_len; struct mbuf* m_next; int /*<<< orphan*/  m_type; } ;

/* Variables and functions */
 int MHLEN ; 
 int /*<<< orphan*/  MH_ALIGN (struct mbuf*,int) ; 
 int MLEN ; 
 int /*<<< orphan*/  M_ALIGN (struct mbuf*,int) ; 
 int /*<<< orphan*/  M_COPY_PKTHDR (struct mbuf*,struct mbuf*) ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  _MGET (struct mbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

struct mbuf *
m_prepend(struct mbuf *m, int len, int how)
{
	struct mbuf *mn;

	_MGET(mn, how, m->m_type);
	if (mn == NULL) {
		m_freem(m);
		return (NULL);
	}
	if (m->m_flags & M_PKTHDR) {
		M_COPY_PKTHDR(mn, m);
		m->m_flags &= ~M_PKTHDR;
	}
	mn->m_next = m;
	m = mn;
	if (m->m_flags & M_PKTHDR) {
		VERIFY(len <= MHLEN);
		MH_ALIGN(m, len);
	} else {
		VERIFY(len <= MLEN);
		M_ALIGN(m, len);
	}
	m->m_len = len;
	return (m);
}