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
struct TYPE_2__ {int /*<<< orphan*/  tags; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;
struct m_tag {scalar_t__ m_tag_cookie; } ;

/* Variables and functions */
 int M_PKTHDR ; 
 scalar_t__ M_TAG_VALID_PATTERN ; 
 struct m_tag* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct m_tag* SLIST_NEXT (struct m_tag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  m_tag_delete (struct mbuf*,struct m_tag*) ; 
 int /*<<< orphan*/  m_tag_link ; 

void
m_tag_delete_chain(struct mbuf *m, struct m_tag *t)
{
	struct m_tag *p, *q;

	VERIFY(m->m_flags & M_PKTHDR);

	if (t != NULL) {
		p = t;
	} else {
		p = SLIST_FIRST(&m->m_pkthdr.tags);
	}
	if (p == NULL)
		return;

	VERIFY(p->m_tag_cookie == M_TAG_VALID_PATTERN);
	while ((q = SLIST_NEXT(p, m_tag_link)) != NULL) {
		VERIFY(q->m_tag_cookie == M_TAG_VALID_PATTERN);
		m_tag_delete(m, q);
	}
	m_tag_delete(m, p);
}