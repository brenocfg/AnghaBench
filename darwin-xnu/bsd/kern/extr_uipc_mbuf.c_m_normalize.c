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
struct mbuf {struct mbuf* m_next; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ MBUF_MULTIPAGES (struct mbuf*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  atomic_add_32 (int /*<<< orphan*/ *,int) ; 
 struct mbuf* m_expand (struct mbuf*,struct mbuf**) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mb_normalized ; 

struct mbuf *
m_normalize(struct mbuf *m)
{
	struct mbuf *top = NULL;
	struct mbuf **nm = &top;
	boolean_t expanded = FALSE;

	while (m != NULL) {
		struct mbuf *n;

		n = m->m_next;
		m->m_next = NULL;

		/* Does the data cross one or more page boundaries? */
		if (MBUF_MULTIPAGES(m)) {
			struct mbuf *last;
			if ((m = m_expand(m, &last)) == NULL) {
				m_freem(n);
				m_freem(top);
				top = NULL;
				break;
			}
			*nm = m;
			nm = &last->m_next;
			expanded = TRUE;
		} else {
			*nm = m;
			nm = &m->m_next;
		}
		m = n;
	}
	if (expanded)
		atomic_add_32(&mb_normalized, 1);
	return (top);
}