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
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ u_int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  tags; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;
struct m_tag {scalar_t__ m_tag_cookie; scalar_t__ m_tag_id; scalar_t__ m_tag_type; } ;

/* Variables and functions */
 int M_PKTHDR ; 
 scalar_t__ M_TAG_VALID_PATTERN ; 
 struct m_tag* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct m_tag* SLIST_NEXT (struct m_tag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  m_tag_link ; 

struct m_tag *
m_tag_locate(struct mbuf *m, u_int32_t id, u_int16_t type, struct m_tag *t)
{
	struct m_tag *p;

	VERIFY(m->m_flags & M_PKTHDR);

	if (t == NULL) {
		p = SLIST_FIRST(&m->m_pkthdr.tags);
	} else {
		VERIFY(t->m_tag_cookie == M_TAG_VALID_PATTERN);
		p = SLIST_NEXT(t, m_tag_link);
	}
	while (p != NULL) {
		VERIFY(p->m_tag_cookie == M_TAG_VALID_PATTERN);
		if (p->m_tag_id == id && p->m_tag_type == type)
			return (p);
		p = SLIST_NEXT(p, m_tag_link);
	}
	return (NULL);
}